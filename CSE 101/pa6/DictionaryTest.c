/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa6
* DictionaryTest.c
* Tests Dictionary operations in isolation
***************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){
    Dictionary A = newDictionary(0);                        // newDictionary()
    Dictionary B = newDictionary(1);

    if (getUnique(A) != 0 || getUnique(B) != 1){            // getUnique()
        printf("getUnique() failed\n");
    }

    insert(A, "b", 1);                                      // insert()
    insert(A, "a", 2);
    insert(A, "c", 3);

    if (size(A) != 3 || size(B) != 0){                      // size()
        printf("size() failed\n");
    }

    if (lookup(A, "a") != 2 || lookup(A, "b") != 1){        // lookup
        printf("lookup() failed\n");
    }

    printf("Dictionary A: ");
    printDictionary(stdout, A);                             // printDictionary()

    printf("Delete 'c' from A\n");
    delete(A, "c");                                         // delete()

    printf("Dictionary A: ");
    printDictionary(stdout, A);

    insert(B, "x", 4);
    insert(B, "y", 6);
    printf("Dictionary B: ");
    printDictionary(stdout, B);

    printf("makeEmpty Dictionary B\n");
    makeEmpty(B);                                           // makeEmpty()

    printf("Dictionary B: \n");
    printDictionary(stdout, B);

    insert(B, "x", 4);
    insert(B, "y", 6);
    insert(B, "t", 12);

    printf("2\n1\n=\n");
    // beginForward(), currentVal(), next()
    for (beginForward(A); currentVal(A) != VAL_UNDEF; next(A)){
        printf(VAL_FORMAT, currentVal(A));
        printf("\n");
    }

    printf("\n6\n4\n12\n=\n");
    // beginReverse(), currentKey(), prev()
    for(beginReverse(B); currentKey(B) != KEY_UNDEF; prev(B)){
        printf(VAL_FORMAT, currentVal(B));
        printf("\n");
    }

    freeDictionary(&A);                                     // freeDictionary()
    freeDictionary(&B);

}
