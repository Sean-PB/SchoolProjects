#include "hash.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>
// Constructor for a HashTable
//
// length:  Length of the HashTable.
// salt:    Salt for the HashTable.
//
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) { // If malloc worked
    // Set salts (numbers given in lab pdf)
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    // Assign input value to HashTable struct
    ht->length = length;
    // Heads is an array of pointers
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }
  // Return NIL if malloc failed
  return (HashTable *)NIL;
}

// Destructor for a HashTable.
//
// ht:   The HashTable.
//
void ht_delete(HashTable *ht) {
  if (ht == NULL) { // Checking that the given HashTable is not null
    printf("Null HashTable in ht_delete\n");
    return;
  }
  // Loop through each index in HashTable->heads
  for (uint32_t i = 0; i < ht->length; i++) {
    if (ht->heads[i] != NULL) { // If index is not null
      // Delete that linked list
      ll_delete(ht->heads[i]);
    }
  }
  // After every linked list in HashTable is deleted,
  // free the HashTable
  free(ht->heads);
  free(ht);
  return;
}

// Returns number of non null heads in hash table
//
// h:   The HashTable.
//
uint32_t ht_count(HashTable *h) {
  if (h == NULL) { // Checking that HashTable isn't NULL
    printf("Null HashTable in ht_count\n");
    return 0;
  }

  uint32_t count = 0;
  // Loop through each index in the HashTabele->heads
  for (uint32_t i = 0; i < h->length; i++) {
    // If there is a node there, increment count
    if (h->heads[i] != NULL) {
      count++;
    }
  }
  return count;
}

// Searches a HashTable for a key.
// Returns the ListNode if found and returns NULL otherwise.
// This should call the ll_lookup() function.
//
// ht:   The HashTable.
// key:  The key to search for.
//
ListNode *ht_lookup(HashTable *ht, char *key) {
  if (ht == NULL) { // Checking that HashTable isn't nuull
    printf("Null HashTable in ht_lookup\n");
    return NULL;
  }
  // Finding the index of the key if it were in the HashTable
  uint32_t index = hash(ht->salt, key) % ht->length;
  // Chekc to see if the key is anywhere in that index
  // Will return node if its there and NULL otherwise
  return ll_lookup(&ht->heads[index], key);
}

// First creates a new ListNode from HatterSpeak.
// The created ListNode is then inserted into a HashTable.
// This should call the ll_insert() function.
//
// ht:   The HashTable.
// gs:   The HatterSpeak to add to the HashTable.
//
void ht_insert(HashTable *ht, HatterSpeak *gs) {
  if (ht == NULL) { // Checking to see if HashTable is NULL
    printf("Null HasTable in ht_insert\n");
    return;
  }
  // Find the index of where HatterSpeak struct should go
  uint32_t index = hash(ht->salt, gs->oldspeak) % ht->length;
  // Use that index to insert a list node
  ht->heads[index] = ll_insert(&ht->heads[index], gs);
  return;
}

// My function, not found in lab doc.
// Counts all linked list nodes in a hashtable
//
// ht:   The HashTable
//
int ht_node_count(HashTable *h) {
  if (h == NULL) { // Check that HashTable is not NULL
    printf("Null HashTable in ht_count\n");
    return 0;
  }
  uint32_t count = 0;
  // For each index in the HashTable
  for (uint32_t i = 0; i < h->length; i++) {
    // If there is a linked list at that index
    if (h->heads[i] != NULL) {
      // For each non null node in that linked list
      for (ListNode *c = h->heads[i]; c != NULL;) {
        // Increment count and move through linked list
        count++;
        c = c->next;
      }
    }
  }
  return count;
}
