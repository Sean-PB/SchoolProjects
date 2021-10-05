/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa3
* FindComponents.c
* Client file for finding the strongly connected componets of a graph
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 100

int main(int argc, char* argv[]){

        FILE *in, *out;
        char line[MAX_LEN];             // for file reading
        char * dummyLine = "0 0\n";     // for file reading
        Graph G;                        // original Graph
        Graph T;                        // transpose of G
        List S;                         // stack
        List components;                // for keeping track of the components in a tree

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

        // create Graph
        G = newGraph(atoi(fgets(line, MAX_LEN, in)));

        // Add all edges to G
        int x, y;
        while(strcmp(fgets(line, MAX_LEN, in), dummyLine) != 0){
            sscanf(line, "%d %d", &x, &y);
            addArc(G, x, y);
        }


        // Open output file for writing
        out = fopen(argv[2], "w");
        if(out==NULL){
            printf("Unable to open file %s for writing\n", argv[2]);
            exit(1);
        }

        // print the adjacency list representation
        fprintf(out, "Adjacency list representation of G:\n");
        printGraph(out, G);


        S = newList();
        for(int i = 1; i <= getOrder(G); i++){  // in order
            append(S, i);
        }

        DFS(G, S);                  // call DFS(G) to compute finishing times for each vertex

        T = transpose(G);           // compute the transpose of G

        DFS(T, S);                  // call DFS(T) again with new order

        // print componets
        int numOfComponents = 0;
        for(int i = 1; i <= getOrder(G); i++){
            if(getParent(T, i) == NIL){
                numOfComponents++;
            }
        }

        fprintf(out, "\nG contains %d strongly connected components:", numOfComponents);

        components = newList();
        moveBack(S);
        for(int i = 1; index(S) != -1; movePrev(S)){
            prepend(components, get(S));
            if(getParent(T, get(S)) == NIL){
                fprintf(out, "\nComponent %d: ", i++);
                printList(out, components);
                clear(components);
            }
        }

        // close IO files
        fclose(in);
        fclose(out);

        // free graph
        freeGraph(&G);
        freeGraph(&T);
        freeList(&S);
        freeList(&components);
}
