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
 * File:   UndirectedWeightedGraph.h
 * Author: Nathan Nard
 *
 * Created on July 25, 2018, 5:58 PM
 */

#ifndef UNDIRECTEDWEIGHTEDGRAPH_H
#define UNDIRECTEDWEIGHTEDGRAPH_H

#include "PrimNode.h"
#include "PrimEdge.h"
#include "StaticFunctions.h"
#include "EdgeComparators.h"
#include "../datastructures/pqueue.h"

#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <iterator>

using namespace std;

class UndirectedWeightedGraph {
public:
    
    //Constructors & Destructor
    UndirectedWeightedGraph(string filename);
    
    bool areAllVisited();
    
    //for debugging
    map<int, PrimNode*> getNodeList();
    
    int prim();
    int kspacing(int k);
    int findKWithSpacingOfThree();
    
    int sumMin();
    PrimEdge* findNextMinEdge(set<PrimEdge*, PrimEdgeComparator<PrimEdge>>::iterator itr);
    void printMinTree();
    
    friend ostream& operator<< (ostream& os, const UndirectedWeightedGraph& g);
    
private:
    int edges;
    int nodes;
    map<int, PrimNode*> nodeList;
    map<int, PrimNode*> visitedNodeList;
    map<int, PrimNode*> unvisitdedNodeList;
    pqueue<PrimEdge*, PrimEdgeComparator<PrimEdge>> edgeList;
    pqueue<PrimEdge*, PrimEdgeComparator<PrimEdge>> minCostEdgeList;
    
    void readInData(string filename);
};

#endif /* UNDIRECTEDWEIGHTEDGRAPH_H */

