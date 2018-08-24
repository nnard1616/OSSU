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

#include <map>
using std::map;

#include <vector>
using std::vector;

template <class Comparable, class Compare = std::less<Comparable> >
class heapp {
public:
//    heapp();
//    heapp(const heapp& orig);
    
    Comparable top();
    void pop();
    void insert(Comparable object);
    int size() const;
    void update(Comparable object);
    Comparable at(int i);
    int index(Comparable object);
    bool empty();
    
    template<class AnyComparable, class AnyCompare>
    friend ostream& operator<< (ostream& os, const heapp<AnyComparable, AnyCompare>& h);
private:
    pair<int, int> children(int i);
    int parent(int i);
    void swap (int i, int j);
    void swapIndices(Comparable i, Comparable j);
    
    vector<Comparable> objects;
    map<Comparable, int> indices;
};


/******************************************************************************/
/*  Implementation                                                            */
/******************************************************************************/


template <class Comparable, class Compare>
Comparable heapp<Comparable, Compare>::top(){
    try{
        return objects.at(0);
    } catch (std::out_of_range) {
        cout << "Vector is empty!" << endl;
        throw;
    }
}

template <class Comparable, class Compare>
void heapp<Comparable, Compare>::pop(){
    
    if ( ! objects.empty() ){
        swap(0, objects.size()-1);
        indices.erase(objects.back());
        objects.erase(objects.end()-1);
    } else {
        cout << "Vector is empty! Nothing to pop." << endl;
        return;
    }
    
    
    Compare compare = Compare();
    
    int i = 0;
    pair<int, int> cs = children(i);
    int child1 = cs.first;
    int child2 = cs.second;
    
    
    while ((i < objects.size()) && (compare(objects[child1], objects[i]) || 
                                    compare(objects[child2], objects[i])   )  ){
        cs = children(i);
        child1 = cs.first;
        child2 = cs.second;
        
        if (child1 >= objects.size() || child2 >= objects.size()) //maybe bug?
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
    objects.push_back(object);
    indices[object] = objects.size()-1;
    
    if (objects.size() == 1)
        return;
    
    
    int c  = objects.size() - 1;
    int p = parent(c);
    
    //while child is less than parent...
    while (  compare(objects[c], objects[p])){
        
        swap(c, p);
        c = p;
        p = parent(p);
        
        //check if both p and c pointers are at the top of the array.
        if (p == 0 && c == 0)//maybe bug??
            break;
    }
}

template <class Comparable, class Compare>
int heapp<Comparable, Compare>::size() const{
    return objects.size();
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
    swapIndices(objects[i], objects[j]);
}


template <class Comparable, class Compare>
ostream& operator<< (ostream& os, const heapp<Comparable, Compare>& h){
    int c = 1;
    for (int i = 0 ; i < h.size(); i++){
        os << h.objects[i] << ' ';
        if  (i+2 == pow(2,c)){
            os << endl;
            c++;
        }
    }
    
    return os;
}

template <class Comparable, class Compare>
void heapp<Comparable, Compare>::swapIndices(Comparable i, Comparable j){
    try{
        int temp1 = indices.at(i);
        int temp2 = indices.at(j);
        
        if (objects[temp1] != j){
            cout << "Mismatch of first indices!" << endl;
            return;
        }
        if (objects[temp2] != i){
            cout << "Mismatch of second indices!" << endl;
            return;
        } 
        
        indices[j] = temp1;
        indices[i] = temp2;
    } catch (std::out_of_range) {
        cout << "Can't swap indices of items that don't exist!" << endl;
        cout << i << " " << j << endl;
    } 
}


template <class Comparable, class Compare>
void heapp<Comparable, Compare>::update(Comparable object){
    
    Compare compare = Compare();
    int index = indices[object];
    // case where object became too small
    
    // while object is less than its parent, swap it with its parent.
    while (compare(object, objects[parent(index)])){
        
        swap(index, parent(index));
        index = indices[object];
        
    }
    
    //1 child
    if (children(index).first == size()-1){
        if (compare(objects[children(index).first], object)){
            swap(index, children(index).first);
            index = indices[object];
        }
        return;
    }

    //2 children
    if (children(index).second == size() - 1){
        if (compare(objects[children(index).first], object) || compare(objects[children(index).second], object) ){
            if (compare(objects[children(index).first], objects[children(index).second]) ){
                swap(index, children(index).first);
            } else { // right child is less than left child.
                swap(index, children(index).second);
            }
            index = indices[object];
        }
        return;
    }

    //0 children
    if (children(index).first >= size()){
        return;
    }
    
    //case where object became too big
    while (compare(objects[children(index).first], object) || compare(objects[children(index).second], object)){
        //if left child is less than right child
        if (compare(objects[children(index).first], objects[children(index).second]) ){
            swap(index, children(index).first);
        } else { // right child is less than left child.
            swap(index, children(index).second);
        }
        index = indices[object];
        
        // check if near bottom of tree (0, 1 or 2 children)
        
        //1 child
        if (children(index).first == size()-1){
            if (compare(objects[children(index).first], object)){
                swap(index, children(index).first);
                index = indices[object];
            }
            break;
        }
        
        //2 children
        if (children(index).second == size() - 1){
            if (compare(objects[children(index).first], object) || compare(objects[children(index).second], object) ){
                if (compare(objects[children(index).first], objects[children(index).second]) ){
                    swap(index, children(index).first);
                } else { // right child is less than left child.
                    swap(index, children(index).second);
                }
                index = indices[object];
            }
            break;
        }
        
        //0 children
        if (children(index).first >= size()){
            break;
        }
    }
}

template <class Comparable, class Compare>
Comparable heapp<Comparable, Compare>::at(int i){
    return objects[i];
}

template <class Comparable, class Compare>
int heapp<Comparable, Compare>::index(Comparable object){
    try{
        return indices.at(object);
    } catch (std::out_of_range) {
        return -1;
    }
}

template <class Comparable, class Compare>
bool heapp<Comparable, Compare>::empty(){
    return objects.empty();
}

#endif