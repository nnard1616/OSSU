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
 * File:   EdgeComparator.h
 * Author: Nathan Nard
 *
 * Created on July 26, 2018, 5:21 PM
 */

#ifndef EDGECOMPARATOR_H
#define EDGECOMPARATOR_H
#include "PrimEdge.h"
#include <typeinfo>
#include <iostream>
using std::cout;
using std::endl;

#include <string.h>



template <class T> struct PrimEdgeComparator {
    bool operator() ( T* x,  T* y) {
        if (strcmp ( typeid(T).name(), "PrimEdge")){
            if (x->oneVisited() && ! y->oneVisited())
                return true;
            if (! x->oneVisited() && y->oneVisited())
                return false;
            return x->getWeight() < y->getWeight();
            
        }
        else
            throw std::string("PrimEdgeComparator may only be used with PrimEdge objects!");
    }
};

template <class T> struct KruskalEdgeComparator {
    bool operator() ( T* x,  T* y) {
        
        if (strcmp ( typeid(T).name(), "PrimEdge")){
            
            if (x->differentLeaderNodes() && y->sameLeaderNodes())
                return true;
            if (x->sameLeaderNodes() && y->differentLeaderNodes())
                return false;
            return *x < *y;
        }
        else
            throw std::string("KruskalEdgeComparator may only be used with PrimEdge objects!");
    }
};

#endif /* EDGECOMPARATOR_H */

