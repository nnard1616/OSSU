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
 * File:   WeightComparator.h
 * Author: Nathan Nard
 *
 * Created on July 13, 2018, 11:31 AM
 */

#ifndef WEIGHTCOMPARATOR_H
#define WEIGHTCOMPARATOR_H
#include <string.h>

using namespace std;

template <class T> struct WeightComparator {
    bool operator() (const pair<T*, int>* x, 
                     const pair<T*, int>* y ) {
        return x->second < y->second;
    }
    typedef bool result_type;
};

template <class T> struct WeightedTreeNodeComparator {
    bool operator() ( T* x,  T* y) {
        if (strcmp ( typeid(T).name(), "WeightedTreeNode")){
            return x->getWeight() < y->getWeight();
            
        }
        else
            throw std::string("WeightedTreeNodeComparator may only be used with WeightedTreeNode objects!");
    }
};
#endif /* WEIGHTCOMPARATOR_H */
