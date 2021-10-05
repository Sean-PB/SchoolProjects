/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa2
* FindPath.c
* Client file for Finding the shortest path and Graph ADT
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 100

int main(int argc, char* argv[]){

        FILE *in, *out;
        char line[MAX_LEN];
        char * dummyLine = "0 0\n";
        Graph G;
        List path;

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
            addEdge(G, x, y);
        }


        // Open output file for writing
        out = fopen(argv[2], "w");
        if(out==NULL){
            printf("Unable to open file %s for writing\n", argv[2]);
            exit(1);
        }

        // print the adjacency list representation
        printGraph(out, G);

         // Do a BFS and getPath for each vert
        path = newList();

        while(strcmp(fgets(line, MAX_LEN, in), dummyLine) != 0){
            clear(path);
            sscanf(line, "%d %d", &x, &y);
            BFS(G, x);
            getPath(path, G, y);
            if(getDist(G, y) == -1){
                fprintf(out, "\nThe distance from %d to %d is infinity\n", x, y);
                fprintf(out, "No %d-%d path exists\n", x, y);
            }
            else{
                fprintf(out, "\nThe distance from %d to %d is %d\n", x, y, getDist(G, y));
                fprintf(out, "A shortest %d-%d path is: ", x, y);
                printList(out, path);
                fprintf(out, "\n");
            }
        }

        // close IO files
        fclose(in);
        fclose(out);

        // free graph and list
        freeGraph(&G);
        freeList(&path);

}
