package Offline3;

import java.util.Scanner;

public class Offline3 {

       public static void printMenu() {
              System.out.println("1. Clear SP Values");
              System.out.println("2. Floyd Warshall Algorithm");
              System.out.println("3. Johnson's Algorithm");
              System.out.println("4. Weight of the shortest path [u v]");
              System.out.println("5. Print Graph");
              System.out.println("6. Print Distance Matrix");
              System.out.println("7. Print Predecessor Matrix");
       }

       public static void main(String[] args) {
              Scanner sc = new Scanner(System.in);

              int nVert = sc.nextInt();
              int nEdge = sc.nextInt();

              int u, v;
              double w;

              Graph g = new Graph();
              g.setnVertices(nVert + 1);

              for (int i=0; i<nEdge; i++) {
                     u = sc.nextInt();
                     v = sc.nextInt();
                     w = sc.nextDouble();
                     g.addEdge(u, v, w);
              }
              System.out.println("Graph Created.");
              
              int option;
              while(true) {
                     printMenu();
                     option = sc.nextInt();
                     
                     if (option == 1) {
                            g.cleanSPInfo();
                            System.out.println("APSP matrices cleared.");
                     }
                     else if (option == 2) {
                            g.floydWarshall();
                            System.out.println("Floyd-Warshall algorithm implemented");
                     }
                     else if (option == 3) {
                            g.johnsonsAlgo();
                            System.out.println("Johnson's algorithm implemented");
                     }
                     else if (option == 4) {
                            u = sc.nextInt();
                            v = sc.nextInt();

                            g.getShortestPathWeight(u, v);
                            g.printShortestPath(u, v);
                     }
                     else if (option == 5) {
                            g.printGraph();
                     }
                     else if (option == 6) {
                            g.printDistanceMatrix();
                     }
                     else if (option == 7) {
                            g.printPredecessorMatrix();
                     }
                     else {
                            break;
                     }
              }
              sc.close();
       }
}