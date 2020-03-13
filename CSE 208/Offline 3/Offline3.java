import java.util.Scanner;

public class Offline3 {
       public static void main(String[] args) {

              Scanner sc = new Scanner(System.in);
              Graph g = new Graph();
              
              System.out.println("Enter graph size: ");
              int size = sc.nextInt();

              g.setnVertices(size);

              System.out.println("Enter edges number: ");
              int edgeSize = sc.nextInt();

              for (int i=0; i<edgeSize; i++) {
                     System.out.println("Enter u, v, w: ");
                     int u, v;
                     double w;
       
                     u = sc.nextInt();
                     v = sc.nextInt();
                     w = sc.nextDouble();
       
                     g.addEdge(u, v, w);
              }

              System.out.println("Printing the graph: ");
              g.printGraph();
       }
}