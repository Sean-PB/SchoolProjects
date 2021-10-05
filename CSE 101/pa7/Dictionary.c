//--------------------------------------------------------------------------------------------------
// Sean Brandon, spbrando
// 2021 Spring CSE101 pa7
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
    char color;
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
    N->color = '\0';
    N->parent = N->left = N->right =  NULL;
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
    nullNode->color = 'B';
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

//------------------------------------ Private Helper Functions ------------------------------------

// dictMin()
// Returns the min node of the Dictionary D starting from Node x
Node dictMin(Dictionary D, Node x){
    while (x != D->NIL && x->left != D->NIL){
        x = x->left;
    }
    return x;
}

// dictMax()
// Returns the max node of the Dictionary D starting from Node x
Node dictMax(Dictionary D, Node x){
    while (x != D->NIL && x->right != D->NIL){
        x = x->right;
    }
    return x;
}

// leftRotate()
// Rotates the Red Black tree left
void leftRotate(Dictionary D, Node x){
    // set y
    Node y = x->right;

    // turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left != D->NIL){
        y->left->parent = x;
    }

    // link y's parent to x
    y->parent = x->parent;
    if (x->parent == D->NIL){
        D->root = y;
    }
    else if (x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    // put x on y's left
    y->left = x;
    x->parent = y;
}

// rightRotate()
// Rotates the Red Black tree right
void rightRotate(Dictionary D, Node x){
    // set y
    Node y = x->left;

    // turn y's right subtree into x's left subtree
    x->left = y->right;
    if (y->right != D->NIL){
        y->right->parent = x;
    }

    // link y's parent to x
    y->parent = x->parent;
    if (x->parent == D->NIL){
        D->root = y;
    }
    else if (x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }

    // put x on y's right
    y->right = x;
    x->parent = y;
}

// RB_InsertFixeUp()
// Balances the Red Black tree after insert()
void RB_InsertFixeUp(Dictionary D, Node z){
    Node y;
    while (z->parent->color == 'R'){
        if (z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if (y->color == 'R'){                   // case 1
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->right){         // case 2
                    z = z->parent;
                    leftRotate(D, z);
                }
                                                    // case 3
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(D, z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;
            if (y->color == 'R'){                   // case 4
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->left){          // case 5
                    z = z->parent;
                    rightRotate(D, z);
                }
                                                    // case 6
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(D, z->parent->parent);
            }
        }
    }
    D->root->color = 'B';
}

// RB_deleteFixUp()
// Balances the Red Black tree after delete()
void RB_deleteFixUp(Dictionary D, Node x){
    Node w;

    while (x != D->root && x->color == 'B'){
        if (x == x->parent->left){
            w = x->parent->right;
            if (w->color == 'R'){                                       // case 1
                w->color = 'B';
                x->parent->color = 'R';
                leftRotate(D, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B'){       // case 2
                w->color = 'R';
                x = x->parent;
            }
            else{
                if (w->right->color == 'B'){                            // case 3
                    w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(D, w);
                    w = x->parent->right;
                }
                                                                        // case 4
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                leftRotate(D, x->parent);
                x = D->root;
            }
        }
        else{
            w = x->parent->left;
            if (w->color == 'R'){                                       // case 5
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(D, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 'B' && w->left->color == 'B'){       // case 6
                w->color = 'R';
                x = x->parent;
            }
            else{
                if (w->left->color == 'B'){                             // case 7
                    w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(D, w);
                    w = x->parent->left;
                }
                                                                        // case 8
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                rightRotate(D, x->parent);
                x = D->root;
            }
        }
    }
    x->color = 'B';
}

// RB_transplant()
// Transplants node u and node v in a Red Black tree
void RB_transplant(Dictionary D, Node u, Node v){
    if (u->parent == D->NIL){
        D->root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// preOrderDictWalk()
// writes the keys of the dict in pre order to the designated file
void preOrderDictWalk(FILE* out, Dictionary D, Node x){
    if (x != D->NIL){
        fprintf(out, KEY_FORMAT, x->key);
        preOrderDictWalk(out, D, x->left);
        preOrderDictWalk(out, D, x->right);
    }
}

// inOrderDictWalk()
// writes the keys of the dict in order to the designated file
void inOrderDictWalk(FILE* out, Dictionary D, Node x){
    if (x != D->NIL){
        inOrderDictWalk(out, D, x->left);
        fprintf(out, KEY_FORMAT, x->key);
        inOrderDictWalk(out, D, x->right);
    }
}

// postOrderDictWalk()
// writes the keys of the dict in post order to the designated file
void postOrderDictWalk(FILE* out, Dictionary D, Node x){
    if (x != D->NIL){
        postOrderDictWalk(out, D, x->left);
        postOrderDictWalk(out, D, x->right);
        fprintf(out, KEY_FORMAT, x->key);
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
        if (KEY_CMP(z->key, x->key) < 0){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    z->parent = y;
    if (y == D->NIL){
        D->root = z;
    }
    else if (KEY_CMP(z->key, y->key) < 0){
        y->left = z;
    }
    else{
        y->right = z;
    }

    z->left = D->NIL;
    z->right = D->NIL;
    z->color = 'R';
    RB_InsertFixeUp(D, z);
    D->size++;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling insert() on a NULL Dictionary reference\n");
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

    Node x;
    Node y = z;
    char y_original_color = y->color;

    if (z->left == D->NIL){
        x = z->right;
        RB_transplant(D, z, z->right);
    }
    else if (z->right == D->NIL){
        x = z->left;
        RB_transplant(D, z, z->left);
    }
    else{
        y = dictMin(D, z->right);
        y_original_color = y->color;            // doesn't it already = y->color????????????????????????
        x = y->right;
        if (y->parent == z){
            x->parent = y;
        }
        else{
            RB_transplant(D, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_transplant(D, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == 'B'){
        RB_deleteFixUp(D, x);
    }

    if (z == D->current){                // if were deleting the current node, current = nil
        D->current = D->NIL;
    }
    freeNode(&z);
    D->size--;
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling insert() on a NULL Dictionary reference\n");
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
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printDictionary(FILE* out, Dictionary D, const char* ord){
    if (D == NULL){
        fprintf(stderr, "Dictionary Error: Calling printDictionary() on a NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(ord, "pre") == 0){
        preOrderDictWalk(out, D, D->root);
    }
    else if(strcmp(ord, "in") == 0){
        inOrderDictWalk(out, D, D->root);
    }
    else if(strcmp(ord, "post") == 0){
        postOrderDictWalk(out, D, D->root);
    }
}
