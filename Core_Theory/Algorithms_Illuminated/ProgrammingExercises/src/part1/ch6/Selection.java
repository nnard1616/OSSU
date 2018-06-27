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
package part1.ch6;

import java.util.Arrays;
import java.util.Random;
import static part1.ch5.QuickSort.partition;
import static part1.ch5.QuickSort.swap;

/**
 *
 * @author Nathan Nard
 */
public class Selection {
    private static final int GROUP = 5;
    private static Random rand = new Random();
    
    /**
     *  Assumes ith statistic exists.
     * 1st --> i = 0
     * 2nd --> i = 1, etc.
     * 
     * @param a
     * @param i
     * @return value at ith statistic
     */
    public static Comparable dselect(Comparable[] a, int i){
        //base case
        if (a.length == 1)
            return a[0];
        
        //c will contain medians of the groups of GROUP
        Comparable[] c = new Comparable[a.length/GROUP];
        
        for (int h = 0; h < a.length/GROUP; h++)
            c[h] = median(Arrays.copyOfRange(a, h*GROUP, (h+1)*GROUP));
        
        //p will be the median of the medians in c.
        Comparable p = -1;
        
        
        //there's potential for c to be smaller than GROUP
        
        //c's length is less than the GROUP divisor
        if (c.length == 0)
            p = median(a);
        else //c's length is longer than GROUP divisor
            p = dselect(c, (c.length-1)/2);
        
        //pivot index
        int indexOfp = getIndexOf(a, p);
        
        //switches first element with chosen pivot
        swap(a, indexOfp, 0);
        
        //partition returns index of new pivot, j
        int j = partition(a, 0, a.length-1);
        
        if (j == i)
            return p;
        else if ( j > i)
            return dselect(Arrays.copyOfRange(a, 0, j), i);
        else
            return dselect(Arrays.copyOfRange(a, j+1, a.length), i-j-1);
    }
    
    public static Comparable rselect(Comparable[] a, int i){
        //base case
        if (a.length == 1)
            return a[0];
        
        //randomly pick pivot
        int p = rand.nextInt(a.length);
        
        //switches first element with chosen pivot
        swap(a, p, 0);
        
        //partition returns index of new pivot, j
        int j = partition(a, 0, a.length-1);
        
        if (j == i)
            return a[p];
        else if ( j > i)
            return rselect(Arrays.copyOfRange(a, 0, j), i);
        else
            return rselect(Arrays.copyOfRange(a, j+1, a.length), i-j-1);
    }
    
    /**
     * Returns index of first occurrence of value.  -1 if value is not in a.
     * @param a
     * @param value
     * @return 
     */
    private static int getIndexOf(Comparable[] a, Comparable value){
        for (int i = 0; i < a.length; i++)
            if (a[i].equals(value))
                return i;
        
        return -1;
    }
    
    private static Comparable median(Comparable[] a){
        Arrays.sort(a); 
        
        return a[(a.length-1)/2];
    }
}
