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
 * File:   WeightedNode.h
 * Author: Nathan Nard
 *
 * Created on July 10, 2018, 4:08 PM
 */

#ifndef WEIGHTEDNODE_H
#define WEIGHTEDNODE_H

#include <map>
#include <set>
#include <iostream>

using namespace std;

class WeightedNode{
public:
    
    //constructors and destructor
    WeightedNode():WeightedNode(0){}
    WeightedNode(int value);
    WeightedNode(const WeightedNode& orig);
    virtual ~WeightedNode();
    
    //Getters & Setters
    unsigned int getValue () const;
    int getDistance () const;
    set<pair<WeightedNode*, int>*>* getNeighbors();
    WeightedNode* getPreviousOptimalNeighbor();
    
    bool isVisited() const;
    bool allNeighborsVisited();
    
    void setValue (int i) ;
    void setVisited( bool b);
    void setDistance(int i);
    
    void setPreviousOptimalNeighbor(WeightedNode* p);
    
    void addNeighbor(pair<WeightedNode*, int>* n);
    
    //Operators
    bool operator==  (const WeightedNode &n1);
    friend ostream& operator<<  (ostream& os, const WeightedNode& n);
    
private:
    unsigned int value;
    bool visited;
    
    set<pair<WeightedNode*, int>*> neighborWeights;
    unsigned int distance = 1000000;
    
    WeightedNode* previousOptimalNeighbor;

};

#endif /* WEIGHTEDNODE_H */