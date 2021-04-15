#include "io.h"
#include "code.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static uint8_t symbuf[4096] = { 0 };
static uint16_t symbuffindex = 0;
static uint8_t bitbuf[4096] = { 0 };
static uint16_t bitbuffindex = 0;

uint64_t total_syms = 0; // Stats
uint64_t total_bits = 0; // Stats

// Wrapper for the read() syscall.
// Loops to read the specified number of bytes, or until input is exhausted.
// Returns the number of bytes read.
//
// infile:  File descriptor of the input file to read from.
// buf:     Buffer to store read bytes into.
// to_read: Number of bytes to read.
// returns: Number of bytes read.
//
int read_bytes(int infile, uint8_t *buf, int to_read) {
  int total = 0; // Total bytes read
  int bytes_read = 0;
  int bytes_to_read = to_read;
  do {
    // Syscall read into bytes_read and increment/decrement
    bytes_read = read(infile, buf + total, bytes_to_read);
    total += bytes_read;
    bytes_to_read = to_read - total;
    // While there are byte to rerad AND while we haven't read them all
  } while ((total != to_read) && (bytes_read > 0));
  total_syms += total;
  return total;
}

// Wrapper for the write() syscall.
// Loops to write the specified number of bytes, or until nothing is written.
// Returns the number of bytes written.
//
// outfile:   File descriptor of the output file to write to.
// buf:       Buffer that stores the bytes to write out.
// to_write:  Number of bytes to write.
// returns:   Number of bytes written.
//
int write_bytes(int outfile, uint8_t *buf, int to_write) {
  int total = 0; // Total bytes read
  int bytes_wrote = 0;
  int bytes_to_write = to_write;
  do {
    // Syscall write into bytes_wrote and increment/decrement
    bytes_wrote = write(outfile, buf + total, bytes_to_write);
    total += bytes_wrote;
    bytes_to_write = to_write - total;
    // While there are byte to write AND while we haven't written them all
  } while ((total != to_write) && (bytes_wrote != 0));
  total_bits += total;
  return total;
}

// Reads in a FileHeader from the input file.
// Endianness of header fields are swapped if byte order isn't little endian.
//
// infile:  File desc
// riptor of input file to read header from.
// header:  Pointer to memory where the bytes of the read header should go.
// returns: Void.
//
void read_header(int infile, FileHeader *header) {
  read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  bitbuffindex += 8;
  return;
}

// Writes a FileHeader to the output file.
// Endianness of header fields are swapped if byte order isn't little endian.
//
// outfile: File descriptor of output file to write header to.
// header:  Pointer to the header to write out.
// returns: Void.
//
void write_header(int outfile, FileHeader *header) {
  write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
  bitbuffindex += 8;
  return;
}

// "Reads" a symbol from the input file.
// The "read" symbol is placed into the pointer to sym (pass by reference).
// In reality, a block of symbols is read into a buffer.
// An index keeps track of the currently read symbol in the buffer.
// Once all symbols are processed, another block is read.
// If less than a block is read, the end of the buffer is updated.
// Returns true if there are symbols to be read, false otherwise.
//
// infile:  File descriptor of input file to read symbols from.
// sym:     Pointer to memory which stores the read symbol.
// returns: True if there are symbols to be read, false otherwise.
//
bool read_sym(int infile, uint8_t *byte) {
  static bool check;
  uint16_t temp;
  if (symbuffindex == 0) {
    int num_of_bytes_read = read_bytes(infile, symbuf, 4096);
    if (num_of_bytes_read == 4096) {
      check = true;
    } else {
      temp = num_of_bytes_read;
      check = false;
    }
  }
  *byte = symbuf[symbuffindex]; // Pass back symbol
  symbuffindex = (symbuffindex + 1) % 4096;
  return check || (symbuffindex != temp);
}

// Buffers a pair. A pair is comprised of a symbol and an index.
// The bits of the symbol are buffered first, starting from the LSB.
// The bits of the index are buffered next, also starting from the LSB.
// bit_len bits of the index are buffered to provide a minimal representation.
// The buffer is written out whenever it is filled.
//
// outfile: File descriptor of the output file to write to.
// sym:     Symbol of the pair to buffer.
// index:   Index of the pair to buffer.
// bit_len: Number of bits of the index to buffer.
// returns: Void.
//
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bit_len) {
  // Buffering sym
  for (uint8_t i = 0; i < 8; i++) {
    // bit shifting
    if (sym & (1 << (i % 8))) {
      // Set bit of bitbuffindex
      bitbuf[bitbuffindex / 8] |= (1 << (bitbuffindex % 8));
    } else {
      // Clear bit
      bitbuf[bitbuffindex / 8] &= ~(1 << (bitbuffindex % 8));
    }
    bitbuffindex += 1;
    if (bitbuffindex == 4096 * 8) {
      write_bytes(outfile, bitbuf, 4096);
      bitbuffindex = 0;
    }
  }

  // Buffering code
  for (uint8_t i = 0; i < bit_len; i++) {
    // bit shifting
    if (code & (1 << (i % 16))) {
      // Set bit of bitbuffindex
      bitbuf[bitbuffindex / 8] |= (1 << (bitbuffindex % 8));
    } else {
      // Clear bit
      bitbuf[bitbuffindex / 8] &= ~(1 << (bitbuffindex % 8));
    }
    bitbuffindex += 1;
    if (bitbuffindex / 8 == 4096) {
      write_bytes(outfile, bitbuf, 4096);
      bitbuffindex = 0;
    }
  }
  return;
}

// Writes out any remaining pairs of symbols and indexes to the output file.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
//
void flush_pairs(int outfile) {
  if (bitbuffindex != 0) {
    // Find number of bytes using ceiling division
    int bytes;
    if ((bitbuffindex & 8) == 0) {
      bytes = bitbuffindex / 8;
    } else {
      bytes = (bitbuffindex / 8) + 1;
    }

    write_bytes(outfile, bitbuf, bytes);
  }
  return;
}

// "Reads" a pair (symbol and index) from the input file.
// The "read" symbol is placed in the pointer to sym (pass by reference).
// The "read" index is placed in the pointer to index (pass by reference).
// In reality, a block of pairs is read into a buffer.
// An index keeps track of the current bit in the buffer.
// Once all bits have been processed, another block is read.
// The first 8 bits of the pair constitute the symbol, starting from the LSB.
// The next bit_len bits constitutes the index, starting from the the LSB.
// Returns true if there are pairs left to read in the buffer, else false.
// There are pairs left to read if the read index is not STOP_INDEX.
//
// infile:  File descriptor of the input file to read from.
// sym:     Pointer to memory which stores the read symbol.
// index:   Pointer to memory which stores the read index.
// bit_len: Length in bits of the index to read.
// returns: True if there are pairs left to read, false otherwise.
//
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bit_len) {
  // Reading sym
  *sym = 0;
  for (uint8_t i = 0; i < 8; i++) {
    if (bitbuffindex == 0) {
      read_bytes(infile, bitbuf, 4096);
    }
    if (bitbuf[bitbuffindex / 8] & (1 << (bitbuffindex % 8))) {
      // set_bit(*code, i)
      *sym |= (1 << (i % 8));
    } else {
      // clear_bit(*code, i)
      *sym &= ~(1 << (i % 8));
    }
    bitbuffindex = (bitbuffindex + 1) % (4096 * 8);
  }

  // Reading code
  *code = 0;
  for (uint8_t i = 0; i < bit_len; i++) {
    if (bitbuffindex == 0) {
      read_bytes(infile, bitbuf, 4096);
    }

    if (bitbuf[bitbuffindex / 8] & (1 << (bitbuffindex % 8))) {
      // set_bit(*code, i)
      *code |= (1 << (i % 16));
    } else {
      // clear_bit(*code, i)
      *code &= ~(1 << (i % 16));
    }
    bitbuffindex = (bitbuffindex + 1) % (4096 * 8);
  }
  // Return
  return (*code != STOP_CODE);
}

// Buffers a Word, or more specifically, the symbols of a Word.
// Each symbol of the Word is placed into a buffer.
// The buffer is written out when it is filled.
//
// outfile: File descriptor of the output file to write to.
// w:       Word to buffer.
// returns: Void.
//
void buffer_word(int outfile, Word *w) {
  for (uint32_t i = 0; i < w->len; i++) {
    symbuf[symbuffindex++] = w->syms[i];
    if (symbuffindex == 4096) { // If we've reached end of 4Kb
      write_bytes(outfile, symbuf, 4096);
      symbuffindex = 0; // Reset symbuffindex
    }
  }
  return;
}

// Writes out any remaining symbols in the buffer.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
//
void flush_words(int outfile) {
  if (symbuffindex != 0) {
    write_bytes(outfile, symbuf, symbuffindex);
    symbuffindex = 0;
  }
  return;
}
