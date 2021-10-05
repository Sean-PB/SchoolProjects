/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa2
* List.h
* Header file for List ADT
***************************************************************************************************/
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdio.h>

// ----------------------------- Exported type ---------------------------------
typedef struct ListObj* List;

// ------------------------- Constructors - Destructors ------------------------

// newList()
// Creates and returns a new empty list
List newList(void);

// freeList(pL)
// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL);

// -------------------------- Access functions ---------------------------------

// length(L)
// Returns the number of elements in L.
int length(List L);

// index(L)
// Returns index of cursor element if defined, -1 otherwise.
// !Cannot contain a loop!
int index(List L);

// front(L)
// Returns front element of L.
// Pre: length()>0
int front(List L);

// back(L)
// Returns back element of L
// Pre: length()>0
int back(List L);

// get(L)
// Returns cursor element of L.
// Pre: length()>0, index()>= 0
int get(List L);

// equals(A, B)
// Returns true (1) iff Lists A and B are in same state, and returns false(0)
// otherwise.
int equals(List A, List B);

// ------------------------ Manipulation procedures ----------------------------

// clear(L)
// Resets L to its original empty state
void clear (List L);

// set(L, x)
// Overwrites the cursor element's data with x.
// Prerequisite: length()>0, index()>=0
void set(List L, int x);

// moveFront(L)
// If L is non-empty, sets cursor under the front element, otherwise does
// nothing.
void moveFront(List L);

// moveBack(L)
// If L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L);

// movePrev(L)
// If cursor is defined and not at front, move cursor ones step toward the back
// of L;
// If cursor is defined and at back, cursor becomes undefined;
// If cursor is undefined do nothing.
void movePrev(List L);

// moveNext(L)
// If cursor is defined and not at back, move cursor one step toward the back of
// L;
// If cursor is defined and at back, cursor becomes undefined;
// If cursor is undefined do nothing.
void moveNext(List L);

// prepend(L, x)
// Insert new element into L. If L is non-empty, insertion takes place before
// front element.
void prepend(List L, int x);

// append(L, x)
// Insert new element into L. If L is non-empty, insertion takes place after
// back element.
void append(List L, int x);

// insertBefore(L, x)
// Insert new element before cursor
// Pre: length()>0, index()>=0
void insertBefore(List L, int x);

// insertAfter(L, x)
// Insert new element after cursor
// Pre: length()>0, index()>=0
void insertAfter(List L, int x);

// deleteFront(L)
// Deletes the front element.
// Pre: length()>0
void deleteFront(List L);

// deleteBack(L)
// Delete the back element.
// Pre: length()>0
void deleteBack(List L);

// delete(L)
// Delete cursor element, making cursor undefined
// Pre: length()>0, index()>=0
void delete(List L);

// ---------------------- Other operations -------------------------------------

// printList(out, L)
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L);

// copyList(L)
// Returns a new List representing the same integer sequence as L. The cursor in
// the new list is undefined, regardless of the state of the cursor in L. The
// state of L is unchanged.
List copyList(List L);

// concatList(A, B)
// Returns a new List which is the concatenation of A and B. The cursor in the
// new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B);

#endif
