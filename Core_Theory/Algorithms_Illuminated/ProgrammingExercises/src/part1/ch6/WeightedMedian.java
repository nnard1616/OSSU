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

import static part1.ch6.Selection.dselect;

/**
 *
 * @author Nathan Nard
 */
public class WeightedMedian {
    
    public static Doublet weightedMedian(Doublet[] a, int l, int r){
        //base case
        if (l == r)
            return (Doublet)dselect(a, l);
        
        //ith statistic, choose to be middle ith.
        int i = (l+r)/2;
        
        //a will be rearranged so that d is in its proper ith position and every
        //element to the left will be less than, and every element to the right
        //will be greater than d.
        Doublet d = (Doublet)dselect(a, i);
        
        int fullSum  = weightedSum(a, 0, a.length-1);
        int rightSum = weightedSum(a, i+1, a.length-1);
        int leftSum  = weightedSum(a, 0, i-1);
        
        //recurse on left half
        if (leftSum > fullSum/2)
            return weightedMedian(a, l, i-1);
        
        //recurse on right half
        if (rightSum > fullSum/2)
            return weightedMedian(a, i+1, r);
        
        //we got lucky, d is a weighted median
        return d;
    }
    
    /**
     * Sum of weights from l to r inclusive.
     * @param a
     * @param l
     * @param r
     * @return 
     */
    private static int weightedSum(Doublet[] a, int l, int r){
        int result = 0;
        for (int i = l; i <= r; i++)
            result += a[i].W;
        return result;
    }
}
