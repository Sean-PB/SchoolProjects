/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa7
* DictionaryTest.c
* Tests Dictionary operations in isolation
***************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){

    int val = 333;

    Dictionary A = newDictionary(0);                                // newDictionary()
    Dictionary B = newDictionary(1);

    insert(A, "a", (&val));                                           // insert()
    insert(A, "b", (&val));
    insert(A, "c", (&val));
    insert(A, "d", (&val));

    printf("Dictionary A in order:\na\nb\nc\nd\n==\n");
    printDictionary(stdout, A, "in");                               // printDictionary()

    if (size(A) != 4){                                              // size()
        printf("size() failed\n");
    }

    if (getUnique(A) != 0){                                         // getUnique()
        printf("getUnique() failed\n");
    }

    if (lookup(A, "b") == VAL_UNDEF){                               // lookup()
        printf("lookup() failed\n");
    }

    insert(B, "z", (&val));
    insert(B, "y", (&val));
    insert(B, "x", (&val));

    delete(B, "x");                                                 // delete()
    if (size(B) != 2){
        printf("delete failed\n");
    }

    printf("Dictionary A:\n");
    // beginForward(), currentKey(), next()
    for (beginForward(A); currentKey(A) != KEY_UNDEF; next(A)){
        printf(""KEY_FORMAT"\n", currentKey(A));
    }

    printf("Dictionary B in reverse:\n");
    // beginReverse(), prev()
    for (beginReverse(B); currentKey(B) != KEY_UNDEF; prev(B)){
        printf(""KEY_FORMAT"\n", currentKey(B));
    }

    if (currentVal(A) != NULL){                                     // currentVal()
        printf("currentVal() failed\n");
    }

    makeEmpty(B);                                                   // makeEmpty()
    if (size(B) != 0){
        printf("delete failed\n");
    }

    freeDictionary(&A);                                             // freeDictionary()
    freeDictionary(&B);

}
