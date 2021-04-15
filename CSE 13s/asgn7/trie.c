#include "trie.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>

// Constructor for a TrieNode.
//
// index:   Index of the constructed TrieNode.
// returns: Pointer to a TrieNode that has been allocated memory.
//
TrieNode *trie_node_create(uint16_t index) {
  TrieNode *n = malloc(sizeof(TrieNode));
  if (n) { // Check if malloc worked
    for (int i = 0; i < ALPHABET; i++) { // Set every child to NULL
      n->children[i] = NULL;
    }
    n->code = index;
    return n;
  }
  // If n wasn't malloc'd correctly
  printf("trie_node_create malloc error. Exiting\n");
  return NULL;
}

// Destructor for a TrieNode.
//
// n:       TrieNode to free allocated memory for.
// returns: Void.
//
void trie_node_delete(TrieNode *n) {
  if (n) { // Check if n is not NULL
    free(n);
    n = NULL;
  }
  return;
}

// Initializes a Trie: a root TrieNode with the index EMPTY_CODE.
//
// returns: Pointer to the root of a Trie.
//
TrieNode *trie_create(void) {
  return trie_node_create(EMPTY_CODE); // Return a new node with starting index
}

// Resets a Trie to just the root TrieNode.
//
// root:    Root of the Trie to reset.
// returns: Void.
//
void trie_reset(TrieNode *root) {
  for (int i = 0; i < ALPHABET; i++) { // For all children
    if (root->children[i]) { // If child isn't null
      trie_delete(root->children[i]); // Delete
    }
  }
  return;
}

// Deletes a sub-Trie starting from the sub-Trie's root.
//
// n:       Root of the sub-Trie to delete.
// returns: Void.
//
void trie_delete(TrieNode *n) {
  if (n) { // Make sure n isn't NULL
    for (int i = 0; i < ALPHABET; i++) { // For all n's children
      trie_delete(n->children[i]);
    }
    trie_node_delete(n);
    n = NULL;
  }
  return;
}

// Returns a pointer to the child TrieNode reprsenting the symbol sym.
// If the symbol doesn't exist, NULL is returned.
//
// n:       TrieNode to step from.
// sym:     Symbol to check for.
// returns: Pointer to the TrieNode representing the symbol.
//
TrieNode *trie_step(
    TrieNode *n, uint8_t sym) { // MIGHT HAVE TO WRRY AB IT BEING NULL LATER
  return n->children[sym];
}
