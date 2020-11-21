package Offline3;

import java.util.Collections;
import java.util.PriorityQueue;
import java.util.Vector;

import java.lang.Math;


public class Graph {

       public static double INFINITY = 999999999;
       public int nVertices, nEdges;

       int[][] parentMatrix;
       double[][] dist;

       double[] distance;
       boolean[] visited;
       int[] parent;

       Vector<Edge> adjList;

       public Graph(){
              //..
       }

       public void setnVertices(int n){
              nVertices = n + 1;
              parent = new int[nVertices];
              distance = new double[nVertices];
              adjList = new Vector<Edge>(nVertices);
              visited = new boolean[nVertices];
              parentMatrix = new int[nVertices][nVertices];
              dist = new double[nVertices][nVertices];
       }

       private int findEdge(int u, int v) {
              int edgeIndex = -1;
              for (int i=0; i < nEdges; i++) {
                     Edge edge = adjList.elementAt(i);
                     if ((edge.getU() == u) && (edge.getV() == v)) {
                            edgeIndex = i;
                            break;
                     }
              }
              return edgeIndex;
       }

       public Boolean addEdge(int u, int v, double w){
              for (int i=0; i < nEdges; i++) {
                     Edge edge = adjList.elementAt(i);
                     if ((edge.getU() == u) && (edge.getV() == v)){
                            return false;
                     }
              }
              adjList.add(new Edge(u, v, w));
              return true;
       }

       public void removeEdge(int u, int v){
              int edgeIndex = findEdge(u, v);
              adjList.removeElementAt(edgeIndex);
       }

       public void reweightEdge(int u, int v, double w) {
              int index = findEdge(u, v);

              if (index == -1) {
                     Edge newEdge = new Edge(u, v, w);
                     adjList.add(newEdge);
              } else { 
                     adjList.elementAt(index).setU(u);
                     adjList.elementAt(index).setV(v);
                     adjList.elementAt(index).setWeight(w);
              }
       }

       public Edge searchEdge(int u, int v) {
              int index = findEdge(u, v);

              if (index == -1) {
                     return null;
              } else {
                     Edge edge = adjList.elementAt(index);
                     return edge;
              }
       }

       public boolean isEdge (int u, int v) {
              int index = findEdge(u, v);
              if (index == -1) {
                     return false;
              } else {
                     return true;
              }
       }

       public double getWeight (int u, int v) {
              int index = findEdge(u, v);
              if (index == -1) {
                     return INFINITY;
              } else {
                     return adjList.elementAt(index).getWeight();
              }
       }

       public void printGraph() {
              System.out.println("- Print Graph");
              for (int i=0; i<nVertices; i++) {
                     System.out.print(i + ": ");
                     for (int j=0; j<adjList.size(); j++) {
                            if (adjList.elementAt(j).getU() == i) {
                                   System.out.print(adjList.elementAt(j).getV() + " ");
                            }
                     }
                     System.out.print("\n");
              }
       }

       public double getShortestPathWeight(int u, int v) {
              if (this.bellmanFord(u)) {
                     return dist[u][v];
              } else {
                     return INFINITY;
              }
       }

       public void printShortestPath(int u, int v) {
              if (v > 0) {
                     printShortestPath(u, parent[v]);
                     System.out.print(v);
              } else if (v == u) {
                     System.out.print(v);
              }
       }

       public void cleanSPInfo(){
              for (int i=0; i < nVertices; i++) {
                     for (int j=0; j < nVertices; j++) {
                            dist[i][j] = INFINITY;
                            parentMatrix[i][j] = -1;
                     }
              }
       }

       public void printdist(){
              for (int i=0; i < nVertices; i++) {
                     for (int j=0; j < nVertices; j++) {
                            if (dist[i][j] == INFINITY) {
                                   System.out.print("INF ");
                            } else {
                                   System.out.print(dist[i][j] + " ");
                            }
                     }
                     System.out.println("");
              }
       }

       public void printPredecessorMatrix() {
              for (int i=0; i < nVertices; i++) {
                     for (int j=0; j < nVertices; j++) {
                            if (parentMatrix[i][j] == -1) {
                                   System.out.print("NIL ");
                            } else {
                                   System.out.print(parentMatrix[i][j] + " ");
                            }
                     }
                     System.out.println("");
              }
       }

       public void floydWarshall() {
              // assuming no negative weight cycle

              for (int i=0; i < nVertices; i++) {
                     for (int j=0; j < nVertices; j++) {
                            if (i == j) {
                                   dist[i][j] = 0;
                            } else {
                                   dist[i][j] = INFINITY;
                            }
                     }
              }

              for (int k=0; k < nVertices; k++) {
                     for (int i=0; i < nVertices; i++) {
                            for (int j=0; j < nVertices; j++) {
                                   
                                   this.dist[i][j] = Math.min(this.dist[i][j], this.dist[i][k] + this.dist[k][j]);
                                   
                                   if ((i==j) || (getWeight(i, j)==INFINITY)) {
                                          this.parentMatrix[i][j] = -1;
                                   } else if ((i != j) && (this.getWeight(i, j) < INFINITY)){
                                          this.parentMatrix[i][j] = i;
                                   }
                            }
                     }
              }
       }

       public boolean bellmanFord(int src) {
              for (int i=0; i < nVertices; i++) {
                     parent[i] = -1;
                     distance[i] = INFINITY;
              }

              distance[src] = 0;
              for (int i=0; i < nVertices - 1; i++) {
                     for (int j=0; j < adjList.size(); j++) {
                            int u = adjList.elementAt(j).getU();
                            int v = adjList.elementAt(j).getV();
                            double w = adjList.elementAt(j).getWeight();
                            
                            if (distance[v] > distance[u] + w) {
                                   distance[v] = distance[u] + w;
                                   parent[v] = u;
                            }
                     }
              }
              for (int j=0; j < adjList.size(); j++) {
                     int u = adjList.elementAt(j).getU();
                     int v = adjList.elementAt(j).getV();
                     double w = adjList.elementAt(j).getWeight();
                     
                     if (distance[v] > distance[u] + w) {
                            System.out.println("Negative weight cycle !");
                            return false;
                     }
              }
              return true;
       }

       public void Dijkstra(int src) {

              PriorityQueue<Integer> queue = new PriorityQueue<Integer>(Collections.reverseOrder());
              for (int i=0; i<nVertices; i++) {
                     distance[i] = INFINITY;
                     visited[i] = false;
                     parent[i] = -1;
              }
              queue.add(src);
              distance[src] = 0;

              int u;
              while (!queue.isEmpty()) {
                     u = queue.remove();
                     visited[u] = true;
                     double w;

                     for (int v=0; v<nVertices; v++) {
                            int index = findEdge(u, v);
                            if (index != -1) {
                                   w = Math.abs(adjList.elementAt(index).getWeight());
                                   if (distance[v] > distance[u] + w) {
                                          distance[v] = distance[u] + w;
                                          parent[v] = u;
                                          queue.add(v);
                                   }
                            }
                     }
              }
       }

       public void johnsonsAlgo() {
              Graph gr = new Graph();
              gr.setnVertices(this.nVertices + 1);
              gr.adjList = this.adjList;

              for (int i=0; i < this.nVertices; i++) {
                     for (int j=0; j < this.nVertices; j++) {
                            gr.parentMatrix[i][j] = this.parentMatrix[i][j];
                            gr.dist[i][j] = this.dist[i][j];
                     }
                     gr.parent[i] = this.parent[i];
                     gr.visited[i] = this.visited[i];
                     gr.distance[i] = this.distance[i];
              }

              int src = this.nVertices;
              for (int i=0; i < nVertices; i++) {
                     gr.addEdge(src, i, 0);
              }

              if (gr.bellmanFord(src) == false) {
                     System.out.println("There is a negative-weight cycle.");
                     return;
              } 
              else {
                     for (int i=0; i < gr.nVertices; i++) {
                            gr.distance[i] = gr.dist[src][i];
                     }

                     for (int i=0; i < adjList.size(); i++) {
                            int u = adjList.elementAt(i).getU();
                            int v = adjList.elementAt(i).getV();

                            if ((u != nVertices) && (v != nVertices)) {  
                                   reweightEdge(u, v, getWeight(u, v) + distance[u] - distance[v]);
                            }
                     }
                     double[][] newDMatrix = new double[nVertices][nVertices];

                     for (int i=0; i<nVertices; i++) {
                            this.Dijkstra(i);
                            for (int j=0; j<nVertices; j++) {
                                   newDMatrix[i][j] = dist[i][j] + distance[j] - distance[i];
                            }
                     }
                     //return newDMatrix;
              }
       }
}