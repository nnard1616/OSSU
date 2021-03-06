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
 * File:   DirectedWeightedGraph.h
 * Author: Nathan Nard
 *
 * Created on July 13, 2018, 10:51 AM
 */

#ifndef DIRECTEDWEIGHTEDGRAPH_H
#define DIRECTEDWEIGHTEDGRAPH_H

#include "WeightedNode.h"
#include "StaticFunctions.h"
#include "DistanceComparator.h"
#include "../datastructures/pqueue.h"

#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <queue>

using namespace std;

class DirectedWeightedGraph {
public:
    
    //Constructors & Destructor
    DirectedWeightedGraph(string filename);
    DirectedWeightedGraph(const DirectedWeightedGraph& orig);
    virtual ~DirectedWeightedGraph();
    
    //getters and setters
    int getEdges() const;
    int getNodes() const;
    int numberOfEdges();
    
    string getOptimalPath(int n);
    string getAnswerPT2WK2();
    
    int getMinPath();
    void printMinPath(int end);
    void printMinPath2(int start);
    void computeMinPath(int start);
    
    map<int, WeightedNode*> getNodeList();
    
    void setAllVisited();
    void setAllNotVisited();
    bool areAllVisited();
    bool areAllNotVisited();
    void resetAllOptimalPreviousNeighbors();
    
    void printPathScores();
    
    //shortest paths solver, n is starting point node
    void dijkstra(int n);
    bool bellmanford(int n);
    bool johnsonSimplified();
    bool johnson();
    void flloydwarshall();
    
    friend ostream& operator<< (ostream& os, const DirectedWeightedGraph& g);
    
    void readInDataPT2WK2();
    void readInDataPT4WK1();
    
    void printDistances(int start);
    void resetDistances();
private:
    int edges;
    int nodes;
    int minPath = INT32_MAX;
    bool negativeEdgeWeightsPresent = false;
    string filename;
    map<int, WeightedNode*> nodeList;
    
    
    
};

#endif /* DIRECTEDWEIGHTEDGRAPH_H */

