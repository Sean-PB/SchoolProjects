#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "vi:o:"

uint64_t total_bits;
uint64_t total_syms;

// Prototypes
uint8_t bit_len(uint16_t num);

int main(int argc, char **argv) {
  // User input variables and defaults
  static bool stats = false;
  static int infile = STDIN_FILENO;
  static int outfile = STDOUT_FILENO;
  char choice;
  // Getopt loop
  while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
    switch (choice) {
    case 'v':
      stats = true;
      break;
    case 'i':
      infile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
      break;
    case 'o':
      outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
      break;
    default:
      printf("Only the following inputs are allowed:\n"
             "-v   : Display compression statistics\n"
             "-i   <input>: Specify input to decompress (stdin by default)\n"
             "-o   <output>: Specify output of decompressed input (stdout "
             "by default)\n");
      return 0;
    }
  }

  FileHeader hd = { 0, 0 };
  read_header(infile, &hd);
  fchmod(outfile, hd.protection);
  if (hd.magic != 0x8badbeef) {
    return 0;
  }

  WordTable table = *wt_create();
  uint8_t cur_sym = 0;
  uint16_t cur_code = 0;
  uint16_t next_code = START_CODE;
  while (read_pair(infile, &cur_code, &cur_sym, bit_len(next_code))) {
    table[next_code] = *word_append_sym(&table[cur_code], cur_sym);
    buffer_word(outfile, &table[next_code]);
    next_code = next_code + 1;
    if (next_code == MAX_CODE) {
      wt_reset(&table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);

  // Close files
  close(infile);
  close(outfile);

  if (stats) {
    printf("Compressed file size: %d bytes\n"
           "Uncompressed file size: %d bytes\n"
           "Compression ratio %.2f%% bytes\n",
        (int)total_syms, (int)total_bits,
        (100 * (1 - (float)(total_syms / total_bits))));
  }

  return 0;
}

// Finds number of bits needed to represent a bit
uint8_t bit_len(uint16_t num) {
  uint8_t count = 0;
  while (num > 0) {
    count++;
    num /= 2;
  }
  return count;
}
