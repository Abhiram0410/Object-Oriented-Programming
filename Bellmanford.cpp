#include <iostream>
#include <climits> // For INT_MAX
using namespace std;
struct Edge {
    int src, dst, wt;
};
const int MAX_V = 100; // Maximum number of vertices
Edge edges[MAX_V * MAX_V]; // Edge list can be at most V*(V-1) for a directed graph
int V, E; // Number of vertices and edges
int value[MAX_V]; // To store the minimum cost to reach each vertex
void relax(int iteration) {
    bool updated = false;
    for (int j = 0; j < E; ++j) {
        int U = edges[j].src;
        int V = edges[j].dst;
        int wt = edges[j].wt;
        if (value[U] != INT_MAX && value[U] + wt < value[V]) {
            value[V] = value[U] + wt;
            updated = true;
        }
    }
    if (iteration < V - 1 && updated) {
        relax(iteration + 1);
    }
}
void bellmanFord() {
    for (int i = 0; i < V; ++i) value[i] = INT_MAX; 
    value[0] = 0; 
    relax(0);
    for (int j = 0; j < E; ++j) {
        int U = edges[j].src;
        int V = edges[j].dst;
        int wt = edges[j].wt;
        if (value[U] != INT_MAX && value[U] + wt < value[V]) {
            cout << "Graph contains a negative-weight cycle" << endl;
            return;
        }
    }
    for (int i = 1; i < V; ++i) {
        cout << "Cost to reach vertex " << i << " from source 0: " << value[i] << "\n";
    }
}
int main() {
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
    cout << "Enter edges (src dst wt):" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].src >> edges[i].dst >> edges[i].wt;
    }
    bellmanFord(); 
    return 0;
}