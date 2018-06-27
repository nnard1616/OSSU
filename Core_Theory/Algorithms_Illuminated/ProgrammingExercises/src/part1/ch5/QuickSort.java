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
package part1.ch5;

import java.util.Random;

/**
 *
 * @author Nathan Nard
 */
public class QuickSort {
    private static Random rand = new Random();
    
    public static void quickSort(Comparable[] a, int l, int r){
        //base case
        if (l >= r)
            return;
        
        int i = choosePivot(l, r);
        
        //switches first element with chosen pivot
        swap(a, i, l);
        
        //partition returns index of new pivot, j
        int j = partition(a, l, r);
        
        
        quickSort(a, l, j-1);
        quickSort(a, j+1, r);
        
    }
    
    private static int choosePivot(int l, int r){
        return rand.nextInt(r-l+1)+l;
    }
    
    public static int partition(Comparable[] a, int l, int r){
        Comparable p = a[l];
        int i = l+1;
        
        for (int j = l + 1; j <= r; j++)
            if (a[j].compareTo(p) < 0)
                swap(a, i++, j);
        
        swap(a, l, i-1);
        
        return i-1;
    }
    
    public static void swap(Object[] a, int i, int j){
        Object temp = a[j];
        a[j] = a[i];
        a[i] = temp;
    }
    
    public static void printArray(Object[] a){
        String result = "";
        for (Object i: a){
            result += i + " ";
        }
        System.out.println(result);
    }
}
