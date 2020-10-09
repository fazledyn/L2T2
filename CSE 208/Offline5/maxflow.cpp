#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
    public:
    int nVertices;
    vector <int> parent;
    vector< vector<int> > adjList;
    vector< vector<int> > capacity;


    Graph(int n) {
        nVertices = n;
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

    bool bfs(int source, int sink) {
        bool visited[nVertices];

        for (int i=0; i < nVertices; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        queue<int> q;
        q.push(source);        
        //parent[source] = -2;
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

        for (int i=0; i < nVertices; i++) {
            for (int j=0; j < adjList[i].size(); j++) {
                int v = adjList[i].at(j);
                cout << i << " " << v << " " << capacity[i][v] - res.capacity[i][v] << "/" << capacity[i][v] << endl; 
            }
        }
        //return maxFlow;
    }
        
    void printFlow(Graph res) {
        for (int i=0; i < nVertices; i++) {
            for (int j=0; j < adjList[i].size(); j++) {
                int v = adjList[i].at(j);
                cout << i << " " << v << " " << capacity[i][v] - res.capacity[i][v] << endl; 
            }
        }
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N, E;
    cin >> N >> E;
    Graph g(N);

    int u, v, c;
    for (int i=0; i < E; i++) {
        cin >> u >> v >> c;
        g.addEdge(u, v, c);
    }
    int s, t;
    cin >> s >> t;

    g.fordFulkerson(s, t);
}