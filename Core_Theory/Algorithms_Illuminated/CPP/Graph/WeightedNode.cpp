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
 * File:   WeightedNode.cpp
 * Author: Nathan Nard
 * 
 * Created on July 10, 2018, 4:08 PM
 */

#include "WeightedNode.h"


/******************************************************************************/
/*  Constructors/Destructor                                                   */
/******************************************************************************/

WeightedNode::WeightedNode(int value){
    setValue(value);
    setVisited(false);
}

WeightedNode::WeightedNode(const WeightedNode& orig) {
}

WeightedNode::~WeightedNode() {
}


/******************************************************************************/
/*  Getters/Setters                                                           */
/******************************************************************************/

unsigned int WeightedNode::getValue() const {
    return value;
}

void WeightedNode::setValue(int i) {
    value = i;
}

set<pair<WeightedNode*, int>*>* WeightedNode::getNeighbors() {
    return &neighborWeights;
}

bool WeightedNode::allNeighborsVisited() {
    for (auto& i : neighborWeights)
        if ( ! i->first->isVisited())
            return false;
    return true;
}

bool WeightedNode::isVisited() const { 
    return visited;
}

void WeightedNode::setVisited( bool b){
    visited = b;
}

int WeightedNode::getDistance() const {
    return distance;
}

void WeightedNode::setDistance(int i) {
    distance = i;
}

WeightedNode* WeightedNode::getPreviousOptimalNeighbor() {
    return previousOptimalNeighbor;
}

void WeightedNode::setPreviousOptimalNeighbor(WeightedNode* p) {
    previousOptimalNeighbor = p;
}

void WeightedNode::addNeighbor(pair<WeightedNode*, int>* n){
    neighborWeights.insert(n);
}


/******************************************************************************/
/*  Operators                                                                 */
/******************************************************************************/

bool WeightedNode::operator==(const WeightedNode& n1) {
    return value == n1.getValue();
}

ostream& operator<<(ostream& os, const WeightedNode& n) {
    os << n.getValue() << ' ';
    for (auto i : n.neighborWeights)
        os << i->first->getValue() << ',' << i->second << ' ';
    
    return os;
}