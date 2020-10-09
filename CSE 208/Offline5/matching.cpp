#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define NO_COLOR -1
#define RED 1
#define BLUE 2


class Graph {
    public:
    int nVertices;
    vector< int > parent;
    vector< int > color;
    vector< vector<int> > adjList;
    vector< vector<int> > capacity;

    Graph(int n) {
        nVertices = n;
        color.resize(nVertices);
        parent.resize(nVertices);
        adjList.resize(nVertices);
        capacity.resize(nVertices);

        for (int i=0; i < nVertices; i++) {
            capacity[i].resize(nVertices);
        }
    }


    void addEdge(int u, int v, int c) {
        adjList[u].push_back(v);
        capacity[u][v] = c;
    }

    void print() {
        for (int i=0; i < nVertices; i++) {
            for (int j=0; j < adjList[i].size(); j++) {
                int v = adjList[i].at(j);
                cout << i << " " << v << " " << capacity[i][v] << endl; 
            }
        }
    }

    void printMatching(Graph res, int source, int sink) {
        for (int i=0; i < nVertices; i++) {
            for (int j=0; j < adjList[i].size(); j++) {
                int v = adjList[i].at(j);
                if ( (i != source) && (i != sink) && (v != source) && (v != sink) ) {
                    if (res.capacity[i][v] == 0) {
                        cout << i << " " << v << endl;
                    }
                } 
            }
        }
    }

    bool bfs(int source, int sink) {
        bool visited[nVertices];

        for (int i=0; i < nVertices; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int i=0; i < nVertices; i++) {
                if (visited[i] == false) {
                    if (capacity[curr][i] > 0) {
                        q.push(i);
                        parent[i] = curr;
                        visited[i] = true;
                    }
                }
            }
        }
        return (visited[sink] == true);
    }

    void fordFulkerson(int source, int sink) {
        int maxFlow = 0;
        Graph res(nVertices);

        for (int i=0; i < nVertices; i++) {
            for (int j=0; j < adjList[i].size(); j++) {
                int v = adjList[i].at(j);
                res.adjList[i].push_back(v);
                res.capacity[i][v] = capacity[i][v];
            }
        }

        if (!res.bfs(source, sink)) {
            cout << "Source and sink is disconnected.";
            return;
        }

        while (res.bfs(source, sink)) {
            int flow = INT_MAX;
            int prev, curr;
            
            for (curr = sink; curr != source; curr = res.parent[curr]) { 
                prev = res.parent[curr]; 
                flow = min(flow, res.capacity[prev][curr]); 
            }

            for (curr = sink; curr != source; curr = res.parent[curr]) {
                prev = res.parent[curr];
                res.capacity[prev][curr] -= flow;
                res.capacity[curr][prev] += flow;
            }
            maxFlow += flow;
        }
        cout << maxFlow << endl;
        printMatching(res, source, sink);
    }

    bool isBipartite() {
        for (int i=0; i < nVertices; i++) {
            color[i] = NO_COLOR;
        }

        for (int i=0; i < nVertices; i++) {
            if (color[i] == NO_COLOR) {
                if (isBipartiteCall(i) == false) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool isBipartiteCall(int source) {
        color[source] = RED;
        queue<int> q;
        q.push(source);
                
        while ( !q.empty() ) {
            int curr = q.front();
            q.pop();
            
            // SELF LOOP Check
            for (int i=0; i < adjList[curr].size(); i++) {
                if (adjList[curr].at(i) == curr) {
                    return false;
                }
            }
            for (int i=0; i < adjList[curr].size(); i++) {
                int node = adjList[curr][i];

                if ((capacity[curr][node]) && (color[node] == NO_COLOR)) {    
                    if (color[curr] == RED)
                        color[node] = BLUE;
                    else if (color[curr] == BLUE)
                        color[node] = RED;

                    q.push(node);
                } else if ( (capacity[curr][node]) && (color[curr] == color[node]) ) {
                    // Meighbors are same colored
                    return false;
                }
            }
        }
        return true; 
    }

    void maxMatching() {
        Graph g(nVertices + 2);
        int source = nVertices;
        int sink = nVertices + 1;
        // nijeder connecteion
        for (int i=0; i < nVertices; i++) {
            for (int j=0; j < adjList[i].size(); j++) {
                int node = adjList[i].at(j);
                if (color[i] == RED) {
                    g.addEdge(i, node, 1);
                }
            }
        }
        //one sided connection
        for (int i=0; i < nVertices; i++) {
            if (color[i] == RED) {
                g.addEdge(source, i, 1);
            }
            else if (color[i] == BLUE) {
                g.addEdge(i, sink, 1);
            }
        }
        g.fordFulkerson(source, sink);
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, E;
    cin >> N >> E;
    Graph graph(N);

    int u, v;
    for (int i=0; i < E; i++) {
        cin >> u >> v;
        graph.addEdge(u, v, 1);
        graph.addEdge(v, u, 1);
    }

    if (graph.isBipartite()) {
        graph.maxMatching();
    } else {
        cout << "The graph is not bipartite";
    }

    return 0;
}