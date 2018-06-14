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
package part1.ch1;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.ListIterator;

/**
 *
 * @author Nathan Nard
 */
public class MergeSort {
    /**
     * Assumes list has a size that is a power of 2.
     * @param inlist
     * @return 
     */
    public static List<Comparable> mergeSort(List<Comparable> inlist){
        List<Comparable> result;
        
        //base case: list with two items
        if (inlist.size() == 2 ){
            if (inlist.get(0).compareTo(inlist.get(1)) > 0)
                Collections.reverse(inlist);
            return inlist;
        }
        
        //divide list into two
        List<Comparable> l1 = inlist.subList(0, inlist.size()/2);
        List<Comparable> l2 = inlist.subList(inlist.size()/2, inlist.size());
        
        //perform merge sort on both halves
        l1 = mergeSort(l1);
        l2 = mergeSort(l2);
        
        //merge the two lists
        result = merge(l1,l2);
        return result;
    }
    
    /**
     * Merges two lists in ascending order.
     * @param list1
     * @param list2
     * @return 
     */
    public static List<Comparable> merge(List<Comparable> list1, List<Comparable> list2){
        List<Comparable> result = new ArrayList<>();
        
        ListIterator<Comparable> itr1 = list1.listIterator();
        ListIterator<Comparable> itr2 = list2.listIterator();
        
        while(itr1.hasNext() || itr2.hasNext()){
            while(!itr1.hasNext() && itr2.hasNext()){
                Comparable item2 = itr2.next();
                result.add(item2);
            }
            
            while(itr1.hasNext() && !itr2.hasNext()){
                Comparable item1 = itr1.next();
                result.add(item1);
            }
            
            while(itr1.hasNext() && itr2.hasNext()){
                Comparable item1 = itr1.next();
                Comparable item2 = itr2.next();
                
                if (item1.compareTo(item2) < 0){
                    result.add(item1);
                    itr2.previous();
                }else{
                    result.add(item2);
                    itr1.previous();
                }
            }
        }
        return result;
    }
    
    public static void printList(List<Comparable> inlist){
        String result = "";
        
        for (Object o : inlist){
            result += o.toString() + " ";
        }
        
        System.out.println(result);
    }
}
