#include "ll.h"
#include "hatspeak.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool move_to_front;
int seeks;
int nodes_trav;

// Consrtuctor for a ListNode.
//
// gs:   Hatterspeak struct containing oldspeak and its hatterspeak translationn
//
ListNode *ll_node_create(HatterSpeak *gs) {
  ListNode *n = (ListNode *)malloc(sizeof(ListNode));
  if (n == NULL) { // Checking malloc
    printf("Failed to create node\n");
    return NULL;
  }
  // Assigning struct values
  n->gs = gs;
  n->next = NULL;
  return n;
}

// Destructor for a ListNode.
//
// n:    The ListNode to free.
//
void ll_node_delete(ListNode *n) {
  if (n == NULL) {
    printf("Failed to delete node\n");
    return;
  }
  // Freeing everything in the node
  // Including the hatterspeak struct
  hs_delete(n->gs);
  free(n->gs);
  free(n);

  return;
}

// Destructor for a linked list of ListNodes.
//
// head:    The head of the linked list.
//
void ll_delete(ListNode *head) {
  // Looping through and deleting every node in list
  for (ListNode *cur = head; cur != NULL;) {
    ListNode *next = cur->next;
    ll_node_delete(cur);
    cur = next;
  }
  return;
}

// Creates and inserts a ListNode into a linked list.
//
// head:  The head of the linked list to insert in.
// gs:    HatterSpeak struct.
//
ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  // Checking that hatterspeak isn't already present in list
  ListNode *node = ll_lookup(head, gs->oldspeak);
  if (node != NULL) { // If it is, free the input and return
    hs_delete(gs);
    free(gs);
    return *head;
  }
  // If it isn't, create the node and make it head of list
  node = ll_node_create(gs);
  if (node != NULL) { // Making sure node create didn't fail
    node->next = *head;
  } // If it did fail, node would be null anyways so no need for an else
  return node; // Return node becuase it is the new head
}

// Searches for a specific key in a linked list.
// Returns the ListNode if found and NULL otherwise.
//
// head:  The head of the linked list to search in.
// key:   The key to search for.
//
ListNode *ll_lookup(ListNode **head, char *key) {
  seeks++;
  if (head == NULL) { // Check that head isn't null
    printf("Null head in ll_lookup\n");
    return NULL;
  }
  ListNode *prev = NULL; // Keep track of prev node in case move_to_front
  for (ListNode *c = *head; c != NULL;) { // Loop through nodes in list
    nodes_trav++;
    // If current node's oldspeak is same as the key
    if (strcmp(c->gs->oldspeak, key) == 0) {
      // If move to front is on AND if we aren't already at the head
      if ((move_to_front) && (prev != NULL)) {
        // Rewire linked list to move current node to head without breaking
        // the linked list
        prev->next = c->next;
        c->next = *head;
        *head = c;
      }
      return c; // Returning found node
    }
    // Moving through list if node wasn't found yet
    prev = c;
    c = c->next;
  }
  // Return NULL if key isn't in list
  return NULL;
}
