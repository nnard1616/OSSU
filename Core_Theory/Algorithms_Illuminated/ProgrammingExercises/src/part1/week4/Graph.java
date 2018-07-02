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
import java.util.HashMap;
import java.util.Iterator;

/**
 * Undirected general graph.
 * 
 * @author Nathan Nard
 */
public class Graph {
    private HashMap<Integer,ArrayList<Integer>> adjList;
    
    public Graph(){
        adjList = new HashMap<>();
    }
    //copy constructor
    public Graph(Graph g){
        adjList = (HashMap)g.getAdjList().clone();
    }
    
    public void addNode(Integer n, ArrayList<Integer> adjs){
        adjList.put(n, adjs);
    }
    
    public int cutDegree(){
        if (adjList.size() != 2)
            throw new IllegalStateException("Cut has not been made yet.");
        
        return adjList.get((Integer)adjList.keySet().toArray()[0]).size();
    }
    
    public void contract( Integer aIndex, Integer bIndex){
        Integer a = (Integer)adjList.keySet().toArray()[aIndex];
        Integer b = (Integer)adjList.keySet().toArray()[bIndex];
        
        Iterator itrA = adjList.get(a).iterator();
        Iterator itrB = adjList.get(b).iterator();
        
        while (itrA.hasNext())
            if (itrA.next() == b)
                itrA.remove();
        
        while (itrB.hasNext())
            if (itrB.next() == a)
                itrB.remove();
        
        //find min(a,b)
        Integer minimum = Math.min(a, b);
        Integer maximum = Math.max(a, b);
        
        //cycle through adjs of adjs of a and b. 
        ArrayList<Integer> adjMax = adjList.get(maximum); //adjs of max
        ArrayList<Integer> adjMin = adjList.get(minimum); //adjs of min
        ArrayList<Integer> adjI;
        
        for (int i = 0; i < adjMax.size(); i++){
            adjI = adjList.get(adjMax.get(i));
            System.out.println(i + ": ");
            for (int j = 0; j < adjI.size(); j++){
                //If see larger value in adjs, convert to smaller value.
                if (adjI.get(j).equals(maximum))
                    adjI.set(j, minimum);
            }
            //put adjs of larger into smaller
            adjMin.add(adjMax.get(i));
        }
        
        //delete larger value
        adjList.remove(maximum);
        
    }

    public HashMap<Integer, ArrayList<Integer>> getAdjList() {
        return adjList;
    }

    
    @Override
    public String toString() {
        String result = "";
        
        for (Integer i: adjList.keySet()){
            result += i + " ";
            for (Integer j : adjList.get(i)){
                result += j + " ";
            }
            result += "\n";
        }
        
        return result;
    }
    
}
