/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa2
* GraphTest.c
* Tests Graph operations in isolation
***************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
    Graph test = newGraph(3);       // newgraph
    addEdge(test, 1, 2);            // addEdge
    addEdge(test, 2, 3);            // addEdge
    addArc(test, 1, 3);             // addArc
    addArc(test, 3, 1);             // addArc

    printf("getOrder test: ");
    if(getOrder(test) != 3){        // getOrder
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    printf("getSize test 1: ");
    if(getSize(test) != 4){         // getSize
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    makeNull(test);                 // makeNull

    printf("getSize test 2: ");
    if(getSize(test) != 0){         // getSize
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    addEdge(test, 1, 2);            // addEdge
    addEdge(test, 2, 3);            // addEdge
    addArc(test, 1, 3);             // addArc
    addArc(test, 3, 1);             // addArc

    printGraph(stdout, test);       // printGraph

    BFS(test, 2);                   // BFS

    printf("getSource test: ");
    if(getSource(test) != 2){       // getSource
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    printf("getParent test: ");
    if(getParent(test, 1) != 2){    // getParent
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    printf("getDist test: ");
    if(getDist(test, 3) != 1){      // getDist
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    List listTest = newList();
    List listTest2 = newList();
    append(listTest2, 2);
    append(listTest2, 3);
    getPath(listTest, test, 3);     // getPath
    printf("getPath test: ");
    if(!equals(listTest, listTest2)){
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    freeGraph(&test);                // freeGraph
    freeList(&listTest);
    freeList(&listTest2);
}
