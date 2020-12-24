#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;


int bruteForce(vector<vector<int>> matrix, int source, int N) {

    vector<int> vertex;

    for (int i=0; i < N; i++) {
        if (i != source) {
            vertex.push_back(i);
        }
    }

    int currentWeight, minWeight = INT_MAX;
    do {
        currentWeight = 0;
        int firstNode = source, secondNode;

        for (int i=0; i < vertex.size(); i++) {
            secondNode = vertex[i];
            currentWeight += matrix[firstNode][secondNode];
            firstNode = secondNode;
        }

        currentWeight += matrix[secondNode][source];
        minWeight = min(minWeight, currentWeight);
    } while (next_permutation(vertex.begin(), vertex.end()));

    return minWeight;
}


int main() {
    freopen("input.txt", "r", stdin);

    int N, E;
    cin >> N >> E;
    cout << "N: " << N << " E: " << E << endl;

    vector< vector<int> > graph;
    int u, v, w;

    graph.reserve(N);
    for (int i=0; i < graph.size(); i++)
        graph[i].reserve(N);

    for (int i=0; i < N; i++) {
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    cout << endl << endl;
    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nMin cost: ";
    cout << bruteForce(graph, 0, N);
    return 0;
}
