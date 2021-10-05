/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa3
* GraphTest.c
* Tests Graph operations in isolation
***************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
    Graph test = newGraph(6);                               // newgraph
    addEdge(test, 1, 2);                                    // addEdge
    addEdge(test, 2, 3);                                    // addEdge
    addArc(test, 1, 3);                                     // addArc
    addArc(test, 3, 1);                                     // addArc

    printf("getOrder test: ");
    if(getOrder(test) != 6){                                // getOrder
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    printf("getSize test 1: ");
    if(getSize(test) != 4){                                 // getSize
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    makeNull(test);                                         // makeNull

    printf("getSize test 2: ");
    if(getSize(test) != 0){                                 // getSize
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    addEdge(test, 1, 2);                                    // addEdge
    addEdge(test, 2, 3);                                    // addEdge
    addArc(test, 1, 3);                                     // addArc
    addArc(test, 3, 1);                                     // addArc

    printf("Graph:\n");
    printGraph(stdout, test);                               // printGraph

    BFS(test, 2);                                           // BFS

    printf("getSource test: ");
    if(getSource(test) != 2){                               // getSource
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    printf("getParent test: ");
    if(getParent(test, 1) != 2){                            // getParent
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    printf("getDist test: ");
    if(getDist(test, 3) != 1){                              // getDist
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    List listTest = newList();
    List listTest2 = newList();
    append(listTest2, 2);
    append(listTest2, 3);
    getPath(listTest, test, 3);                             // getPath
    printf("getPath test: ");
    if(!equals(listTest, listTest2)){
        printf("failed\n");
    }
    else{
        printf("passed\n");
    }

    makeNull(test);                                         // makeNull

    addArc(test, 1, 2);
    addArc(test, 1, 3);
    addArc(test, 2, 1);
    addArc(test, 2, 4);
    addArc(test, 2, 5);
    addArc(test, 2, 6);
    addArc(test, 3, 1);
    addArc(test, 3, 4);
    addArc(test, 4, 2);
    addArc(test, 4, 3);
    addArc(test, 4, 5);
    addArc(test, 5, 2);
    addArc(test, 5, 4);
    addArc(test, 5, 6);
    addArc(test, 6, 2);
    addArc(test, 6, 5);

    Graph graphT = transpose(test);                         // transpose
    Graph graphCopy = copyGraph(test);                      // copyGraph
    printf("Graph:\n");
    printGraph(stdout, test);
    printf("Graph copy:\n");
    printGraph(stdout, graphCopy);
    printf("Graph transpose:\n");
    printGraph(stdout, graphT);

    List S = newList();
    append(S, 1);
    append(S, 2);
    append(S, 3);
    append(S, 4);
    append(S, 5);
    append(S, 6);

    addArc(test, 1, 2);
    addArc(test, 1, 3);
    addArc(test, 2, 1);
    addArc(test, 2, 4);
    addArc(test, 2, 5);
    addArc(test, 2, 6);
    addArc(test, 3, 1);
    addArc(test, 3, 4);
    addArc(test, 4, 2);
    addArc(test, 4, 3);
    addArc(test, 4, 5);
    addArc(test, 5, 2);
    addArc(test, 5, 4);
    addArc(test, 5, 6);
    addArc(test, 6, 2);
    addArc(test, 6, 5);

    DFS(test, S);                                           // DFS

    printf("Discover of 1: %d\n", getDiscover(test, 1));    // getDiscover
    printf("Finish of 1: %d\n", getFinish(test, 1));        // getFinish
    printf("Discover of 3: %d\n", getDiscover(test, 3));    // getDiscover
    printf("Finish of 3: %d\n", getFinish(test, 3));        // getFinish
    printf("Discover of 5: %d\n", getDiscover(test, 5));    // getDiscover
    printf("Finish of 5: %d\n", getFinish(test, 5));        // getFinish
    printf("Discover of 6: %d\n", getDiscover(test, 6));    // getDiscover
    printf("Finish of 6: %d\n", getFinish(test, 6));        // getFinish

    freeGraph(&test);                                       // freeGrap
    freeGraph(&graphCopy);
    freeGraph(&graphT);
    freeList(&S);
    freeList(&listTest);
    freeList(&listTest2);
}
