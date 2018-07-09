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
 * File:   DAGraph.h
 * Author: Nathan Nard
 *
 * Created on July 6, 2018, 11:51 AM
 */

#ifndef DAGRAPH_H
#define DAGRAPH_H
#include <map>
#include <set>
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class DAGraph {
public:
    DAGraph(string filename);
    DAGraph(const DAGraph& orig);
    virtual ~DAGraph();
    
    map<int, set<int>> getAdjacencyList() const;
    int getEdges() const;
    int getNodes() const;

    
    void readInData(string filename);
    int SCCcount();//TODO
    
    
    
    friend ostream& operator<< (ostream& os, const DAGraph& g);
private:
    int edges;
    int nodes;
    map<int, set<int>> adjacencyList;
//    map<int, set<int>> DFSLoopAdjacencyList;
    
    map<int, set<int>> reverseArcs(const map<int, set<int>>& al);
    //orders nodes by finish times.
    vector<int> DFS(int n);
    void postOrder(int n, vector<int>& v, set<int>& s, map<int, set<int>>& m);
    
    int DFScount(map<int, set<int>>& m);
    
    
    
    
    
};

#endif /* DAGRAPH_H */

