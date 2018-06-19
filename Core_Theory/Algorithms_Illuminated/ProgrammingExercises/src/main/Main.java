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

import java.util.ArrayList;
import java.util.Random;
import static part1.ch3.ex1To4.localMin;

/**
 *
 * @author Nathan Nard
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
//    int[][] m = new int[][] {{46,16,47,49,52,53,54,15},
//                             {45, 4,48,50,55,56,57,58},
//                             { 5, 0, 6,51,61,60,59, 8},
//                             {44, 7,41,40,62,63, 9, 3},
//                             {43,42,39,38,37,11,36,10},
//                             {21,22,23,26,14, 1,12,35},
//                             {19, 2,24,27,29,13,33,34},
//                             {18,20,25,28,30,31,32,17}};
    int s = 64;
    int maxRand = 5000;
    
    int[][] m = new int[s][s];
    
    Random r = new Random();
    int n;
    ArrayList<Integer> record = new ArrayList<Integer>();
    String p = "";
    
    for (int i = 0; i < s; i++){
        for(int j = 0; j < s; j++){
            n = r.nextInt(maxRand);
            while(record.contains(n))
                n = r.nextInt(maxRand);
            m[i][j] = n;
            record.add(n);
            
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
    
       
    int ans = localMin(m,0,0,7,7);
    System.out.println(ans);
    System.out.println(p);
                                 
        
    }
    
    
}
