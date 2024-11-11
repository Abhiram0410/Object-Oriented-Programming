#include <iostream>
#include <climits> // For INT_MAX
using namespace std;
struct Edge{
    int src,dst,wt;
};
const int MAX_V=100;
Edge edges[MAX_V*MAX_V];
int V,E;
int value[MAX_V];

void bellmanFord() {
    for (int i = 0; i < V; ++i) value[i] = INT_MAX; 
    value[0] = 0; 
    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int U = edges[j].src;
            int V = edges[j].dst;
            int wt = edges[j].wt;
            if (value[U] != INT_MAX && value[U] + wt < value[V]) {
                value[V] = value[U] + wt;
            }
        }
    }
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
        if (value[i] == INT_MAX) {
            cout << "Vertex " << i << " is unreachable from the source." << endl;
        } else {
            cout << "Cost to reach vertex " << i << " from source 0: " << value[i] << "\n";
        }
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
