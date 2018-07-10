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
 * File:   DirectedGraph.h
 * Author: Nathan Nard
 *
 * Created on July 8, 2018, 1:09 PM
 */

#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H
#include "Node.h"
#include <fstream>
#include <string>
#include <map>
#include <queue>

using namespace std;

class DirectedGraph {
public:
    //Constructors & Destructor
    DirectedGraph(string filename);
    DirectedGraph(const DirectedGraph& orig);
    virtual ~DirectedGraph();
    
    int getEdges() const;
    int getNodes() const;
    
    void setAllVisited();
    void setAllNotVisited();
    bool areAllVisited();
    bool areAllNotVisited();

    
    void readInData(string filename);
    void findSCCs();
    
    friend ostream& operator<< (ostream& os, const DirectedGraph& g);
    
private:
    int edges;
    int nodes;
    map<int, Node*> nodeList;
    map<int, int> nToFinishTime;
    
    map<int, Node*> reverseArcsAndTransform(const map<int, Node*>& al);
    void DFS(Node* n, int& counter);
    void DFSOnOriginal();
    priority_queue<int> DFSOnReversedTransform();
};

#endif /* DIRECTEDGRAPH_H */

