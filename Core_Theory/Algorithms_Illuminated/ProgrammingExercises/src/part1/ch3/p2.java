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
package part1.ch3;

/**
 *
 * @author Nathan Nard
 */
public class p2 {
    /**
     * Assumes 'in' array has length of power of 2 and is strictly 
     * unimodal with no consecutive terms that are equal.
     * 
     * @param in
     * @return 
     */
    public static Comparable unimodalMax(Comparable[] in, Integer start, Integer end){
        //base case
        if (end - start == 1)
            return (in[start].compareTo(in[end]) < 0) ? in[end] : in[start];
        
        //divide
        Integer mid = (start+end+1)/2;
        
        Comparable lleft  = in[mid-1]; //last of left half
        Comparable fright = in[mid];   //first of right half
        
        //recurse
        
        //if last element in left half is less than the first element
        //of the right half, then the max element is in the right half.
        //Else, the max element is in the left half.
        return (lleft.compareTo(fright) < 0) ? unimodalMax(in, mid, end) : 
                                               unimodalMax(in, start, mid-1);
    }
    
    /**
     * Assumes 'in' array of length of power of 2 and no duplicates.
     * @param in
     * @return 
     */
    public static boolean oneEleEqual2Index(Integer[] in, Integer start, Integer end){
        //base case
        if (start == end)
            return (in[start].compareTo(start) == 0);
        
        //law of syllogism
        //if last element is less than its index, then there's no way
        //that preceeding elements will ever be equal to their indices.
        if (in[end].compareTo(end) < 0)
            return false;
        
        //divide
        if (in[end].compareTo(end) > 0){
            Integer mid = (start+end+1)/2;
            
            //recurse
            
            //check if target is in left half
            if (oneEleEqual2Index(in, start, mid-1))
                return true;
            
            //check if target is in right half.
            return oneEleEqual2Index(in, mid, end);
        }
        
        //very last element of 'in' is equal to its index.
        return true;
    }
    
    public static void printArray(Object[] in){
        String result = "";
        for (Object o : in){
            result += o + " ";
        }
        System.out.println(result);
    }
}
