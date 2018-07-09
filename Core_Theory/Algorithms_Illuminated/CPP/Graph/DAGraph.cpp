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
 * File:   DAGraph.cpp
 * Author: Nathan Nard
 * 
 * Created on July 6, 2018, 11:51 AM
 */

#include "DAGraph.h"
#include "StaticFunctions.h"


DAGraph::DAGraph(string filename) {
    readInData(filename);
}

DAGraph::DAGraph(const DAGraph& orig) {
    edges = orig.edges;
    nodes = orig.nodes;
    adjacencyList = orig.adjacencyList;
}

DAGraph::~DAGraph() {
}

void DAGraph::readInData(string filename) {
    cout << "reading data..." << endl;
    adjacencyList.clear();
    nodes = 0;
    edges = 0;
    
    ifstream infile(filename);
    string line;
    
    vector<int> pair;
    
    while (getline(infile,line)){
        pair = strings_to_ints(split(line, ' '));
        
        int mInt = pair.at(0);
        int nInt = pair.at(1);
        
        
        adjacencyList[mInt].insert(nInt);
        edges++;
        
        pair.clear();
    }
    nodes = adjacencyList.size();
    cout << "Data read. " << endl << "Nodes: " << adjacencyList.size() << "Edges: " << edges << endl;
    for (auto pair : adjacencyList)
        cout << pair.first << ' ';
    cout << endl;
}

map<int, set<int> > DAGraph::reverseArcs(const map<int, set<int> >& al) {
    map<int, set<int>> ral;
    
    for (auto pair : al)
        for ( int i : pair.second)
            ral[i].insert(pair.first);
    
    return ral;
}



vector<int> DAGraph::DFS(int n) {
    vector<int> v; // stuff gets added to in "postorder"
    set<int> memo; //stuff gets added to in "DFS"
    
    while (v.size() != nodes){
        postOrder(n, v, memo, adjacencyList);
        while (memo.find(n) != memo.end())
            n--;
    }
    
    return v;
}

void DAGraph::postOrder(int n, vector<int>& v, set<int>& memo, map<int, set<int>>& m) {
    memo.insert(n);
    set<int>* s = &m[n];
    
    for (int a : *s){
        if (memo.find(a) == memo.end()){
            postOrder(a, v, memo, m);
        }
    }
    v.push_back(n);
}


ostream& operator<< (ostream& os, const map<int, set<int>>& m){
    for (const auto& pair : m){
        os << pair.first << ' ';
        for (int n : pair.second)
            os << n << ' ';
        os << endl;
    }
    return os;
}

int DAGraph::SCCcount() {
    cout << "Mapping..." << endl;
    //map nodes to DFS finish times (from DFS)
    vector<int> d = DFS(nodes); //assuming nodes 1, 2, 3, ..., n
    map<int, int> finishTimes;
    
    for (int i = 1; i <= d.size(); i++)
        finishTimes[ d[i-1] ] = i;  
        
    cout << "Mapping done." << endl;
    //transform adjacencyList using map
    cout << "Transforming..." << endl;
    map<int, set<int>> transformed;
    
    for (auto& pair : adjacencyList)
        for (int i : pair.second)
            transformed[finishTimes[pair.first]].insert(finishTimes[i]);
    
    
    //reverse arcs
    transformed = reverseArcs(transformed);
    
    cout << "Transforming done.  Now counting cycles..." <<endl;
    //count cycles
    return DFScount(transformed);
}

int DAGraph::DFScount(map<int, set<int> >& m) {
    vector<int> v; // stuck gets added to in "postorder"
    set<int> memo; //stuff gets added to in "DFS"
    int n = m.size();
    
    int c = 0;
    while (v.size() != nodes){
        c++;
        postOrder(n, v, memo, m);
        while (memo.find(n) != memo.end())
            n--;
    }
    return c;
}


ostream& operator<< (ostream& os, const DAGraph& g ){
    for (const auto& pair : g.getAdjacencyList()){
        os << pair.first << ' ';
        for (int n : pair.second)
            os << n << ' ';
        os << endl;
    }
    return os;
}

map<int, set<int> > DAGraph::getAdjacencyList() const {
    return adjacencyList;
}

int DAGraph::getEdges() const {
    return edges;
}

int DAGraph::getNodes() const {
    return nodes;
}

