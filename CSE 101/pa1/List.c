/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa1
* List.c
* Implementation file for List ADT
***************************************************************************************************/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// ------------------------------ Structs --------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private List type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int cursorIndex;
    int length;
} ListObj;

// ------------------------- Constructors - Destructors ------------------------

// newList()
// Creates and returns a new empty list
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    if(L == NULL){
        fprintf(stderr, "List Error: newList() malloc'ed a NULL List");
        exit(EXIT_FAILURE);
    }
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
    return(L);
}

// freeList(pL)
// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// newNode()
// Creates and returns a new Node
Node newNode(int data){
    Node N = NULL;
    N = malloc(sizeof(NodeObj));
    if(N == NULL){
        fprintf(stderr, "List Error: newNode() malloc'ed a NULL Node");
        exit(EXIT_FAILURE);
    }
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return(N);
}

// freeNode(pN)
// Frees all heap memory associated with *pN, and sets *pN to null
void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

// -------------------------- Access functions ---------------------------------

// length(L)
// Returns the number of elements in L.
int length(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    return(L->length);
}

// index(L)
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    return(L->cursorIndex); // should already be -1 if L->cursor == NULL
}

// front(L)
// Returns front element of L.
// Pre: length()>0
int front(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling front() on empty List\n");
        exit(EXIT_FAILURE);
    }

    return(L->front->data);
}

// back(L)
// Returns back element of L
// Pre: length()>0
int back(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling back() on empty List\n");
        exit(EXIT_FAILURE);
    }

    return(L->back->data);
}

// get(L)
// Returns cursor element of L.
// Pre: length()>0, index()>= 0
int get(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling get() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0){
        fprintf(stderr, "List Error: calling get() when cursor is off List\n");
        exit(EXIT_FAILURE);
    }

    return(L->cursor->data);
}

// equals(A, B)
// Returns true (1) iff Lists A and B are in same state, and returns false(0)
// otherwise. !Don't use cursor, just make nodes to move up and down comparing!
int equals(List A, List B){
    int eq = 0;
    Node nodeA = NULL;
    Node nodeB = NULL;

    if (A == NULL || B == NULL){
        fprintf(stderr, "List Error: calling equals() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    eq = (A->length == B->length); // Checks if same length
    nodeA = A->front;
    nodeB = B->front;
    while(eq && nodeA != NULL){
        eq = (nodeA->data == nodeB->data); // Checks if same value
        nodeA = nodeA->next;
        nodeB = nodeB->next;
    }
    return(eq);
}

// ------------------------ Manipulation procedures ----------------------------

// clear(L)
// Resets L to its original empty state
void clear (List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    while(L->length != 0){
        deleteBack(L);
    }
}

// set(L, x)
// Overwrites the cursor element's data with x.
// Prerequisite: length()>0, index()>=0
void set(List L, int x){
    if(L == NULL){
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling set() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0){
        fprintf(stderr, "List Error: calling set() when cursor is off List\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
}

// moveFront(L)
// If L is non-empty, sets cursor under the front element, otherwise does
// nothing.
void moveFront(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0){
        L->cursor = L->front;
        L->cursorIndex = 0;
    }
}

// moveBack(L)
// If L is non-empty, sets cursor under the back element, otherwise does
// nothing.
void moveBack(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0){
        L->cursor = L->back;
        L->cursorIndex = L->length - 1;
    }
}

// movePrev(L)
// If cursor is defined and not at front, move cursor ones step toward the front
// of L;
// If cursor is defined and at front, cursor becomes undefined;
// If cursor is undefined do nothing.
void movePrev(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor != NULL){
        if(L->cursor != L->front){
            L->cursor = L->cursor->prev;
            L->cursorIndex -= 1;
        }
        else{
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
    }
}

// moveNext(L)
// If cursor is defined and not at back, move cursor one step toward the back of
// L;
// If cursor is defined and at back, cursor becomes undefined;
// If cursor is undefined do nothing.
void moveNext(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor != NULL){
        if(L->cursor != L->back){
            L->cursor = L->cursor->next;
            L->cursorIndex += 1;
        }
        else{
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
    }
}

// prepend(L, x)
// Insert new element into L. If L is non-empty, insertion takes place before
// front element.
void prepend(List L, int x){
    Node N = NULL;

    if(L == NULL){
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    N = newNode(x);
    if(L->length > 0){
        if(L->cursor != NULL){ // If cursor != null, cursor index needs shifting
            L->cursorIndex += 1;
        }
        N->next = L->front;
        L->front->prev = N;
    }
    else{
        L->back = N;
    }
    L->front = N;
    L->length++;
}

// append(L, x)
// Insert new element into L. If L is non-empty, insertion takes place after
// back element.
void append(List L, int x){
    Node N = NULL;

    if(L == NULL){
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    N = newNode(x);
    if(L->length > 0){
        N->prev = L->back;
        L->back->next = N;
    }
    else{
        L->front = N;
    }
    L->back = N;
    L->length++;
}

// insertBefore(L, x)
// Insert new element before cursor
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
    Node N = NULL;

    if(L == NULL){
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling insertBefore() on empty list\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0){
        fprintf(stderr, "List Error: calling insertBefore() on NULL cursor reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == L->front){
        prepend(L, x);
    }
    else{
        N = newNode(x);
        N->next = L->cursor;
        N->prev = L->cursor->prev;
        N->prev->next = N;
        L->cursor->prev = N;
        L->cursorIndex += 1;  // cursor index needs to shift with cursor
        L->length++;
    }
}

// insertAfter(L, x)
// Insert new element after cursor
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
    Node N = NULL;

    if(L == NULL){
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling insertAfter() on empty list\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0){
        fprintf(stderr, "List Error: calling insertAfter() on NULL cursor reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == L->back){
        append(L, x);
    }
    else{
        N = newNode(x);
        N->next = L->cursor->next;
        N->prev = L->cursor;
        L->cursor->next = N;
        N->next->prev = N;
        L->length++;
    }
}

// deleteFront(L)
// Deletes the front element. Moves front element pointer
// Pre: length()>0
void deleteFront(List L){
    Node tempNode = NULL;

    if(L == NULL){
        fprintf(stderr, "List Error: calling deleteFront() on NULL LIST reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling deleteFront() on empty list\n");
        exit(EXIT_FAILURE);
    }

    tempNode = L->front;
    if(L->length > 1){
        if(L->front == L->cursor){ // if front and cursor are the same...
            L->cursor = NULL;           // delete the cursor too and...
            L->cursorIndex = -1;        // set cursorIndex to -1
        }
        else{                      // otherwise, the cursor index needs shifting
            L->cursorIndex -= 1;
        }
        L->front = L->front->next;  // move "front" foward
        L->front->prev = NULL;
    }
    else{  // If there is only one element then NULL everything in list
        L->back = L->front = L->cursor = NULL;
        L->cursorIndex = -1;
    }
    L->length--;
    freeNode(&tempNode);
}

// deleteBack(L)
// Delete the back element. Moves back element pointer
// Pre: length()>0
void deleteBack(List L){
    Node tempNode = NULL;

    if(L == NULL){
        fprintf(stderr, "List Error: calling deleteBack() on NULL LIST reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling deleteBack() on empty list\n");
        exit(EXIT_FAILURE);
    }

    tempNode = L->back;
    if(L->length > 1){
        if(L->back == L->cursor){ // if front and cursor are the same...
            L->cursor = NULL;           // delete the cursor too and...
            L->cursorIndex = -1;        // set cursorIndex to -1
        }
        L->back = L->back->prev;  // Move "back" back
        L->back->next = NULL;
    }
    else{  // If there is only one element then NULL everything in list
        L->back = L->front = L->cursor = NULL;
        L->cursorIndex = -1;
    }
    L->length--;
    freeNode(&tempNode);
}

// delete(L)
// Delete cursor element, making cursor undefined
// Pre: length()>0, index()>=0
void delete(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling delete() on NULL LIST reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling delete() on empty list\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0){
        fprintf(stderr, "List Error: calling delete() on NULL cursor reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != L->front){
        L->cursor->prev->next = L->cursor->next;
    }
    else{
        L->front = L->cursor->next;
    }

    if(L->cursor != L->back){
        L->cursor->next->prev = L->cursor->prev;
    }
    else{
        L->back = L->cursor->prev;
    }

    L->length--;
    freeNode(&(L->cursor));
    L->cursorIndex = -1;
}

// ---------------------- Other operations -------------------------------------

// printList(out, L)
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
    Node N = NULL;

    if(L == NULL){
        fprintf(stderr, "List Error: calling printList() on NULL LIST reference\n");
        exit(EXIT_FAILURE);
    }

    if( out==NULL ){
        printf("Unable to open file for writing\n");
        exit(1);
    }
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d ", N->data); // print to file
    }
}

// copyList(L)
// Returns a new List representing the same integer sequence as L. The cursor in
// the new list is undefined, regardless of the state of the cursor in L. The
// state of L is unchanged.
List copyList(List L){
    List listCopy = NULL;
    Node N = NULL;

    if(L == NULL){
        fprintf(stderr, "List Error: calling copyList() on NULL LIST reference\n");
        exit(EXIT_FAILURE);
    }

    listCopy = newList();
    for(N = L->front; N != NULL; N = N->next){
        append(listCopy, N->data);
    }
    return(listCopy);
}

// concatList(A, B)
// Returns a new List which is the concatenation of A and B. The cursor in the
// new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B){
    List listConcat = NULL;
    Node N = NULL;

    if (A == NULL || B == NULL){
        fprintf(stderr, "List Error: calling concatList() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    listConcat = newList();
    for(N = A->front; N != NULL; N = N->next){
        append(listConcat, N->data);
    }
    for(N = B->front; N != NULL; N = N->next){
        append(listConcat, N->data);
    }
    return(listConcat);
}
