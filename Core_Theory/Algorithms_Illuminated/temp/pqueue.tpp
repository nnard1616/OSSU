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

#include <vector>
#include "pqueue.h"

template <typename Comparable>
using itr = typename vector<Comparable>::iterator; 

template <typename Comparable>
pqueue<Comparable>::pqueue() {
}

template <typename Comparable>
pqueue<Comparable>::pqueue(vector<Comparable> objects) {
    this->objects.swap(objects);
}

template<typename Comparable>
Comparable pqueue<Comparable>::top(){
    return objects.front();
}

template<typename Comparable>
void pqueue<Comparable>::pop() {
    objects.erase(objects.begin());
}

template<typename Comparable>
vector<Comparable> pqueue<Comparable>::getObjects() {
    return objects;
}


template<typename Comparable>
typename vector<Comparable>::iterator pqueue<Comparable>::binarySearch(Comparable object) {
    typename vector<Comparable>::iterator low  = objects.begin();
    typename vector<Comparable>::iterator high = objects.end() - 1;
    typename vector<Comparable>::iterator mid  = objects.begin();
    
    // if array empty
    if (objects.empty())
        return objects.begin();
    
    // if object is smaller than first item in array
    if (object < objects[0])
        return objects.begin();
    
    // if object is greater than last item in array
    if (object > objects[objects.size()-1])
        return objects.end();
    
    // object is between low and high bounds, search for it...
    while (low <= high){
        mid = std::advance(mid, std::distance(low, high)/2);
        
        if (*mid < object)
            low = mid++;
        else if (*mid > object)
            high = mid--;
        else
            return mid;
    }
    
    //object was not present in array, and is between the bounds
    return std::advance(mid, std::distance(low, high)/2) + 1;
}

