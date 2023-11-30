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
   // Initialize variables and data structures
    int n = numVertices;
    source = newSource;
    graphTraversed = true;
    fullTraversal = true;

    // Create arrays and data structures for Dijkstra's algorithm
    bool* extracted = (bool*)malloc(n * sizeof(bool));
    for (int i = 0; i < n; ++i) {
        extracted[i] = false;
        extractedVertices[i] = -1.0;
        relaxedVertices[i] = -1.0;
        predecessor[i] = -1;
        distance[i] = DOUBLE_MAX;
    }

    // Mark the source as extracted
    extracted[source] = true;

    // Initialize the MinHeap data structure
    minHeap.init(n);
    distance[source] = 0;
    minHeap.push(0, source);

    // If flag is set, print initial insertion
    if (flag == 1) {
        cout << std::fixed << std::setprecision(4) << "Insert vertex " << source << ", key=" << setw(12)  << distance[source] << endl;
    }

    // Main Dijkstra's algorithm loop
    while (!minHeap.empty()) {
        // Extract the minimum distance vertex from the MinHeap
        int u = minHeap.pop();

        // Mark the vertex as extracted
        extracted[u] = true;
        extractedVertices[u] = distance[u];

        // If flag is set, print deletion of vertex
        if (flag == 1) {
            cout << std::fixed << std::setprecision(4) << "Delete vertex " << u << ", key=" << setw(12) << distance[u] << endl;
        }

        // If the destination is reached, exit the loop
        if (u == destination) {
            break;
        }

        // Loop through the adjacency list of the current vertex
        if (adjacencyLists[u] != nullptr) {
            int j = 0;
            while (adjacencyLists[u][j].destination != 0) {
                // Extract neighbor information
                int v = adjacencyLists[u][j].destination;
                double w = adjacencyLists[u][j].weight;

                // If the neighbor is not extracted and relaxation is possible
                if (!extracted[v] && distance[u] + w < distance[v]) {
                    // Perform relaxation
                    double oldDistance = distance[v];
                    distance[v] = distance[u] + w;
                    predecessor[v] = u;
                    relaxedVertices[v] = distance[v];

                    // If flag is set, print decrease key operation
                    if (oldDistance != DOUBLE_MAX && flag == 1) {
                        cout  << "Decrease key of vertex " << v << ", from " << setw(12) << oldDistance << " to " << std::fixed << std::setprecision(4) << setw(12) << distance[v] << endl;
                    }

                    // Push the neighbor into the MinHeap
                    minHeap.push(distance[v], v);

                    // If flag is set, print insertion of vertex
                    if (flag == 1) {
                        cout << std::fixed << std::setprecision(4) << "Insert vertex " << v << ", key=" << setw(12) << distance[v] << endl;
                    }
                }
                j++;
            }
        }
    }

    // Handle vertices left in MinHeap after the main loop
    while (!minHeap.empty()) {
        int u = minHeap.pop();
        if (!extracted[u]) {
            fullTraversal = false;
        }
    }

    // Deallocate memory for extracted array
    free(extracted);
}

void Graph::printAdjacencyLists() {
   
  

}
