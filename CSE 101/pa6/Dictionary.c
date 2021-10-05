//--------------------------------------------------------------------------------------------------
// Sean Brandon, spbrando
// 2021 Spring CSE101 pa6
// Dictionary.c
// Implementation file for the Dictionary ADT
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

//------------------------------------------- Structs ----------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    KEY_TYPE key;
    VAL_TYPE val;
    struct NodeObj* parent;
    struct NodeObj* left;
    struct NodeObj* right;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private Dictionary type
typedef struct DictionaryObj{
    Node root;          // Start of tree
    Node NIL;           // End of tree
    Node current;       // Used for iteration
    int direction;      // 1 = forward, 0 = no iteration, -1 = backwards
    int unique;
    int size;
} DictionaryObj;

//------------------------------------ Constructors-Destructors ------------------------------------

// newNode()
// Creates and returns a new Node
Node newNode(KEY_TYPE key, VAL_TYPE val){
    Node N = NULL;
    N = malloc(sizeof(NodeObj));
    if (N == NULL){
        fprintf(stderr, "Dictionary Error: newNode() malloc'ed a NULL Node\n");
        exit(EXIT_FAILURE);
    }
    N->key = key;
    N->val = val;
    N->parent = N->left = N->right = NULL;
    return(N);
}

// freeNode()
// Frees all heap memory associated with *pN, and sets *pN to NULL
void freeNode(Node *pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary
// will accept duplicate keys, i.e. distinct pairs with identical keys. If
// unique==true (1 or any non-zero value), then duplicate keys will not be
// accepted. In this case, the operation insert(D, k) will enforce the
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
    Dictionary D;
    Node nullNode;
    D = malloc(sizeof(DictionaryObj));
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: newDictionary() malloc'ed a NULL Dictionary\n");
        exit(EXIT_FAILURE);
    }
    nullNode = newNode(KEY_UNDEF, VAL_UNDEF);
    D->root = nullNode;
    D->NIL = nullNode;
    D->root->parent = D->NIL;
    D->current = nullNode;
    D->direction = 0;
    D->unique = unique;
    D->size = 0;
    return(D);
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
    if (pD != NULL && *pD != NULL){
        makeEmpty(*pD);
        free((*pD)->NIL);
        free(*pD);
        *pD = NULL;
    }
}

//---------------------------------------- Access functions ----------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling size() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    return (D->size);
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling getUnique() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    return (D->unique);
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling lookup() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    Node x = D->root;

    while(x != D->NIL && KEY_CMP(k, x->key) != 0){
        if (KEY_CMP(k, x->key) < 0){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    return (x->val);
}

// dictMin()
// Private helper function. Returns the min node of the Dictionary D starting from Node x
Node dictMin(Dictionary D, Node x){
    while (x != D->NIL && x->left != D->NIL){
        x = x->left;
    }
    return x;
}

// dictMax()
// Private helper function. Returns the max node of the Dictionary D starting from Node x
Node dictMax(Dictionary D, Node x){
    while (x != D->NIL && x->right != D->NIL){
        x = x->right;
    }
    return x;
}

//------------------------------------- Manipulation procedures ------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling insert() on a NULL Dictionary reference\n");
    }
    if (D->unique == 1 && lookup(D, k) != VAL_UNDEF){
        fprintf(stderr, "Dictionary Error: Calling insert() with a already inserted key\n");
        exit(EXIT_FAILURE);
    }

    Node z = newNode(k, v);
    Node y = D->NIL;
    Node x = D->root;
    while (x != D->NIL){
        y = x;
        if(KEY_CMP(k, x->key) < 0){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y;
    if (y == D->NIL){
        D->root = z;         // Dictionary was empty
        z->left = D->NIL;
        z->right = D->NIL;
    }
    else if (KEY_CMP(k, y->key) < 0){
        y->left = z;
        z->left = D->NIL;
        z->right = D->NIL;
    }
    else {
        y->right = z;
        z->left = D->NIL;
        z->right = D->NIL;
    }
    D->size++;
}

// transplant()
// Private helper function for delete()
void transplant(Dictionary D, Node u, Node v){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling transplant() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    if (u == D->root){
        D->root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if (v != D->NIL){
        v->parent = u->parent;
    }
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling delete() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    if (lookup(D, k) == VAL_UNDEF){
        fprintf(stderr, "Dictionary Error: Calling delete() with a non-existent key\n");
        exit(EXIT_FAILURE);
    }

    Node z = D->root;
    // Locate correct node
    while (KEY_CMP(z->key, k) != 0){
        if(KEY_CMP(k, z->key) < 0){
            z = z->left;
        }
        else{
            z = z->right;
        }
    }

    // Rewire around located node
    if (z->left == D->NIL){                 // Right only OR last node
        transplant(D, z, z->right);
    }
    else if (z->right == D->NIL){           // left only
        transplant(D, z, z->left);
    }
    else{                                   // Left and right nodes present
        Node y = dictMin(D, z->right);
        if (y->parent != z){
            transplant(D, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(D, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    if (z == D->current){
        D->current = D->NIL;
    }
    // Delete located node
    freeNode(&z);
    D->size--;
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling makeEmpty() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    while (D->size > 0){
        delete(D, D->root->key);
    }
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling beginForward() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    Node y = dictMin(D, D->root);
    D->current = y;
    D->direction = 1;
    return y->val;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling beginReverse() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    Node y = dictMax(D, D->root);
    D->current = y;
    D->direction = -1;
    return y->val;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling currentKey() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    return D->current->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling currentVal() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    return D->current->val;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling next() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    if (D->direction == 1){             // forward iteration
        if (D->current->right != D->NIL){
            D->current = dictMin(D, D->current->right);
            return D->current->val;
        }
        Node y = D->current->parent;
        while (y != D->NIL && D->current == y->right){
            D->current = y;
            y = y->parent;
        }
        D->current = y;
        return D->current->val;
    }
    else if (D->direction == -1){       // backwards iteration
        if (D->current->left != D->NIL){
            D->current = dictMax(D, D->current->left);
            return D->current->val;
        }
        Node y = D->current->parent;
        while (y != D->NIL && D->current == y->left){
            D->current = y;
            y = y->parent;
        }
        D->current = y;
        return D->current->val;
    }
    return VAL_UNDEF;                   // no iteration was underway
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling prev() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    if (D->direction == -1){         // backwards iteration
        if (D->current->left != D->NIL){
            D->current = dictMax(D, D->current->left);
            return D->current->val;
        }
        Node y = D->current->parent;
        while (y != D->NIL && D->current == y->left){
            D->current = y;
            y = y->parent;
        }
        D->current = y;
        return D->current->val;
    }
    else if (D->direction == 1){    // forwards iteration
        if (D->current->right != D->NIL){
            D->current = dictMin(D, D->current->right);
            return D->current->val;
        }
        Node y = D->current->parent;
        while (y != D->NIL && D->current == y->right){
            D->current = y;
            y = y->parent;
        }
        D->current = y;
        return D->current->val;
    }
    return VAL_UNDEF;               // no iteration was underway
}

//--------------------------------------- Other operations -----------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling printDictionary() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    Node n = D->current;    // in case the was an iteration taking place already
    int d = D->direction;   // in case the was an iteration taking place already
    for (beginForward(D); currentVal(D) != VAL_UNDEF; next(D)){
        fprintf(out, ""KEY_FORMAT" "VAL_FORMAT"\n", currentKey(D), currentVal(D));
    }

    // in case the was an iteration taking ilace already, move back to that pos
    if (d == 1){
        for(beginForward(D); D->current != n; next(D));
    }
    else if (d == -1){
        for (beginReverse(D); D->current != n; prev(D));
    }
}
