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
package part2.week4;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Scanner;

/**
 *
 * @author Nathan Nard
 */
public class TwoSum {
    public static void solve() throws FileNotFoundException{
        Scanner sc = new Scanner(new File("/home/nathan/Programming/OSSU/"
                + "Core_Theory/Algorithms-Roughgarden/Part2/Week4/"
                + "algo1-programming_prob-2sum.txt"));
        
        Long l;
        Long complement;
        Long t;
        Integer repeats;
        int result = 0; 
        
        HashSet<Long> s = new HashSet<>();
        HashMap<Long,Integer> n = new HashMap<>(); //unassigned returns null
        
        //create range of -10000 to 10000
        for (long i = -10000; i <= 10000; i++)
            s.add(i);
        
        //read in the million numbers
        while(sc.hasNextLong()){
            l = sc.nextLong();
            repeats = n.putIfAbsent(l, 1);
            if (repeats != null)
                n.put(l, repeats+1);
        }
        
        
        Iterator itr = s.iterator();
        
        //iterate through million numbers
        for (Long number : n.keySet()){
            
            //iterate through what's left of -10000 to 10000
            while (itr.hasNext()){
                
                t = (Long)itr.next();
                complement = t - number;
                
                //check they are distinct
                if (complement != number){
                    
                    //check if both in our list of million numbers
                    if (n.containsKey(complement)){
                        
                        //remove current t from our range of -10000 to 10000,
                        //so we don't examine it again.
                        itr.remove();
                        
                        result++;
                    }
                }
            }
            
            //reset iterator
            itr = s.iterator();
        }
        
        System.out.println("Answer: " + result + "\n");
    }
}
