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
 * File:   DGraph.cpp
 * Author: Nathan Nard
 * 
 * Created on July 5, 2018, 4:37 PM
 */

#include "DGraph.h"
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

DGraph::DGraph(string filename) {
    readInData(filename);
}

DGraph::DGraph(const DGraph& orig) {
}

DGraph::~DGraph() {
}

int DGraph::numberOfEdges() {
    return edges.size();
}

int DGraph::numberOfNodes() {
    return nodes.size();
}



void DGraph::readInData(string filename) {
    
    map<int, Node> memo;
    
    nodes.clear();
    edges.clear();
    
    ifstream infile(filename);
    string line;
    
    vector<int> pair;
    
    while (getline(infile,line)){
        pair = strings_to_ints(split(line, ' '));
        
        int mInt = pair.at(0);
        int nInt = pair.at(1);
        
        
        try{
            memo.at(mInt);
        } catch(out_of_range){
            memo[mInt] = Node(mInt);
            nodes.push_back(memo[mInt]);
        }
        
        try{
            memo.at(nInt);
        } catch(out_of_range){
            memo[nInt] = Node(nInt);
            nodes.push_back(memo[nInt]);
        }
        
        edges.push_back(Edge(&memo[mInt], &memo[nInt]));
        
        pair.clear();
    }
    
}