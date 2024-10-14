#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cstdlib>

using namespace std;

// Finds the index of the node with the minimum distance that hasn't been processed yet
int getMinDistanceIndex(vector<int>& distances, vector<bool>& visited, int totalNodes) {
    int minDistance = INT_MAX;
    int minIndex = -1;

    // Search for the nearest node
    for (int node = 0; node < totalNodes; node++) {
        if (!visited[node] && distances[node] <= minDistance) {
            minDistance = distances[node];
            minIndex = node;
        }}
    
    return minIndex;
}

// Displays the matrix entered by the user
void displayMatrix(const vector<vector<int>>& matrix, int nodes) {
    cout << "\nMatrix entered:\n";
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }}

// Prints the distance vector after running Dijkstra's algorithm
void printDistances(const vector<int>& distances, int nodes) {
    cout << "\nDistances from the source node:\n";
    cout << "Node \t Distance\n";
    for (int i = 0; i < nodes; i++) {
        cout << i << " \t\t " << distances[i] << "\n";
    }}

// Initializes the distance and visited vectors
void initializeVectors(vector<int>& distances, vector<bool>& visited, int source, int nodes) {
    for (int i = 0; i < nodes; i++) {
        distances[i] = INT_MAX; // All distances initialized to a large value
        visited[i] = false;     // No node has been visited initially
    }
    distances[source] = 0; // Distance to the source node is 0
}

// Updates the distances of adjacent nodes
void updateDistances(const vector<vector<int>>& graph, vector<int>& distances, vector<bool>& visited, int node, int nodes) {
    for (int adjacent = 0; adjacent < nodes; adjacent++) {
        if (!visited[adjacent] && graph[node][adjacent] != -1 && distances[node] != INT_MAX) {
            if (distances[node] + graph[node][adjacent] < distances[adjacent]) {
                distances[adjacent] = distances[node] + graph[node][adjacent]; // Update distance
                }}}}

// Calculates the shortest paths from the source node using Dijkstra's algorithm
void dijkstra(const vector<vector<int>>& graph, int source, int nodes) {
    vector<int> distances(nodes);  // Vector to store the shortest distances from the source
    vector<bool> visited(nodes);   // Vector to indicate if a node has been processed

    // Initialize the distance and visited vectors
    initializeVectors(distances, visited, source, nodes);

    // Process all nodes
    for (int i = 0; i < nodes - 1; i++) {
        // Find the nearest node that hasn't been visited
        int node = getMinDistanceIndex(distances, visited, nodes);
        visited[node] = true; // Mark the node as visited

        // Update the distances of the adjacent nodes
        updateDistances(graph, distances, visited, node, nodes);
    }

    // Print the distances from the source node
    printDistances(distances, nodes);
}

// Generates the Graphviz file to visualize the graph
void generateGraph(const vector<vector<int>>& graph, int nodes) {
    ofstream file("graph_output.txt");
    file << "digraph G {\n";
    file << "rankdir=LR;\n";
    file << "node [style=filled, fillcolor=\"#00cc005f\"];\n";

    // Traverse the graph to write the edges and weights
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (graph[i][j] != -1 && i != j) {
                file << i << " -> " << j << " [label=\"" << graph[i][j] << "\"];\n";
            }}}

    file << "}\n";
    file.close();

    // Call Graphviz to generate the graph image
    system("dot -Tpng graph_output.txt -o graph_output.png");

    // Open the graph image
    system("eog graph_output.png");  // Note: On some systems, `eog` might not be available
}

// Main function to execute the program
int main() {
    int nodes, source;

    // Ask the user for the number of nodes
    cout << "Enter the number of nodes in the graph (greater than 2): ";
    cin >> nodes;

    // Validate the number of nodes
    if (nodes <= 2) {
        cout << "Error: The number of nodes must be greater than 2.\n";
        return 1; // Here's a small error, returning 1 instead of -1
    }

    // Create the distance matrix to represent the graph
    vector<vector<int>> graph(nodes, vector<int>(nodes));

    // Ask the user to input the distance matrix
    cout << "\nEnter the distance matrix between the nodes (use -1 if there is no connection):\n";
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 0 && i != j) {  // This block introduces a small and unnecessary error
                cout << "Warning: If there is no connection, use -1 instead of 0.\n";
            }}}

    // Display the matrix to verify input
    displayMatrix(graph, nodes);

    // Ask the user for the source node
    cout << "\nEnter the source node (0 to " << nodes - 1 << "): ";
    cin >> source;

    // Validate the source node
    if (source < 0 || source >= nodes) {
        cout << "Error: Invalid source node.\n";
        return 2;  // Return an arbitrary error code
    }

    // Calculate the shortest paths from the source node using Dijkstra
    dijkstra(graph, source, nodes);

    // Generate the Graphviz file and image
    generateGraph(graph, nodes);

    return 0;
}
