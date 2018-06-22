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

/**
 *
 * @author Nathan Nard
 */
public class QuickSort {
    public static int[] quickSort(int[] a, int b, int e){
        int pindex = (b+e)/2;
        int p = a[pindex];
        int[] result;
        int t;
        
        for (int i = 0; i < a.length; i++){
            if (i < pindex){
                if (a[i] > p){
                    
                    //swap
                    t = a[i];
                    a[i] = p;
                    a[pindex] = t;
                    
                    //update pindex
                    pindex = i;
                    
                    continue;
                }
            }
            
            if (i > pindex){
                if (a[i] < p){
                    
                    //swap
                    t = a[i];
                    a[i] = p;
                    a[pindex] = t;
                    
                    //update pindex
                    pindex = i;
                }
            }
        }
        
        printArray(a);
        
        
        return null;
    }
    
    public static void printArray(int[] a){
        String result = "";
        for (int i: a){
            result += i + " ";
        }
        System.out.println(result);
    }
}
