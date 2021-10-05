/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa6
* Lex.c
* Client file for Dictionary ADT
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 500

int main(int argc, char* argv[]){

    int wordCount;
    FILE *in, *out;
    char line[MAX_LEN];
    Dictionary dict = NULL;

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
    // Open output file for writing
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
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
    char** wordArray = calloc(wordCount, sizeof(char*));
    int i = 0;
    while(fgets(line, MAX_LEN, in)){
        wordArray[i] = calloc(MAX_LEN, sizeof(char));
        strcpy(wordArray[i], line);
        i++;
    }


    // Indirectly sort wordArray with Dictionary
    dict = newDictionary(0);
    // for every element in the wordArray starting at index 0...
    for (int i = 0; i < wordCount; i++){
        insert(dict, wordArray[i], i);
    }

    // Write the words to the file in the order of the sortedList
    for (beginForward(dict); currentVal(dict) != VAL_UNDEF; next(dict)){
        fprintf(out, KEY_FORMAT, currentKey(dict));
    }


    // close files
    fclose(in);
    fclose(out);

    // free sortedList
    freeDictionary(&dict);

    // free wordArray
    for (int i = 0; i < wordCount; i++){
        free(wordArray[i]);
    }
    free(wordArray);

}
