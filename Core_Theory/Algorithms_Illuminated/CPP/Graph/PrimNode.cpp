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
 * File:   PrimNode.cpp
 * Author: Nathan Nard
 * 
 * Created on July 26, 2018, 3:47 PM
 */

#include "PrimNode.h"

PrimNode::PrimNode(int value) {
    this->value = value;
    this->visited = false;
}

void PrimNode::addNeighbor(PrimNode* n, PrimEdge* p) {
    neighbors[p] = n;
}

PrimEdge* PrimNode::getMinEdge() const {
    auto itr = neighbors.begin();
    
    while (itr != neighbors.end()){
        if ( ! itr->second->isVisited())
            return itr->first;
        itr++;
    }
    
    return nullptr;
}

bool PrimNode::isVisited() {
    return visited;
}

void PrimNode::setVisited(bool b) {
    visited = b;
}

int PrimNode::getValue() const {
    return value;
}

map<PrimEdge*, PrimNode*, EdgeComparator<PrimEdge>> PrimNode::getNeighbors() const {
    return neighbors;
}

PrimNode* PrimNode::getNeighbor(PrimEdge* e) {
    try{
        return neighbors.at(e);
    } catch (out_of_range){
        return nullptr;
    }
}

ostream& operator<< (ostream& os, const PrimNode& n){
    os << n.getValue() << ' ';
    for (auto& i : n.getNeighbors()){
        os << i.second->getValue() << ',' << *i.first << ' ';
    }
    return os;
}


