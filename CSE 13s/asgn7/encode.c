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

// Prototype
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
      infile = open(optarg, O_RDONLY);
      break;
    case 'o':
      outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
      break;
    default:
      printf("Only the following inputs are allowed:\n"
             "-v   : Display compression statistics\n"
             "-i   <input>: Specify input to compress (stdin by default)\n"
             "-o   <output>: Specify output of compressed input (stdout "
             "by default)\n");
      close(infile);
      close(outfile);
      return 0;
    }
  }

  // Making header
  FileHeader hd = { 0, 0 };
  hd.magic = 0x8badbeef;
  struct stat header_protection;
  fstat(infile, &header_protection);
  hd.protection = header_protection.st_mode;
  fchmod(outfile, hd.protection);
  write_header(outfile, &hd);

  // Pseudo given in lab pdf
  TrieNode *root = trie_create();
  if (!root) { // If trie_create fails
    // close files
    close(infile);
    close(outfile);
    return 0;
  }
  TrieNode *cur_node = root;
  TrieNode *prev_node = NULL;
  TrieNode *next_node = NULL;
  uint8_t cur_sym = 0;
  uint16_t prev_sym = 0;
  uint16_t next_code = START_CODE;
  while (read_sym(infile, &cur_sym)) {
    next_node = trie_step(cur_node, cur_sym);
    if (next_node) {
      prev_node = cur_node;
      cur_node = next_node;
    } else {
      buffer_pair(outfile, cur_node->code, cur_sym, bit_len(next_code));
      cur_node->children[cur_sym] = trie_node_create(next_code);
      if (!cur_node->children[cur_sym]) { // If trie_create fails
        // close files
        close(infile);
        close(outfile);
        return 0;
      }
      cur_node = root;
      next_code += 1;
    }
    if (next_code == MAX_CODE) {
      trie_reset(root);
      cur_node = root;
      next_code = START_CODE;
    }
    prev_sym = cur_sym;
  }
  if (cur_node != root) {
    buffer_pair(outfile, prev_node->code, prev_sym, bit_len(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }
  buffer_pair(outfile, STOP_CODE, 0, bit_len(next_code));
  flush_pairs(outfile);

  // Close files
  close(infile);
  close(outfile);

  if (stats) {
    printf("Compressed file size: %d bytes\n"
           "Uncompressed file size: %d bytes\n"
           "Compression ratio %.2f%% bytes\n",
        (int)total_bits, (int)total_syms,
        (100 * (1 - (float)(total_bits / total_syms))));
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
