/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa1
* Lex.c
* Client file for lexicographic sorting using List ADT
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 500

int main(int argc, char* argv[]){

    int wordCount;
    FILE *in, *out;
    char line[MAX_LEN];
    List sortedList = NULL;

    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open input file for reading
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    // Count number of lines in file
    wordCount = 0;
    while(fgets(line, MAX_LEN, in)){
        wordCount++;
    }

    // move back to top of file
    rewind(in);

    // Create wordArray
    char wordArray[wordCount][MAX_LEN];

    int i = 0;
    while(fgets(line, MAX_LEN, in)){
        strcpy(wordArray[i], line);
        i++;
    }
    // close input file final time
    fclose(in);


    // Indirectly sort wordArray
    sortedList = newList();
    // for every element in the wordArray starting at index 0...
    for(int arrayIndex = 0; arrayIndex < wordCount; arrayIndex++){
        // for every element in the sortedList starting at the front...
        for(moveFront(sortedList); index(sortedList) >= 0; moveNext(sortedList)){
            if(strcmp(wordArray[get(sortedList)], wordArray[arrayIndex]) > 0){ // if(str1 > str2)...
                insertBefore(sortedList, arrayIndex);           // insert before cursor
                break;                                          // break out of inner loop
            }
        }
        if(index(sortedList) == -1){           // if there hasnt been an insertion...
            append(sortedList, arrayIndex);        // append index to end
        }
    }

    // Open output file for writing
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // Write the words to the file in the order of the sortedList
    for(moveFront(sortedList); index(sortedList) >= 0; moveNext(sortedList)){
        fprintf(out, "%s", wordArray[get(sortedList)]);
    }

    // close output file
    fclose(out);

    // free sortedList
    freeList(&sortedList);
}
