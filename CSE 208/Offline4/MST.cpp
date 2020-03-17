#include <iostream>
#include <vector>
using namespace std;

#define INF 999999999

class Graph {

       vector<pair<int, int>> *adjList;
       int nVertices;

       public:
       Graph(int n){
              nVertices = n;
              adjList = new vector<pair<int, int>>[nVertices];
       }

       void printGraph(){
              for (int i=0; i<nVertices; i++){
                     for (int j=0; j<adjList[i].size(); j++){
                            cout << i << " -> " << adjList[i].at(j).first;
				cout << " : " << adjList[i].at(j).second << endl;
                     }
              }
       }

       void addEdge(int u, int v, int w){
              adjList[u].push_back(make_pair(v, w));
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
       return 0;
}