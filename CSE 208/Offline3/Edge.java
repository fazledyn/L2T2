package Offline3;

public class Edge {
       int u, v;
       double weight;

       public Edge(int u, int v, double weight){
              this.u = u;
              this.v = v;
              this.weight = weight;
       }

       public int getU(){
              return this.u;
       }

       public int getV() {
              return v;
       }

       public void setU(int u) {
              this.u = u;
       }
       
       public void setV(int v) {
              this.v = v;
       }

       public void setWeight(double weight) {
              this.weight = weight;
       }

       public double getWeight() {
              return weight;
       }
}