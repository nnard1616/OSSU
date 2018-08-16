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
 * File:   PrimNode.h
 * Author: Nathan Nard
 *
 * Created on July 26, 2018, 3:47 PM
 */

#ifndef PRIMNODE_H
#define PRIMNODE_H
#include <map>
#include <fstream>
#include "PrimEdge.h"
#include "EdgeComparators.h"

using namespace std;





class PrimEdge;

class PrimNode {
public:
    PrimNode(int value);
    
    //make edge in imp
    void addNeighbor(PrimNode* n, PrimEdge* p);
    
    
    int getValue() const;
    map<PrimEdge*, PrimNode*, PrimEdgeComparator<PrimEdge>> getNeighbors() const;
    
    PrimNode* getNeighbor(PrimEdge* e);
    PrimNode* getLeader();
    void setLeader(PrimNode* p);
    
    PrimEdge* getMinEdge() const;
    
    bool isVisited();
    void setVisited(bool b);
    
    friend ostream& operator<< (ostream& os, const PrimNode& n);
private:

    PrimNode* leader;
    bool visited;
    int value;
    map<PrimEdge*, PrimNode*, PrimEdgeComparator<PrimEdge>> neighbors;
    
};

#endif /* PRIMNODE_H */

