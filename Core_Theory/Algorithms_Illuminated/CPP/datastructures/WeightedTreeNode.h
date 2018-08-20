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
 * File:   WeightedTreeNode.hpp
 * Author: Nathan Nard
 *
 * Created on August 19, 2018, 5:02 PM
 */

#ifndef WEIGHTEDTREENODE_HPP
#define WEIGHTEDTREENODE_HPP

#include "WeightComparator.h"
#include <iostream>
#include <vector>

typedef unsigned long long ull;

class WeightedTreeNode {
public:
    WeightedTreeNode();
    WeightedTreeNode(int value, ull weight);
    WeightedTreeNode(int value, WeightedTreeNode* n1, WeightedTreeNode* n2);
    WeightedTreeNode(int value, ull weight, WeightedTreeNode* n1, WeightedTreeNode* n2);
    
    ull getWeight();
    WeightedTreeNode* getLeft();
    WeightedTreeNode* getRght();
    int getValue();
    int getDepth() const;
    void incDepths();
    void incDepth();
    
    friend ostream& operator<< (ostream& os, const WeightedTreeNode& w);
    friend ostream& operator<< (ostream& os, const WeightedTreeNode* w);
private:
    int value;
    int depth = 0;
    ull weight;
    WeightedTreeNode* left = nullptr;
    WeightedTreeNode* rght = nullptr;
};

#endif /* WEIGHTEDTREENODE_HPP */

