#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <cstdio>

using namespace std;

#define INF 999999999


class Graph {

       vector<pair<int, int>> *adjList;
       int *dist;
       bool *visited;
       int *parent;
       int nVertices;

       public:
       Graph(int n){
              nVertices = n;
              adjList = new vector<pair<int, int>>[nVertices];
              dist = new int[nVertices];
              parent = new int[nVertices];
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

       void printTraceback(FILE *fp, int src, int des){
              if (des > 0) {
                     printTraceback(fp, src, parent[des]);
                     fprintf(fp, " -> %d", des);
              } else if (des == src) {
                     fprintf(fp, "%d", des);
              }
       }

       void DijkstraAlgorithm(FILE *fp, int src, int des){
              int u;
              priority_queue<int, vector<int>, greater<int>> queue;

              for (int i=0; i<nVertices; i++){
                     dist[i] = INF;
                     visited[i] = false;
                     parent[i] = -1;
              }
              
              queue.push(src);
              dist[src] = 0;

              while (!queue.empty()){
                     u = queue.top();
                     queue.pop(); 
                     
                     visited[u] = true;  
                     int v, w;
                     for (int i=0; i < adjList[u].size(); i++){
                            v = adjList[u].at(i).first;
                            w = abs(adjList[u].at(i).second);

                            if (dist[v] > dist[u] + w){
                                   parent[v] = u;
                                   dist[v] = dist[u] + w;
                                   queue.push(v);
                            }
                     }
              }
              fprintf(fp, "Dijkstra Algorithm:\n");
              fprintf(fp, "%d\n", dist[des]);
              printTraceback(fp, src, des);
       }

       void BellmanFord(FILE *fp, int src, int des){
              for (int i=0; i<nVertices; i++){
                     dist[i] = INF;
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
                                          parent[v] = u;
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
                                   fprintf(fp, "Negative edge cycle detected !");
                            }
                     }
              }

              fprintf(fp, "Bellman Ford Algorithm:\n");
              fprintf(fp, "%d\n", dist[des]);
              printTraceback(fp, src, des);
       }
};


int main(){

       FILE *file;
       file = fopen("input.txt", "r");

       int vertices, edges;
       fscanf(file, "%d", &vertices);
       fscanf(file, "%d", &edges);

       Graph g(vertices);
       int first, second, weight;

       for (int i=0; i < edges; i++){
              fscanf(file, "%d", &first);
              fscanf(file, "%d", &second);
              fscanf(file, "%d", &weight);
              g.addEdge(first, second, weight);
       }
       
       int src, des;       
       fscanf(file, "%d", &src);
       fscanf(file, "%d", &des);
       fclose(file);

       // Graph g(10);

       // g.addEdge(0, 7, 60);
       // g.addEdge(7, 1, -150);
       // g.addEdge(4, 8, -70);
       // g.addEdge(6, 4, 80);
       // g.addEdge(5, 1, 4000);

       // g.addEdge(8, 0, 100000);
       // g.addEdge(2, 3, -200);
       // g.addEdge(8, 2, 1000);
       // g.addEdge(0, 3, 300);
       // g.addEdge(3, 8, 50000);
       // g.addEdge(3, 7, -200);
       
       // g.addEdge(2, 5, 120);
       // g.addEdge(6, 3, 1500);
       // g.addEdge(4, 0, 90);
       // g.addEdge(5, 7, -50);
       // g.addEdge(1, 6, 100);
       // g.addEdge(4, 1, -90);

       file = fopen("output.txt", "w");

       g.BellmanFord(file, src, des);
       fprintf(file, "\n \n");
       g.DijkstraAlgorithm(file, src, des);

       fclose(file);

       cout << "The output file has been generated !" << endl;
       cin.ignore();

       return 0;
}