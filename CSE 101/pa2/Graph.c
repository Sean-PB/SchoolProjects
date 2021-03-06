/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa2
* Graph.c
* Implementation file for Graph ADT
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

//------------------------------------------- Structs ----------------------------------------------
typedef struct GraphObj{
    List* adj;
    char* color;
    int* parent;
    int* dist;
    int order;
    int size;
    int source;
} GraphObj;

//------------------------------------ Constructors-Destructors ------------------------------------

// newGraph()
// Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and
// no edges.
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    if(G == NULL){
        fprintf(stderr, "Graph Error: newGraph() malloc'ed a NULL Graph");
        exit(EXIT_FAILURE);
    }
    G->adj = calloc(n+1, sizeof(List));
    for(int i = 1; i < n+1; i++){
        G->adj[i] = newList();
    }
    G->color = calloc(n+1, sizeof(char));
    G->parent = calloc(n+1, sizeof(int));
    G->dist = calloc(n+1, sizeof(int));
    G->order = n;  // number of vertices
    G->size = 0;  // number of edges
    G->source = NIL;
    return(G);
}

// freeGraph()
// Frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 0; i < (*pG)->order + 1; i++){
            freeList(&((*pG)->adj[i]));
        }
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->dist);
        free(*pG);
        *pG = NULL;
    }
}

//----------------------------------- Access functions ---------------------------------------------

// getOrder()
// returns order of G
int getOrder(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    return(G->order);
}

// getSize()
// Returns the size G
int getSize(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    return(G->size);
}

// getSource()
// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been
// called.
int getSource(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    return(G->source);
}

// getParent()
// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not
// yet been called.
// Pre: 1 ??? u ??? G->order
int getParent(Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > G->order){
        fprintf(stderr, "Graph Error: calling getParent() on with a non-existant vertex\n");
        exit(EXIT_FAILURE);
    }

    if(G->source == NIL){
        return(NIL);
    }
    return(G->parent[u]);
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet
// been called.
// Pre: 1 ??? u ??? G->order
int getDist(Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > G->order){
        fprintf(stderr, "Graph Error: calling getDist() on with a non-existant vertex\n");
        exit(EXIT_FAILURE);
    }

    if(G->source == NIL){
        return(INF);
    }
    return(G->dist[u]);
}

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the
// value NIL if no such path exists.
// Pre:  getSource(G)!=NIL,    ( BFS() must be called before getPath() )
// Pre: 1 ??? u ??? G->order
void getPath(List L, Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(L == NULL){
        fprintf(stderr, "Graph Error: calling getPath() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G) == NIL){
        fprintf(stderr, "Graph Error: calling getPath() before calling BFS()\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > G->order){
        fprintf(stderr, "Graph Error: calling getPath() on with a non-existant vertex\n");
        exit(EXIT_FAILURE);
    }

    if(G->parent[u] == NIL){
        if(u == G->source){
            append(L, u);
        }
        else{
            append(L, NIL);
        }
    }
    else{
        for(int x = u; x != G->source; x = G->parent[x]){
            prepend(L, x);
        }
        prepend(L, G->source);
    }
}

//------------------------------------- Manipulation procedures ------------------------------------

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i <= getOrder(G); i++){
        clear(G->adj[i]);
    }
    G->size = 0;
}

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the
// adjacency List of u. This is done in order by increasing labels.
// Pre: 1 <= u, v <= G->order
void addEdge(Graph G, int u, int v){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || v > G->order){
        fprintf(stderr, "Graph Error: calling addEdge() on a non-existant vertex\n");
        exit(EXIT_FAILURE);
    }

    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to
// the adjacency List of v).
// Pre: 1 <= u, v <= G->order
void addArc(Graph G, int u, int v){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || v > G->order){
        fprintf(stderr, "Graph Error: calling addArc() on a non-existant vertex\n");
        exit(EXIT_FAILURE);
    }

    // Loop through u and insert v in correct order
    for(moveFront(G->adj[u]); index(G->adj[u]) >= 0; moveNext(G->adj[u])){
        if(v < get(G->adj[u])){
            insertBefore(G->adj[u], v);
            break;
        }
    }
    // If v hasn't been inserted yet, append it
    if(index(G->adj[u]) == -1){
        append(G->adj[u], v);
    }
    G->size++;
}

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and
// source fields of G accordingly.
void BFS(Graph G, int s){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    int x, y;

    for(int i = 1; i <= G->order; i++){
        G->color[i] = 'W';
        G->dist[i] = INF;
        G->parent[i] = NIL;
    }
    G->source = s;         // assigning source
    G->color[s] = 'G';          // discover the source s
    G->dist[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();         // construct a new empty queue
    append(Q, s);
    while(length(Q) != 0){
        x = front(Q);
        deleteFront(Q);
        for(moveFront(G->adj[x]); index(G->adj[x]) >= 0; moveNext(G->adj[x])){
            y = get(G->adj[x]);
            if(G->color[y] == 'W'){       // y is undiscovered
                G->color[y] = 'G';           // discover y
                G->dist[y] = G->dist[x] + 1;
                G->parent[y] = x;
                append(Q, y);
            }
        }
        G->color[x] = 'B';             // finish x
    }
    freeList(&Q);            // free the queue we made earlier
}

//--------------------------------------- Other operations -----------------------------------------

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if(out == NULL){
        printf("Unable to open file for writing\n");
        exit(1);
    }
    for(int i = 1; i <= G->order; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}
