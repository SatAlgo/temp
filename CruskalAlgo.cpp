#include <iostream>
#include <cstdlib> // for qsort
using namespace std;

// Edge structure
class Edge {
public:
    int src, dest, weight;
};

// Graph structure
class Graph {
public:
    int V, E;
    Edge* edge;
};

// Subset structure for Union-Find
class Subset {
public:
    int parent;
    int rank;
};

// Function to create a graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

// Find function with path compression
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent); // Path compression
    }
    return subsets[i].parent;
}

// Union function by rank
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Union by rank
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparison function to sort edges in increasing order of weight
int myComp(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight - b1->weight;
}

// Kruskal's algorithm to find the Minimum Spanning Tree (MST)
void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];  // To store the resultant MST
    int e = 0;       // Index for result[]
    int i = 0;       // Initial index of sorted edges

    // Sort all the edges in increasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    // Allocate memory for creating V subsets
    Subset* subsets = new Subset[V];

    // Initialize subsets
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Process edges and construct the MST
    while (e < V - 1 && i < graph->E) {
        // Pick the smallest edge
        Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, include it in the result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the constructed MST
    cout << "Constructed MST: \n";
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
        minimumCost += result[i].weight;
    }

    cout << "Minimum Cost Spanning Tree: " << minimumCost << endl;

    // Clean up
    delete[] subsets;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph* graph = createGraph(V, E);

    cout << "Enter the edges (src dest weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> graph->edge[i].src >> graph->edge[i].dest >> graph->edge[i].weight;
    }

    KruskalMST(graph);

    delete[] graph->edge;
    delete graph;

    return 0;
}
