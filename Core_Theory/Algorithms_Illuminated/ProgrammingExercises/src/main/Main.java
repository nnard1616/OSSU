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
package main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import part1.ch1.MergeSort;
import static part1.ch3.ex1To5.absoluteMin;
import static part1.ch5.QuickSort.printArray;
import static part1.ch5.QuickSort.quickSort;
import static part1.ch5.QuickSort.swap;
import part1.ch6.Doublet;
import static part1.ch6.Selection.dselect;
import static part1.ch6.Selection.rselect;
import static part1.ch6.WeightedMedian.weightedMedian;
import part1.week4.Graph;

/**
 *
 * @author Nathan Nard
 */
public class Main {
    private static Random rand = new Random();
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Graph test = new Graph();
        ArrayList<Integer> adjs;
        Integer n;
        Scanner lineScanner;
        Scanner intScanner;
        
        try{
            lineScanner = new Scanner(new File("../../Algorithms-Roughgarden/Part1/week4/kargerMinCut.txt"));
            
            while (lineScanner.hasNextLine()){
                
                
                adjs       = new ArrayList<>();
                intScanner = new Scanner(lineScanner.nextLine());
                n          = intScanner.nextInt();
                
                while (intScanner.hasNextInt())
                    adjs.add(intScanner.nextInt());
                
                test.addNode(n, adjs);
            }
            
            //determine min cut.
            int minCut = Integer.MAX_VALUE;
            Graph testCopy = new Graph(test);
            
            for (int i = 0; i < 200*200*Math.log(200); i++){
                test = new Graph(testCopy);
                
                while (test.getAdjList().size() > 2){
                    Integer randFirst = rand.nextInt(test.getAdjList().size());
                    Integer randSecond = rand.nextInt(test.getAdjList().size());
                    
                    //make sure both numbers are not the same
                    while (randFirst.equals( randSecond))
                        randSecond = rand.nextInt(test.getAdjList().size());
                    
                    test.contract(randFirst, randSecond);
                }
                
                minCut = Math.min(minCut, test.cutDegree());
                System.out.println(minCut);
                    
            }
            
            System.out.println(minCut);
            
        }catch(FileNotFoundException fnfe){
            System.out.println("no file found");
        }
    }
    
    public static void testLocalMin(){
        //    int[][] m = new int[][] {{46,16,47,49,52,53,54,15},
        //                             {45, 4,48,50,55,56,57,58},
        //                             { 5, 0, 6,51,61,60,59, 8},
        //                             {44, 7,41,40,62,63, 9, 3},
        //                             {43,42,39,38,37,11,36,10},
        //                             {21,22,23,26,14, 1,12,35},
        //                             {19, 2,24,27,29,13,33,34},
        //                             {18,20,25,28,30,31,32,17}};
//        int s = 64;
//        int maxRand = 5000;
//
//        int[][] m = new int[s][s];
//
//        Random r = new Random();
//        ArrayList<Integer> record = new ArrayList<Integer>();
        
        int[][] m = new int[][] {{15,34,12,13},
                                 {30, 0, 6,14},
                                 {99,98,97,96},
                                 {95,94,93,92}};
        

        String p = "";
        int n;
        int s = m[0].length;

        for (int i = 0; i < s; i++){
            for(int j = 0; j < s; j++){
//                n = r.nextInt(maxRand);
                n = m[i][j];
//                while(record.contains(n))
//                    n = r.nextInt(maxRand);
//                m[i][j] = n;
//                record.add(n);

                String spacer = "";
                if(n < 1000)
                    spacer = " ";
                if(n < 100)
                    spacer = "  ";
                if(n < 10)
                    spacer = "   ";

                p += spacer + n + " ";
            }
            p += "\n";
        }


        int ans = absoluteMin(m,0,0,s-1,s-1);
        System.out.println(ans);
        System.out.println(p);
    }
    
    public static void testMergeSort(){
        MergeSort test = new MergeSort();
        List<Comparable> a = new ArrayList<Comparable>();
        Scanner scanner;
        try{
            scanner = new Scanner(new File("../../Algorithms-Roughgarden/Part1/week2/IntegerArray.txt"));
            
            while (scanner.hasNextInt())
                a.add(scanner.nextInt());
            
            test.mergeSort(a);
            
            System.out.println(test.getInversions());
            
        }catch(FileNotFoundException fnfe){
            System.out.println("no file found");
        }
    }
    
    public static void testQuickSort(){
        Integer[] a = new Integer[10000];
        Scanner scanner;
        try{
            scanner = new Scanner(new File("../../Algorithms-Roughgarden/Part1/week3/QuickSort.txt"));
            
            int i = 0;
            while (scanner.hasNextInt())
                a[i++] = scanner.nextInt();
            
            quickSort(a, 0, 9999);
            
            printArray(a);
            
        }catch(FileNotFoundException fnfe){
            System.out.println("no file found");
        }
    }
    public static void testDSelect(){
        Integer[] a = new Integer[] {11,6,10,2,15,8,1,7,14,3,9,12,4,5,13,0};
        
        Comparable ans = dselect(a, 7);
        
        System.out.println(ans);
        printArray(a);
    }
    
    public static void testRSelect(){
        Integer[] a = new Integer[] {11,6,10,2,15,8,1,7,14,3,9,12,4,5,13,0};
        
        Comparable ans = rselect(a, 7);
        
        System.out.println(ans);
        printArray(a);
    }
    
    public static void reverseArray(Object[] a){
        for (int i = 0; i < a.length/2; i++)
            swap(a, i, a.length-i-1);
    }
    
    public static void testWeightedMedian(){
        Doublet[] a = new Doublet[] { new Doublet(9, 2),
                                      new Doublet(8, 2),
                                      new Doublet(6,15),
                                      new Doublet(2, 7),
                                      new Doublet(0, 6),
                                      new Doublet(5, 3),
                                      new Doublet(4, 2),
                                      new Doublet(1, 8),
                                      new Doublet(7,10),
                                      new Doublet(3, 1) };
        
        
        Doublet ans = weightedMedian(a, 0, 9);
    }
}
