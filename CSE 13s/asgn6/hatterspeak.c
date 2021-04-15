#include "bf.h"
#include "hash.h"
#include "hatspeak.h"
#include "ll.h"
#include "parser.h"
#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "sh:f:mb"

extern bool move_to_front;
extern int seeks;
extern int nodes_trav;

int main(int argc, char **argv) {
  // User input variables and defaults
  uint32_t ht_size = 10000, bf_size = 1048576;
  bool stats = false;
  move_to_front = false;
  char choice;
  // Getopt loop
  while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
    switch (choice) {
    case 's':
      stats = true;
      break;
    case 'h':
      if (atoi(optarg) > 0) {
        ht_size = (uint32_t)atoi(optarg);
      } else {
        printf("Size of hash table must be greater than 0\n");
        return 0;
      }
      break;
    case 'f':
      if (atoi(optarg) > 0) {
        bf_size = (uint32_t)atoi(optarg);
      } else {
        printf("Size of Bloom filter must be greater than 0\n");
        return 0;
      }
      break;
    case 'm':
      move_to_front = true;
      break;
    case 'b':
      move_to_front = false;
      break;
    default:
      // Error message
      printf("Only these arguments are allowed:\n"
             "-s\twill suppress the letter from the censor, and instead\n"
             "\tprint the statistics that were computed.\n"
             "-h\tsize specifies that the hash table will have size\n"
             "\tentries (the default will be 10000).\n"
             "-f\tsize specifies that the Bloom filter will have size\n"
             "\tentries (the default will be 2^20).\n"
             "-m\twill use the move-to-front rule.\n"
             "-b\twill not use the move-to-front rule.\n"
             "ANY combination of these flags except for -m -b will be\n"
             "supported.\n");
      return 0;
    }
  }

  // Make the bloom filter and hash table
  BloomFilter *bf = bf_create(bf_size);
  HashTable *ht = ht_create(ht_size);

  // Fill hash table and Bloom Filter with hatterspeak.txt
  FILE *hatter_file = fopen("hatterspeak.txt", "r");
  char key_buffer[180];
  char hatter_buffer[180];
  while (fscanf(hatter_file, "%s %s", key_buffer, hatter_buffer) != EOF) {
    bf_insert(bf, key_buffer);
    ht_insert(ht, hs_create(key_buffer, hatter_buffer));
  }
  fclose(hatter_file);

  // Fill hash table and bloom filter and hash table with oldspeak.txt
  FILE *old_file = fopen("oldspeak.txt", "r");
  char word_buffer[180];
  while (fscanf(old_file, "%s\n", word_buffer) != EOF) {
    bf_insert(bf, word_buffer);
    ht_insert(ht, hs_create(word_buffer, NULL));
  }
  fclose(old_file);

  // Set up regular expression filter
  regex_t word_regex;
  if (regcomp(
          &word_regex, "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]*)*", REG_EXTENDED)) {
    printf("Expression Error\n");
    return 0;
  }

  // Prep string and ListNodes to store input words
  char *my_word = NULL;
  ListNode *non_forbiden = NULL;
  ListNode *forbiden = NULL;
  // Take in one word at a time
  while ((my_word = next_word(stdin, &word_regex))) {
    // set all characters in word to lowercase
    for(int i = 0; my_word[i]; i++) {
      my_word[i] = tolower(my_word[i]);
    }
    // Check if its in bloom filter
    if (bf_probe(bf, my_word)) {
      // Make sure it wasn't a false positive by checking in the hash table
      if (ht_lookup(ht, my_word) != NULL) {
        // Check if it has a translation or if its forbiden
        if (ht_lookup(ht, my_word)->gs->hatterspeak != NULL) {
          // Insert found hatterspeak struct into non_forbided linked list
          non_forbiden = ll_insert(
              &non_forbiden, hs_create(ht_lookup(ht, my_word)->gs->oldspeak,
                                 ht_lookup(ht, my_word)->gs->hatterspeak));
        } else {
          // Insert found hatterspeak struct into forbiden linked list
          forbiden = ll_insert(
              &forbiden, hs_create(ht_lookup(ht, my_word)->gs->oldspeak, NULL));
        }
      }
    }
  }

  // If stats flag is set
  if (stats) { // Print stats
    printf("Seeks: %d\n", seeks);
    printf("Avegage seek length: %f\n", ((float)nodes_trav / seeks));
    printf("Average Linked List length: %f\n",
        ((float)ht_node_count(ht) / ht_size));
    printf("Hash table load: %f%%\n", 100 * ((float)ht_count(ht) / ht_size));
    printf(
        "Bloom filter load: %f%%\n", 100 * ((float)bf_set_count(bf) / bf_size));
  } else { // Print letter
    if (forbiden != NULL) { // If there are forbiden words used
      printf("Dear Comrade,\n\nYou have chosen to use words that the queen has"
             " decreed oldspeak.\nDue to you infraction you will be sent to "
             "the dungeon where you will be taught hatterspeak.\n\nYour "
             "errors:\n\n");
      // for every node in forbiden list
      for (ListNode *cur = forbiden; cur != NULL;) {
        // Print and move
        printf("%s\n", cur->gs->oldspeak);
        cur = cur->next;
      }
    }

    if (non_forbiden != NULL) { // If there are non_forbiden bad words used
      if (forbiden == NULL) { // If there are ONLY non_forbiden bad words used
        printf("Dear Comrade,\n\nThe decree for hatterspeak finds your message "
               "lacking. Some of the words that you used are not hatterspeak.\n"
               "The list shows how to turn the oldspeak words into hatterspeak."
               "\n\n");
      } else { // If both forbiden and non_forbiden bad words are used
        printf("\nAppropriate hatterspeak translations.\n\n");
      }
      // For every node in non_forbiden list
      for (ListNode *cur = non_forbiden; cur != NULL;) {
        // Print and move
        printf("%s -> %s\n", cur->gs->oldspeak, cur->gs->hatterspeak);
        cur = cur->next;
      }
    }
  }

  // Free everything
  ll_delete(forbiden);
  ll_delete(non_forbiden);
  regfree(&word_regex);
  clear_words();
  bf_delete(bf);
  ht_delete(ht);

  return 0;
}
