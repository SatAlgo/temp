#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;

struct Edge {
    int u, v, weight;
};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

int findParent(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = findParent(parent, parent[i]); // Path compression
    return parent[i];
}

void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = findParent(parent, x);
    int rootY = findParent(parent, y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

void printMST_Prim(int parent[], int graph[MAX][MAX], int V) {
    int minCost = 0;
    for (int i = 1; i < V; i++)
        minCost += graph[parent[i]][i];

    cout << "\nMinimum cost = " << minCost << endl;
    for (int i = 1; i < V; i++)
        cout << "Edge " << parent[i] + 1 << "-" << i + 1 << " -> " << graph[parent[i]][i] << endl;
}

void primMST(int graph[MAX][MAX], int V) {
    int parent[MAX], key[MAX];
    bool mstSet[MAX];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }

        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST_Prim(parent, graph, V);
}

void kruskalMST(int graph[MAX][MAX], int V) {
    Edge edges[MAX * MAX];
    int edgeCount = 0;

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0) {
                edges[edgeCount++] = {i, j, graph[i][j]};
            }
        }
    }

    sort(edges, edges + edgeCount, compareEdges);

    int parent[MAX], rank[MAX];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    Edge mstEdges[MAX];
    int mstCount = 0, minCost = 0;

    for (int i = 0; i < edgeCount && mstCount < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int wt = edges[i].weight;

        if (findParent(parent, u) != findParent(parent, v)) {
            unionSets(parent, rank, u, v);
            mstEdges[mstCount++] = edges[i];
            minCost += wt;
        }
    }

    cout << "\nMinimum cost = " << minCost << endl;
    for (int i = 0; i < mstCount; i++)
        cout << "Edge " << mstEdges[i].u + 1 << "-" << mstEdges[i].v + 1 << " -> " << mstEdges[i].weight << endl;
}

int main() {
    int V, E;
    cout << "\nEnter the number of vertices (labs): ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    int graph[MAX][MAX] = {0};  // initialize matrix to 0

    cout << "\nEnter the edges (format: vertex1 vertex2 weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--; // Convert to 0-based indexing
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int choice;
    cout << "\nChoose Algorithm:\n";
    cout << "1) Prim's Algorithm\n";
    cout << "2) Kruskal's Algorithm\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
        primMST(graph, V);
    else if (choice == 2)
        kruskalMST(graph, V);
    else
        cout << "\nInvalid choice. Please try again.";

    return 0;
}