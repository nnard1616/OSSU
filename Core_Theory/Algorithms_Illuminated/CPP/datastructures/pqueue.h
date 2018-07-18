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
    
    //needed by push operation
    typename vector<Comparable>::iterator binarySearch(Comparable object);
    
private:
    
    vector<Comparable> objects;
};

#include "pqueue.tpp"

#endif /* PQUEUE_H */