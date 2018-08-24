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

#include <stdint.h>
#include <vector>

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



void WeightedNode::createBFWeights() {
    for (auto i : neighborWeights){
        if (this->getValue() == 320 && i->first->getValue() == 225){
            cout << "HERE: " << endl;
            cout <<  i->second << " + " << this->getBF0Distance() << " - " << i->first->getBF0Distance() << " = " << i->second + BF0Distance - i->first->getBF0Distance() << endl;
        }
        neighborToWeightMap[i->first] = i->second + BF0Distance - i->first->getBF0Distance();
        i->second = i->second + BF0Distance - i->first->getBF0Distance();
        
    }
}


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

int WeightedNode::getBF0Distance() const {
    return BF0Distance;
}

void WeightedNode::setBF0Distance(int i) {
    BF0Distance = i;
}

WeightedNode* WeightedNode::getPreviousOptimalNeighbor() {
    return previousOptimalNeighbor;
}

void WeightedNode::setPreviousOptimalNeighbor(WeightedNode* p) {
    previousOptimalNeighbor = p;
}

void WeightedNode::addNeighbor(pair<WeightedNode*, int>* n){
    neighborWeights.insert(n);
    neighborToWeightMap[n->first] = n->second;
}

int WeightedNode::getWeight(WeightedNode* n) {
    try{
        return neighborToWeightMap.at(n);
    } catch (std::out_of_range){
        cout << "Neighbor doesn't exist!" << endl;
        throw;
    }
}

void WeightedNode::addToPath(WeightedNode* n) {
    if (distance > n->getDistance() + n->getWeight(this)){
        path.clear();
        for (auto& i : n->getPath()){
            path.push_back(i);
        }
        path.push_back(n);
    }
    
}

int WeightedNode::sumPath() {
    int result;
    
    if (! path.empty()){
        for (int i = 0; i < path.size()-1; i++){
            result += path[i]->getWeight(path[i+1]);
        }
        result += path.back()->getWeight(this);
        return result;
    } else {
        return distance;
    }
}


vector<WeightedNode*> WeightedNode::getPath() {
    return path;
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

ostream& operator<<(ostream& os, const WeightedNode* n) {
    os << n->getDistance();
    return os;
}