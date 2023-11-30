#include <sstream>
#include <iostream>
#include <stdlib.h>  
#include <stdio.h> 
#include <iomanip>
#include "graph.h"
#include "minheap.h"
using namespace std;
const double DOUBLE_MAX = 99999999.0;

Graph::Graph() {
    // Constructor implementation
   
    // set variables to default values
    // Initialize numVertices, numEdges, and isDirected
    numVertices = 0;
    numEdges = 0;
    isDirected = false;
    source = -1;
    graphTraversed = false;
    fullTraversal = false;
     // set pointers to nullptr
    adjacencyLists = nullptr;
    extractedVertices = nullptr;
    relaxedVertices = nullptr;
    predecessor = nullptr;
    distance = nullptr;

}

Graph::~Graph() {
    // Destructor implementation
    // deallocate memory for arrays
    
    // Free the vector of adjacency lists
    if (extractedVertices != nullptr) {
        delete[] extractedVertices;
    }
    if (relaxedVertices != nullptr) {
        delete[] relaxedVertices;
    }
    if (predecessor != nullptr) {
        delete[] predecessor;
    }
    if (distance != nullptr) {
        delete[] distance;
    }
    // Free individual adjacency lists
    if (adjacencyLists != nullptr) {
        for (int i = 0; i < numVertices; ++i) {
            if (adjacencyLists[i] != nullptr) {
                delete[] adjacencyLists[i];
            }
        }
        delete[] adjacencyLists;
    }


}

bool Graph::loadGraph(const string& filename, const string& direction) {
    
   
}

void Graph::runDijkstra(int newSource, int destination, int flag) {
   
}

void Graph::printAdjacencyLists() {
   
  

}
