import java.util.Vector;
import java.lang.Math;

public class Graph {

       public static double INFINITY = 999999999;
       int nVertices, nEdges;

       int[][] parentMatrix;
       double[][] distanceMatrix;

       double[] distance;
       int[] parent;

       Vector<Edge> adjList;

       public void setnVertices(int n){
              nVertices = n;
              parent = new int[nVertices];
              distance = new double[nVertices];
              adjList = new Vector<Edge>(nVertices);
              parentMatrix = new int[nVertices][nVertices];
              distanceMatrix = new double[nVertices][nVertices];
       }

       private int findEdge(int u, int v) {
              int edgeIndex = -1;
              for (int i=0; i<nEdges; i++) {
                     Edge edge = adjList.elementAt(i);
                     if ((edge.u == u) && (edge.v == v)) {
                            edgeIndex = i;
                            break;
                     }
              }
              return edgeIndex;
       }

       public Boolean addEdge(int u, int v, double w){
              for (int i=0; i<nEdges; i++) {
                     Edge edge = adjList.elementAt(i);
                     if ((edge.u == u) && (edge.v == v)){
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

       public Boolean isEdge (int u, int v) {
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
                                   System.out.print(adjList.elementAt(i).getV() + " ");
                            }
                     }
                     System.out.print("/n");
              }
       }

       public void cleanSPInfo(){
              for (int i=0; i < nVertices; i++) {
                     for (int j=0; j < nVertices; j++) {
                            distanceMatrix[i][j] = INFINITY;
                            parentMatrix[i][j] = -1;
                     }
              }
       }

       public void printDistanceMatrix(){
              for (int i=0; i < nVertices; i++) {
                     for (int j=0; j < nVertices; j++) {
                            if (distanceMatrix[i][j] == INFINITY) {
                                   System.out.print("INF ");
                            } else {
                                   System.out.print(distanceMatrix[i][j] + " ");
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
              for (int k=0; k < nVertices; k++) {
                     for (int i=0; i < nVertices; i++) {
                            for (int j=0; j < nVertices; j++) {
                                   // distance counting
                                   distanceMatrix[i][j] = Math.min(distanceMatrix[i][j], distanceMatrix[i][k] + distanceMatrix[k][j]);
                                   // parent storing
                                   if ((i==j) || (getWeight(i, j)==INFINITY)) {
                                          parentMatrix[i][j] = -1;
                                   } else if ((i != j) && (getWeight(i, j) < INFINITY)){
                                          parentMatrix[i][j] = i;
                                   }
                            }
                     }
              }
       }

       public Boolean bellmanFord(int src) {
              for (int i=0; i<nVertices; i++) {
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

       }


}