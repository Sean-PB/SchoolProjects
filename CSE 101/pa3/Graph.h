/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa3
* Graph.h
* Header file for Graph ADT
***************************************************************************************************/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#define INF -1
#define UNDEF -2
#define NIL 0

#include <stdio.h>
#include "List.h"

//---------------------------------------- Exported type -------------------------------------------
typedef struct GraphObj* Graph;

//------------------------------------ Constructors-Destructors ------------------------------------

// newGraph()
// Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and
// no edges.
Graph newGraph(int n);

// freeGraph()
// Frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG);

//----------------------------------- Access functions ---------------------------------------------

// getOrder()
// returns order of G
int getOrder(Graph G);

// getSize()
// Returns the size G
int getSize(Graph G);

// getSource()
// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been
// called.
int getSource(Graph G);

// getParent()
// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not
// yet been called.
// Pre: 1≤ u ≤ getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the discover time of the vertex u.
// Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time of the vertex u.
// Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet
// been called.
// Pre: 1≤ u ≤ getOrder(G)
int getDist(Graph G, int u);

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the
// value NIL if no such path exists.
// Pre:  getSource(G)!=NIL, so BFS() must be called before getPath().
// Pre: 1≤ u ≤ getOrder(G)
void getPath(List L, Graph G, int u);

//------------------------------------- Manipulation procedures ------------------------------------

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the
// adjacency List of u. This is done in order by increasing labels.
// Pre: 1 <= u,v <= getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to
// the adjacency List of v).
// Pre: 1 <= u,v <= getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and
// source fields of G accordingly.
void BFS(Graph G, int s);

// DFS()
// Preforms Depth First Search algorithm on G.
// Pre: length(S) == getOrder(G), S contains some permutation of the integers {1,2,...,getOrder(G)}
void DFS(Graph G, List S);

//--------------------------------------- Other operations -----------------------------------------

// transpose()
// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

// copyGraph()
// Returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G);

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif
