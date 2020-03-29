#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>

using namespace std;

#define INF 999999999
#define MAX 100
typedef pair<int, int> pii;


class Node {
public:
    int data;
    int parent;
    int rank;
};

class Edge {
public:
    int u;
    int v;
    int weight;

    Edge(int U, int V, int W) {
        u = U;
        v = V;
        weight = W;
    }
};

bool compareEdge(Edge first, Edge second) {
    return (first.weight < second.weight);
}


class DisjointSet {

    Node node[MAX];
    int totalSize = 0;

    void Link(int x, int y) {
        if (x == y)
            return;

        if (node[x].rank > node[y].rank)
            node[y].parent = x;
        else {
            node[x].parent = y;
            if (node[x].rank == node[y].rank)
                node[y].rank = node[y].rank + 1;
        }
    }

public:

    void makeSet(int x) {
        node[x].parent = x;
        node[x].rank = 0;
        totalSize++;
    }

    int findSet(int x) {
        if (x != node[x].parent)
            node[x].parent = findSet(node[x].parent);

        return node[x].parent;
    }

    void Union(int x, int y) {
        Link(findSet(x), findSet(y));
    }

    void print(int x) {
        for (int i = 0; i < totalSize; i++) {
            if (x == node[i].parent)
                cout << i << " ";
        }
        cout << endl;
    }

    void printArray() {
        for (int i=0; i<totalSize; i++) {
            cout << i << " parent: " << node[i].parent << endl;
        }
    }

    int getSize() {
        return totalSize;
    }
};


class Graph {

    vector<pair<int, int>> *adjList;
    int nVertices, nEdges;
    int *parent, *key;
    vector<Edge> edge;

public:
    Graph(int v, int e) {
        nVertices = v;
        nEdges = e;
        adjList = new vector<pair<int, int> >[nVertices];
        parent = new int[nVertices];
        key = new int[nVertices];
    }

    void printGraph() {
        for (int i=0; i<nVertices; i++) {
            cout << i << ": ";
            for (int j=0; j<adjList[i].size(); j++) {
                cout << adjList[i].at(j).first << "(" << adjList[i].at(j).second << "), ";
            }
            cout << endl;
        }
    }

    void addEdge(int u, int v, int w) {
        // undirected graph
        adjList[u].push_back(make_pair(v, w));
        adjList[v].push_back(make_pair(u, w));
        edge.push_back( Edge(u, v, w) );
    }

    void kruskalMST() {

        DisjointSet set;
        int totalWeight = 0;

        for (int i=0; i < nVertices; i++) {
            parent[i] = -1;
            set.makeSet(i);
        }

        sort(edge.begin(), edge.end(), compareEdge);

        for (int i=0; i < nEdges; i++) {

            int u = edge.at(i).u;
            int v = edge.at(i).v;
            int w = edge.at(i).weight;

            if (set.findSet(u) != set.findSet(v)) {
                set.Union(u, v);

                if ((parent[u] == -1) && (parent[v] != -1)) {
                    parent[u] = v;
                }
                else if (parent[v] == -1) {
                    parent[v] = u;
                }
                totalWeight += w;
            }
        }
        // total weight
        cout << totalWeight << endl;
        // mst print
        cout << "Kruskal's algorithm:" << endl;

        for (int i=0; i < nVertices; i++) {
            if (parent[i] != -1)
                cout << parent[i] << " " << i << endl;
        }
    }

    void primsMST() {

        cout << "Prim's Algorithm: " << endl;

        int root = rand()%nVertices;
        int totalCost = 0;
        bool visited[nVertices];

        cout << "Root node = " << root << endl;

        for (int i=0; i < nVertices; i++) {
            visited[i] = false;
            key[i] = int(INFINITY);
            parent[i] = -1;
        }

        key[root] = 0;
        visited[root] = true;

        priority_queue <pii, vector<pii>, greater<pii> > pq;
        for (int i=0; i < adjList[root].size(); i++) {
            int weight = adjList[root].at(i).second;
            int node = adjList[root].at(i).first;

            pq.push(make_pair(weight, node));
            parent[node] = root;
        }

        while (!pq.empty()) {

            int currentNode = pq.top().second;
            int currentWeight = pq.top().first;
            pq.pop();

            visited[currentNode] = true;
            key[currentNode] = min(currentWeight, key[currentNode]);

            for (int i=0; i < adjList[currentNode].size(); i++) {
                int vertex = adjList[currentNode].at(i).first;
                int weight = adjList[currentNode].at(i).second;

                if (visited[vertex] == false) {
                    if (weight < key[vertex]) {
                        pq.push(make_pair(weight, vertex));
                        key[vertex] = weight;

                        if (parent[vertex] == -1)
                            parent[vertex] = currentNode;
                    }
                }
            }
        }

        for (int i=0; i < nVertices; i++) {
            if (i != root)
                cout << parent[i] << " " << i << endl;
        }
    }
};


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int nVert, nEdge;
    int u, v, w;

    cin >> nVert >> nEdge;

    Graph g(nVert, nEdge);

    for (int i=0; i < nEdge; i++) {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.kruskalMST();
    g.primsMST();

    return 0;
}
