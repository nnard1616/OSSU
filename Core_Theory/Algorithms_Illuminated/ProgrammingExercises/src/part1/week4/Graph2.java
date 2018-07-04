/*
 * The MIT License
 *
 * Copyright 2018 Nathan Nard.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package part1.week4;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

/**
 *
 * @author Nathan Nard
 */
public class Graph2 {
    private ArrayList<Node> nodes;
    private ArrayList<Edge> edges;
    private String filename;
    private static Random rand = new Random();
    
    public Graph2(){
        this(new ArrayList<Node>(), new ArrayList<Edge>());
    }
    
    public Graph2(String filename){
        
        this.filename = filename;
        
        readInData(filename);
        
    }
    
    public Graph2(Graph2 g){
        this.nodes = (ArrayList)g.getNodes().clone();
        this.edges = (ArrayList)g.getEdges().clone();
        this.filename = (String)g.getFilename();
    }

    public ArrayList<Node> getNodes() {
        return nodes;
    }

    public ArrayList<Edge> getEdges() {
        return edges;
    }

    public String getFilename() {
        return filename;
    }
    
    
    private void readInData(String filename){
        nodes = new ArrayList<>();
        edges = new ArrayList<>();
        
        ArrayList<Comparable> adjs;
        Integer n;
        Scanner lineScanner;
        Scanner intScanner;
        try{
            lineScanner = new Scanner(new File(filename));
            
            while (lineScanner.hasNextLine()){
                
                
                adjs       = new ArrayList<>();
                intScanner = new Scanner(lineScanner.nextLine());
                n          = intScanner.nextInt();
                
                while (intScanner.hasNextInt())
                    adjs.add(intScanner.nextInt());
                
                addAdjacency(n, adjs);
            }
        }catch(FileNotFoundException fnfe){
            System.out.println("no file found");
        }
    }
    
    public Graph2(ArrayList<Node> nodes, ArrayList<Edge> edges){
        this.nodes = nodes;
        this.edges = edges;
    }
    
    public int numberOfNodes(){
        return nodes.size();
    }
   
    public int numberOfEdges(){
        return edges.size();
    }
    
    public void addAdjacency(Comparable value, ArrayList<Comparable> neighbors){
        Node n = createOrFetchNode(value);
        Node m;
        Edge e;
        
        for (Comparable neighbor : neighbors){
            m = createOrFetchNode(neighbor);
            e = createOrFetchEdge(n, m);
            
            n.edges.add(e);
        }
    }
    
    public int minCut() throws CloneNotSupportedException{
        int result = Integer.MAX_VALUE;
        Double reps = nodes.size()*nodes.size()*Math.log(nodes.size());
        Graph2 gCopy  = new Graph2(this);
        int c = 0;
        
        for (int i = 0; i < reps; i++){
            
            while (nodes.size() > 2){
//                System.out.println(nodes.size());
                int randomSelection = rand.nextInt(edges.size());
                
//                System.out.println(nodes.size());
//                System.out.println(edges.size() + " : " + randomSelection);
//                System.out.println(edges.get(randomSelection));
//                System.out.println("V---------------------------------------------------V");
//                System.out.println(this);
                contract(edges.get(randomSelection));
//                System.out.println(this);
//                System.out.println("^---------------------------------------------------^\n\n");
            }
            result = Math.min(result, nodes.get(0).edges.size());
            
            //reset
            this.nodes = (ArrayList)gCopy.getNodes().clone();
            this.edges = (ArrayList)gCopy.getEdges().clone();
            
//            readInData(filename);
//            System.out.println(result);
            c++;
            if (c%1==0){
                System.out.println(c + ": " + result);
                
            }
            System.out.println(this);
        }
        
        
        return result;
    }
    
    public void contract(Comparable one, Comparable two){
        Edge e = new Edge(new Node(one), new Node(two));
        contract(edges.get(edges.indexOf(e)));
    }
    
    private void contract(Edge e){
        Node larger  = e.second;
        Node smaller = e.first;
        ArrayList<Edge> toAdd = new ArrayList<>();
        
//        System.out.println("Edges: " + edges.size() + " Nodes: " + nodes.size());
//        System.out.println("Edge: " + e);
//        System.out.println(this);
        for (Edge i : larger.edges){
            if (i.equals(e))
                continue;
            else{
                if (i.first.equals(larger))
                    i.first  = smaller;
                else
                    i.second = smaller;
//                smaller.edges.add(i);
                toAdd.add(i);
            }
        }
        
        for (Edge i : toAdd)
            smaller.edges.add(i);
        
        Edge selfReference = new Edge(smaller, smaller);
        
        //remove self references in smaller node
        while (smaller.edges.contains(selfReference)){
            smaller.edges.remove(selfReference);
            this.edges.remove(selfReference);
        }
        
        while (smaller.edges.contains(e)){
            smaller.edges.remove(e);
        }
        
        while (this.edges.contains(e)){
            this.edges.remove(e);
        }
        
        this.nodes.remove(larger);
//        System.out.println(this);
    }
    
    private Node createOrFetchNode(Comparable value){
        Node n = new Node(value);
        for (Node i : nodes)
            if (i.equals(n))
                return i;
        nodes.add(n);
        return n;
    }
    
    private Edge createOrFetchEdge(Node one, Node two){
        Edge e = new Edge(one, two);
        for (Edge i : edges)
            if (i.equals(e))
                return i;
        edges.add(e);
        return e;
    }

    @Override
    public String toString() {
        String result = "";
        
        for (Node n : this.nodes)
            result += n + "\n";
        
        return result;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return new Graph2((ArrayList)nodes.clone(), (ArrayList)edges.clone());
    }
    
    
    /**************************************************************************/
    /*  Node Implementation                                                   */
    /**************************************************************************/
    private static class Node implements Comparable{
        public final Comparable value;
        public ArrayList<Edge> edges;

        public Node(Comparable value, ArrayList<Edge> edges){
            this.value = value;
            this.edges = edges;
        }
        
        public Node(Comparable value){
            this(value, new ArrayList<>());
        }
        

        @Override
        public int compareTo(Object o) {
            if (o.getClass() != Node.class)
                throw new IllegalStateException("Illegally compared Node to "
                                              + "some other type of object");
            Node other = (Node)o;
            
            if (this.value.getClass() != other.value.getClass())
                throw new IllegalStateException("Illegally compared Nodes "
                                              + "that hold values of different "
                                              + "class types.");
            
            return this.value.compareTo(other.value);
        }
        
        @Override
        public String toString() {
            String result = this.value.toString() + " ";
            
            for (Edge e : this.edges){
                if (e.first.equals(this))
                    result += e.second.value + " ";
                else
                    result += e.first.value + " ";
            }
            return result;
        }

        @Override
        public boolean equals(Object obj) {
            return this.compareTo(obj) == 0;
        } 

        @Override
        public Object clone() throws CloneNotSupportedException {
            return new Node(value, (ArrayList)edges.clone());
        }
    }//end Node implementation
    
    
    /**************************************************************************/
    /*  Edge Implementation                                                   */
    /**************************************************************************/
    private static class Edge{
        public Node first;
        public Node second;

        public Edge(Node a, Node b){
            if(a.value.getClass() != b.value.getClass())
                throw new IllegalStateException("Cannot create edge between "
                                              + "nodes with different types of "
                                              + "values.");
            if (a.compareTo(b) < 0){
                first  = a;
                second = b;
            }else{
                first  = b;
                second = a;
            }
        }
        
        public Edge(){
            this(null, null);
        }

        @Override
        public boolean equals(Object obj) {
            if (obj.getClass() != Edge.class)
                throw new IllegalStateException("Illegally compared Edge to "
                                              + "some other type of object");
            
            Edge other = (Edge)obj;
            
            if (other.first.getClass() != this.first.getClass())
                throw new IllegalStateException("Edges are not same type.");
            
            return this.first.equals(other.first) 
                && this.second.equals(other.second);
        }

        @Override
        public String toString() {
            return first.value + " " + second.value;
        }

        @Override
        public Object clone() throws CloneNotSupportedException {
            return new Edge((Node)first.clone(), (Node)second.clone());
        }
    }//end Edge implementation
}
