// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define MAX_SIZE 10000

/* 
    You will submit only this one file.

    Implement the function "rankPopularity" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

/*
    Notes:

    Time/Space complexities: 
        Let n = number of vertices in graph

        DFS on adjacency matrix = O(n^2)

        Without hashtable overall O(n^2) * O(n) time
            calculating outDeg(v) = O(n)
            calculating inDeg(v) = O(n)
            O(1) space though
            - Check every node and see if it is adjacent to v
            - Can reduce to O(1) if we precalculate the in/outDeg(v) and store in hashtable
        
        With hashtable overall O(n^2) + O(n^2) time
            Creating table = O(n^2) time, O(n) space
            - For each vertex in the graph, calculate in/outDegree

        Trade O(n) extra space for O(1) access times
*/

double inDegree(Graph g, int v);  // O(n)
double outDegree(Graph g, int v);  // O(n)
void initInOutTable(Graph g, double *inTable, double *outTable); // O(n^2)
void dfs(Graph g, int src, int visited[MAX_SIZE], double *mnV, double *inTable, double *outTable); // O(n^2) * O(1)

/*
    How the function works:
    1. Create a hashtable of inDegree and outDegree for each vertex in the graph (O(n^2) time)
    2. Recursively DFS through the graph (O(n^2) time)
    3. If a node is being visited, calculate its rankPopularity and add it to the mnV array (O(1) time)

    Overall O(n^2)
*/

// Returns rankPopularity of each node visitable from src
void rankPopularity(Graph g, int src, double *mnV) {
    int visited[MAX_SIZE] = {0};

    // Create an inDegree and outDegree hashtable
    // key = vertex number, value = in/outDegree
    double inTable[MAX_SIZE] = {0};
    double outTable[MAX_SIZE] = {0};

    // Fills the inTable/outTable with indegree/outdegree respectively
    initInOutTable(g, inTable, outTable);

    // Fills the mnV arrray
    dfs(g, src, visited, mnV, inTable, outTable);
}

// Standard recursive DFS. Calculate rankPopularity at each recursive call
void dfs(Graph g, int src, int visited[MAX_SIZE], double *mnV, double *inTable, double *outTable) {

    // Set src as visited and calculate the rankPopularity
    visited[src] = 1;
    mnV[src] = inTable[src] / outTable[src]; 

    // DFS adjacent nodes
    for (int i = 0; i < g->nV; i++) {

        // If there is a path from src to i and i is unvisited
        if (adjacent(g, src, i) && visited[i] == 0) {
            dfs(g, i, visited, mnV, inTable, outTable);
        }
    }
}

void initInOutTable(Graph g, double *inTable, double *outTable) {
    for (int i = 0; i < g->nV; i++) {
        inTable[i] = inDegree(g, i);
        outTable[i] = outDegree(g, i);
    }
}

// Note: We could combine in/outDegree() and pass in an in/out parameter but I feel like it reduces readability
//  If I were maintaining this, I would make 1 function though
// Returns outDegree of v
double outDegree(Graph g, int v) {
    double outDeg = 0;

    for (int i = 0; i < g->nV; i++) {

        // If there is an edge from v to i
        if (adjacent(g, v, i))
            outDeg++;
    }

    return (outDeg == 0) ? 0.5 : outDeg;
}


// Returns inDegree of v
double inDegree(Graph g, int v) {

    double inDeg = 0;
    for (int i = 0; i < g->nV; i++) {

        // If there is an edge from i to v
        if (adjacent(g, i, v)) {
            inDeg++;
        }
    }
    return (inDeg == 0) ? 0.5 : inDeg;

}
