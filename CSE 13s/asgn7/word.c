#include "word.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constructor for a word.
//
// syms:    Array of symbols a Word represents.
// len:     Length of the array of symbols.
// returns: Pointer to a Word that has been allocated memory.
//
Word *word_create(uint8_t *syms, uint32_t len) {
  Word *w = (Word *)malloc(sizeof(Word));
  if (w) {
    if (syms != NULL) {
      w->syms = (uint8_t *)calloc(len, sizeof(uint8_t));
      if (w->syms) {
        memcpy(w->syms, syms, len);
      }
    }
    w->len = len;
    return w;
  }
  printf("word_create malloc error\n");
  return NULL;
}

// Constructs a new Word from the specified Word appended with a symbol.
// The Word specified to append to may be empty.
// If the above is the case, the new Word should contain only the symbol.
//
// w:       Word to append to.
// sym:     Symbol to append.
// returns: New Word which represents the result of appending.
//
Word *word_append_sym(Word *w, uint8_t sym) {
  uint8_t arr[w->len + 1]; // Add space for extra sym
  for (uint32_t i = 0; i < w->len;
       i++) { // loop through adding syms from old word
    arr[i] = w->syms[i];
  }
  arr[w->len + 1] = sym; // Add new sym to end
  return word_create(arr, w->len + 1); // create the word
}

// Destructor for a Word.
//
// w:       Word to free memory for.
// returns: Void.
//
void word_delete(Word *w) {
  if (w != NULL) {
    free(w->syms);
    free(w);
  }
  return;
}

// Creates a new WordTable, which is an array of Words.
// A WordTable has a pre-defined size of MAX_CODE (UINT16_MAX - 1).
// This is because codes are 16-bit integers.
// A WordTable is initialized with a single Word at index EMPTY_CODE.
// This Word represents the empty word, a string of length of zero.
//
// returns:  Initialized WordTable
//
WordTable *wt_create(void) {
  WordTable *wt = (WordTable *)calloc(MAX_CODE, sizeof(Word *));
  if (wt) {
    wt[EMPTY_CODE] = word_create(NULL, 0);
  }
  return wt;
}

// Resets a WordTable to having just the empty Word.
//
// wt:      WordTable to reset.
// returns: Void.
//
void wt_reset(WordTable *wt) {
  // loop through wt (array) calling word delete
  // starting at 2 to save the empty word
  for (int i = START_CODE; i < MAX_CODE; i++) {
    word_delete(wt[i]);
  }
  return;
}

// Deletes an entire WordTable.
// All Words in the WordTable must be deleted as well.
//
// wt:      WordTable to free memory for.
// returns: Void.
//
void wt_delete(WordTable *wt) {
  // same as reset except delete emtpy word
  for (int i = EMPTY_CODE; i < MAX_CODE; i++) {
    word_delete(wt[i]);
  }
  free(wt);
  return;
}
