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
import java.util.HashMap;
import java.util.Iterator;
import java.util.Random;
import java.util.Scanner;

/**
 * Undirected general graph.
 * 
 * @author Nathan Nard
 */
public class Graph implements Cloneable {
    
    /**************************************************************************/
    /*  Attributes                                                            */
    /**************************************************************************/
    private HashMap<Integer,ArrayList<Integer>> adjList;
    private int minCut = Integer.MAX_VALUE;
    private String filename;
    private static Random rand = new Random();
    
    
    /**************************************************************************/
    /*  Constructor                                                           */
    /**************************************************************************/
    public Graph(String filename){
        adjList = new HashMap<>();
        this.filename = filename;
    }
    
    
    /**************************************************************************/
    /*  Graph Methods                                                         */
    /**************************************************************************/
    private void addNode(Integer n, ArrayList<Integer> adjs){
        adjList.put(n, adjs);
    }
    
    private int cutDegree(){
        if (adjList.size() != 2)
            throw new IllegalStateException("Cut has not been made yet.");
        
        return adjList.get((Integer)adjList.keySet().toArray()[0]).size();
    }
    
    private void contract( Integer a, Integer b){
        Iterator itrA = adjList.get(a).iterator();
        Iterator itrB = adjList.get(b).iterator();
        
        //remove a from b's neighbors (adjacents)
        while (itrA.hasNext())
            if (itrA.next().equals(b))
                itrA.remove();
        
        //remove b from a's neighbors
        while (itrB.hasNext())
            if (itrB.next().equals(a))
                itrB.remove();
        
        //Determine larger and smaller values
        Integer minimum = Math.min(a, b);
        Integer maximum = Math.max(a, b);
        
        //cycle through adjs of larger valued node... 
        ArrayList<Integer> adjMax = adjList.get(maximum); //adjs of max
        ArrayList<Integer> adjMin = adjList.get(minimum); //adjs of min
        ArrayList<Integer> adjI;
        
        /* Point where improvements can be made.*/
        
        for (int i = 0; i < adjMax.size(); i++){
            adjI = adjList.get(adjMax.get(i));
            
            //cycle through adjs of adjs of larger valued node...
            for (int j = 0; j < adjI.size(); j++){
                
                //If see larger value in adjs of adjs, convert to smaller value.
                if (adjI.get(j).equals(maximum))
                    adjI.set(j, minimum);
            }
            
            //put adjs of larger into smaller
            adjMin.add(adjMax.get(i));
        }
        
        //delete larger value
        adjList.remove(maximum);
        
    }
    
    private void readInData(String filename){
        ArrayList<Integer> adjs;
        Integer n;
        Scanner lineScanner;
        Scanner intScanner;
        
        adjList.clear();
        
        try{
            lineScanner = new Scanner(new File(filename));
            
            while (lineScanner.hasNextLine()){
                
                
                adjs       = new ArrayList<>();
                intScanner = new Scanner(lineScanner.nextLine());
                n          = intScanner.nextInt();
                
                while (intScanner.hasNextInt())
                    adjs.add(intScanner.nextInt());
                
                addNode(n, adjs);
            }
        }catch(FileNotFoundException fnfe){
            System.out.println("no file found");
        }
    }
    
    public int determineMinCut(){
        readInData(filename);
        int reps = 1000;

        for (int i = 0; i < reps; i++){


            while (getAdjList().size() > 2){
                //randomly select node
                Integer randFirst = rand.nextInt(adjList.size());
                Integer a = (Integer)adjList.keySet().toArray()[randFirst];

                //randomly select neighbor of first node
                Integer randSecond = rand.nextInt(adjList.get(a).size());
                Integer b = adjList.get(a).get(randSecond);

                contract(a, b);
            }

            minCut = Math.min(minCut, cutDegree());

            //reset
            readInData(filename);
        }

        return minCut;
    }

    
    /**************************************************************************/
    /*  Getters                                                               */
    /**************************************************************************/
    public HashMap<Integer, ArrayList<Integer>> getAdjList() {
        return adjList;
    }

    public int size(){
        return adjList.keySet().size();
    }
    
    
    /**************************************************************************/
    /*  Overrides                                                             */
    /**************************************************************************/
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

    @Override
    public Object clone() throws CloneNotSupportedException {
        return new Graph(filename);
    }
}
