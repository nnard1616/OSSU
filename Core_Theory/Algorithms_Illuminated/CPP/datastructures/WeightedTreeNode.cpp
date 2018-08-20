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
 * File:   WeightedTreeNode.cpp
 * Author: Nathan Nard
 * 
 * Created on August 19, 2018, 5:02 PM
 */

#include "WeightedTreeNode.h"

WeightedTreeNode::WeightedTreeNode() {
    this->value = 0;
    this->weight = -1;
}

WeightedTreeNode::WeightedTreeNode(int value, ull weight, WeightedTreeNode* n1, WeightedTreeNode* n2) {
    this->value = value;
    this->weight = weight;
    this->left = n1;
    this->rght = n2;
}

WeightedTreeNode::WeightedTreeNode(int value, WeightedTreeNode* n1, WeightedTreeNode* n2) {
    this->left = n1;
    this->rght = n2;
    this->weight = n1->getWeight() + n2->getWeight();
    this->value = value;
    
    left->incDepths();
    rght->incDepths();
}

WeightedTreeNode::WeightedTreeNode(int value, ull weight) : WeightedTreeNode() {
    this->value = value;
    this->weight = weight;
    this->depth = 0;
}

WeightedTreeNode* WeightedTreeNode::getLeft() {
    return left;
}

WeightedTreeNode* WeightedTreeNode::getRght() {
    return rght;
}

int WeightedTreeNode::getValue() {
    return value;
}

ull WeightedTreeNode::getWeight() {
    return weight;
}

int WeightedTreeNode::getDepth() const {
    return depth;
}

void WeightedTreeNode::incDepths() {
    vector<WeightedTreeNode*> dfs;
    
    dfs.push_back(this);
    
    WeightedTreeNode* current;
    
    while (! dfs.empty()){
        current = dfs.back();
        if (current->getValue() == 0){
            current->incDepth();
            dfs.pop_back();
            dfs.push_back(current->getLeft());
            dfs.push_back(current->getRght());
        } else {
            current->incDepth();
            dfs.pop_back();
        }
    }
}

void WeightedTreeNode::incDepth() {
    depth++;
}


ostream& operator << (ostream& os, const WeightedTreeNode& w){
    os << w.value;
    return os;
}

ostream& operator << (ostream& os, const WeightedTreeNode* w){
    os << w->value;
    return os;
}





