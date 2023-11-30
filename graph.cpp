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
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open the graph file." << endl;
        return false;
    }

    string line;
    if (!getline(file, line)) {
        cout << "Input file is empty." << endl;
        return false;
    }

    istringstream iss(line);
    int n, m;
    if (!(iss >> n >> m)) {
        cout << "Invalid format for the first line in the input file." << endl;
        return false;
    }
    numVertices = n + 1;
    numEdges = m;

    adjacencyLists = new Edge*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjacencyLists[i] = nullptr;
    }

    extractedVertices = (double*)malloc(numVertices * sizeof(double));
    relaxedVertices = (double*)malloc(numVertices * sizeof(double));
    predecessor = (int*)malloc(numVertices * sizeof(int));
    distance = (double*)malloc(numVertices * sizeof(double));

    for (int i = 0; i < numVertices; ++i) {
        extractedVertices[i] = -1.0;
        relaxedVertices[i] = -1.0;
        predecessor[i] = -1;
        distance[i] = DOUBLE_MAX;
    }

    file.close();
    file.open(filename);
    getline(file, line);

    while (getline(file, line)) {
        istringstream edgeIss(line);
        int edgeId, startNode, endNode;
        double weight;
        if (!(edgeIss >> edgeId >> startNode >> endNode >> weight)) {
            cout << "Invalid format for edge in the input file." << endl;
            return false;
        }
        startNode++;
        endNode++;

        if (startNode > numVertices || endNode > numVertices || startNode < 1 || endNode < 1) {
            cout << "Invalid node IDs in the input file." << endl;
            return false;
        }

        Edge* edge = new Edge;
        edge->destination = endNode;
        edge->weight = weight;

        if (adjacencyLists[startNode] == nullptr) {
            adjacencyLists[startNode] = new Edge[numEdges];
        }

        int j = 0;
        while (adjacencyLists[startNode][j].destination != 0) {
            j++;
        }
        adjacencyLists[startNode][j] = *edge;

        if (direction == "undirected") {
            Edge* reverseEdge = new Edge;
            reverseEdge->destination = startNode;
            reverseEdge->weight = weight;

            if (adjacencyLists[endNode] == nullptr) {
                adjacencyLists[endNode] = new Edge[numEdges];
            }

            j = 0;
            while (adjacencyLists[endNode][j].destination != 0) {
                j++;
            }
            adjacencyLists[endNode][j] = *reverseEdge;
            delete reverseEdge;
        }
        delete edge;
    }

    isDirected = (direction == "directed");
    file.close();
    return true;
    
   
}

void Graph::runDijkstra(int newSource, int destination, int flag) {
   
}

void Graph::printAdjacencyLists() {
   
  

}
