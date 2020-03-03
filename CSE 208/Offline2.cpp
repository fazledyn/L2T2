#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
using namespace std;


class Graph {

       vector<pair<int, int>> *adjList;
       int *dist;
       bool *visited;
       int nVertices;

       public:
       Graph(int n){
              nVertices = n;
              adjList = new vector<pair<int, int>>[nVertices];
              dist = new int[nVertices];
              visited = new bool[nVertices];
       }

       void printDist(){
              for (int i=0; i<nVertices; i++){
                     cout << dist[i] << "  ";
              }
       }

       void printGraph(){
              for (int i=0; i<nVertices; i++){
                     for (int j=0; j<adjList[i].size(); j++){
                            cout << i << " -> " << adjList[i].at(j).first << " : " << adjList[i].at(j).second << endl;
                     }
              }
       }

       void addEdge(int u, int v, int w){
              adjList[u].push_back(make_pair(v, w));
       }

       void DijkstraAlgorithm(int src, int des){
              cout << "Dijkstra's Algorithm :" << endl;
              int u;
              priority_queue<int, vector<int>, greater<int>> queue;

              for (int i=0; i<nVertices; i++){
                     dist[i] = INT_MAX;
                     visited[i] = false;
                     queue.push(i);
              }

              dist[src] = 0;
              while (!queue.empty()){
                     u = queue.top();
                     queue.pop();
                     visited[u] = true;
                     
                     int v, w;
                     for (int i=0; i < adjList[u].size(); i++){
                            v = adjList[u].at(i).first;
                            w = adjList[u].at(i).second;

                            if (dist[v] > dist[u] + w){
                                   dist[v] = dist[u] + w;
                            }
                     }
              }
              if (dist[des] != INT_MAX){
                     cout << "Distance of " << src << " -> " << des << ": " << dist[des] << endl;
              } else {
                     cout << src << " -> " << des << endl;
                     cout << "There's no shortest path" << endl;
              }
              
       }

       void BellmanFord(int src, int des){
              cout << "Bellman Ford Algorithm :" << endl;
              for (int i=0; i<nVertices; i++){
                     dist[i] = INT_MAX;
              }
              dist[src] = 0;
              int v, w;
              for (int i=0; i<nVertices-1; i++){
                     for (int j=0; j < nVertices; j++){
                            int u = j;
                            for (int k=0; k < adjList[j].size(); k++){
                                   v = adjList[j].at(k).first;
                                   w = adjList[j].at(k).second;

                                   if (dist[v] > dist[u] + w){
                                          dist[v] = dist[u] + w;
                                   }
                            }
                     }
              }

              for (int j=0; j<nVertices; j++){
                     int u = j;
                     for (int k=0; k < adjList[j].size(); k++){
                            v = adjList[j].at(k).first;
                            w = adjList[j].at(k).second;

                            if (dist[v] > dist[u] + w){
                                   cout << "Negative Edge Detected !" << endl;
                            }
                     }
              }

              if (dist[des] != INT_MAX){
                     cout << "Distance of " << src << " -> " << des << ": " << dist[des] << endl;
              } else {
                     cout << src << " -> " << des << endl;
                     cout << "There's no shortest path" << endl;
              }
       }
};


int main(){

       Graph g(10);

       g.addEdge(0, 7, 60);
       g.addEdge(7, 1, -150);
       g.addEdge(4, 8, -70);
       g.addEdge(6, 4, 80);
       g.addEdge(5, 1, 4000);
       g.addEdge(8, 0, 100000);
       g.addEdge(2, 3, -200);
       g.addEdge(8, 2, 1000);

       g.addEdge(0, 3, 300);
       g.addEdge(3, 8, 50000);
       g.addEdge(3, 7, -200);
       g.addEdge(2, 5, 120);
       g.addEdge(6, 3, 1500);
       g.addEdge(4, 0, 90);

       g.addEdge(5, 7, -50);
       g.addEdge(1, 6, 100);
       g.addEdge(4, 1, -90);

       g.printGraph();
  //     fstream inputFile;
//       inputFile.open("input.txt", ios::in);

       g.DijkstraAlgorithm(0, 5);
       cout << endl;
       g.printDist();
       
       cout << endl;
       g.BellmanFord(0, 5);
       
       cin.ignore();

       return 0;
}