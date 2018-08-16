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
 * File:   pqueue.h
 * Author: Nathan Nard
 *
 * Created on July 16, 2018, 3:34 PM
 */

#ifndef PQUEUE_H
#define PQUEUE_H
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

//priority queue with an updater function should an object change.
template <class Comparable, class Compare = std::less<Comparable> >
class pqueue {
public:
    
    //constructors
    pqueue();
    pqueue(vector<Comparable> objects);
    
    //getters
    vector<Comparable> getObjects();
    bool empty();
    int size();
    Comparable top();
    
    //container operations
    void push(Comparable object);
    void pop();
    void update();
    typename vector<Comparable>::iterator insert(typename vector<Comparable>::const_iterator pos, typename vector<Comparable>::iterator begin, typename vector<Comparable>::iterator end);
    
    //needed by push operation
    typename vector<Comparable>::iterator binarySearch(Comparable object);
    
    typename vector<Comparable>::iterator begin();
    typename vector<Comparable>::iterator end();
    
    const Comparable& operator[](unsigned int i) const {return objects[i];}
private:
    
    vector<Comparable> objects;
};


/******************************************************************************/
/*  Constructors                                                              */
/******************************************************************************/

template <class Comparable, class Compare> 
pqueue<Comparable, Compare>::pqueue() {
}

template <class Comparable, class Compare> 
pqueue<Comparable, Compare>::pqueue(vector<Comparable> objects) {
    this->objects.swap(objects);
}


/******************************************************************************/
/*  Getters                                                                   */
/******************************************************************************/

template <class Comparable, class Compare> 
Comparable pqueue<Comparable, Compare>::top(){
    return objects.front();
}

template <class Comparable, class Compare> 
vector<Comparable> pqueue<Comparable, Compare>::getObjects() {
    return objects;
}

template<class Comparable, class Compare>
bool pqueue<Comparable, Compare>::empty() {
    return objects.empty();
}

template<class Comparable, class Compare>
int pqueue<Comparable, Compare>::size() {
    return objects.size();
}

template<class Comparable, class Compare>
typename vector<Comparable>::iterator pqueue<Comparable, Compare>::begin() {
    return objects.begin();
}

template<class Comparable, class Compare>
typename vector<Comparable>::iterator pqueue<Comparable, Compare>::end() {
    return objects.end();
}


/******************************************************************************/
/*  Container Operations                                                      */
/******************************************************************************/

template <class Comparable, class Compare> 
void pqueue<Comparable, Compare>::pop() {
    objects.erase(objects.begin());
}

template <class Comparable, class Compare> 
void pqueue<Comparable, Compare>::push(Comparable object) {
    objects.insert(binarySearch(object), object);
}

template<class Comparable, class Compare>
void pqueue<Comparable, Compare>::update() {
    std::sort(objects.begin(), objects.end(), Compare());
}

template<class Comparable, class Compare>
typename vector<Comparable>::iterator pqueue<Comparable, Compare>::insert(typename vector<Comparable>::const_iterator pos, typename vector<Comparable>::iterator begin, typename vector<Comparable>::iterator end) {
    auto returnIterator = objects.insert(pos, begin, end);
    update();
    return returnIterator;
}


template <class Comparable, class Compare> 
typename vector<Comparable>::iterator pqueue<Comparable, Compare>::
binarySearch(Comparable object) {
    
    typename vector<Comparable>::iterator low  = objects.begin();
    typename vector<Comparable>::iterator high = objects.end() - 1;
    typename vector<Comparable>::iterator mid  = objects.begin();
    
    //initialize comparator
    Compare compare = Compare();
    
    // if array empty
    if (objects.empty())
        return objects.begin();
    
    // if object is smaller than first item in array
    if (compare(object, *low))
        return objects.begin();
    
    // if object is greater than last item in array
    if (compare(*high, object))
        return objects.end();
    
    // object is between low and high bounds, search for it...
    while (low <= high){
        
        mid = low + std::distance(low, high)/2 ;
        
        if (compare(*mid, object))
            low = mid+1;
        else if (compare(object, *mid))
            high = mid-1;
        else
            return mid;
        
    }
    
    // object was not present in array, 
    // return iterator where it should be inserted.
    return low;
}

#endif /* PQUEUE_H */