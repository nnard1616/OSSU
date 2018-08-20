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

/* 
 * File:   heapp.hpp
 * Author: Nathan Nard
 *
 * Created on August 19, 2018, 10:38 AM
 */
#ifndef HEAPP_HPP
#define HEAPP_HPP

#include "WeightedTreeNode.h"
#include <math.h>
#include <iostream>
using std::ostream;
using std::endl;
using std::pair;

template <class Comparable, class Compare = std::less<Comparable> >
class heapp {
public:
//    heapp();
//    heapp(const heapp& orig);
    
    Comparable top();
    void pop();
    void insert(Comparable object);
    int size();
    
    template<class AnyComparable, class AnyCompare>
    friend ostream& operator<< (ostream& os, const heapp<AnyComparable, AnyCompare>& h);
private:
    pair<int, int> children(int i);
    int parent(int i);
    void swap (int i, int j);
    
    int end = 0;
    Comparable objects[1000000];
};


/******************************************************************************/
/*  Implementation                                                            */
/******************************************************************************/


template <class Comparable, class Compare>
Comparable heapp<Comparable, Compare>::top(){
    return objects[0];
}

template <class Comparable, class Compare>
void heapp<Comparable, Compare>::pop(){
    
    if (end > 0){
        swap(0, end-1);
        end--;
    } else {
        end--;
        return;
    }
    
    
    Compare compare = Compare();
    
    int i = 0;
    pair<int, int> cs = children(i);
    int child1 = cs.first;
    int child2 = cs.second;
    
    
    while ((i < end) && (compare(objects[child1], objects[i]) || 
                         compare(objects[child2], objects[i])   )  ){
        cs = children(i);
        child1 = cs.first;
        child2 = cs.second;
        
        if (child1 >= end || child2 >= end)
            break;
        
        if (compare(objects[child1], objects[child2])){
            swap(child1, i);
            i = child1;
        } else {
            swap(child2, i);
            i = child2;
        }
    }
}

template <class Comparable, class Compare>
void heapp<Comparable, Compare>::insert(Comparable object){
    Compare compare = Compare();
    
    //put object in at end.
    objects[end] = object;
    
    if (end == 0){
        end++;
        return;
    }
    
    
    int c  = end;
    int p = parent(end);
    
    //while child is less than parent...
    while (  compare(objects[c], objects[p])){
        
        swap(c, p);
        c = p;
        p = parent(p);
        
        //check if both p and c pointers are at the top of the array.
        if (p == 0 && c == 0)
            break;
    }
    
    end++;    
}

template <class Comparable, class Compare>
int heapp<Comparable, Compare>::size(){
    return end;
}


template <class Comparable, class Compare>
pair<int, int> heapp<Comparable, Compare>::children(int i){
    pair<int, int> result;
    result.first  = 2*i+1;
    result.second = 2*i+2;
    return result;
}

template <class Comparable, class Compare>
int heapp<Comparable, Compare>::parent(int i){
    return (i-1)/2;
}

template <class Comparable, class Compare>
void heapp<Comparable, Compare>::swap(int i, int j){
    Comparable temp = objects[i];
    objects[i] = objects[j];
    objects[j] = temp;
}


template <class Comparable, class Compare>
ostream& operator<< (ostream& os, const heapp<Comparable, Compare>& h){
    int c = 1;
    for (int i = 0 ; i < h.end; i++){
        os << h.objects[i] << ' ';
        if  (i+2 == pow(2,c)){
            os << endl;
            c++;
        }
    }
    
    return os;
}



#endif