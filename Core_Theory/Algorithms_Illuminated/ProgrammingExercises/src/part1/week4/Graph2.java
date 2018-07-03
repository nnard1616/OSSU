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

import java.util.ArrayList;

/**
 *
 * @author Nathan Nard
 */
public class Graph2 {
    private ArrayList<Node> nodes;
    private ArrayList<Edge> edges;
    
    
    
    
    
    private class Node<E extends Comparable<E>> implements Comparable<Node>{
        public final E value;
        public ArrayList<Edge> edges;

        public Node(E value, ArrayList<Edge> edges){
            this.value = value;
            this.edges = edges;
        }

        @Override
        public int compareTo(Node o) {
//            
            if (this.value.getClass() != o.value.getClass())
                throw new IllegalStateException("Illegally compared Nodes "
                                              + "that hold values of different "
                                              + "class types.");
            
            return this.value.compareTo((E)o.value);
        }
        
        @Override
        public String toString() {
            return value.toString();
        }

        @Override
        public boolean equals(Object obj) {
            if (obj.getClass() != Node.class)
                throw new IllegalStateException("Illegally compared Node to "
                                              + "some other type of object");
            Node other = (Node)obj;
            
            return this.compareTo(other) == 0;
        }
    }
    
    private class Edge{
        public Node first;
        public Node second;

        public Edge(Node a, Node b){
            if (a.compareTo(b) < 0){
                first  = a;
                second = b;
            }else{
                first  = b;
                second = a;
            }
        }
    }
    
    
    

}
