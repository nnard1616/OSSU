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
 * File:   UGraph.h
 * Author: Nathan Nard
 *
 * Created on July 3, 2018, 6:13 PM
 */

#ifndef UGRAPH_H
#define UGRAPH_H

#include <string>
#include <sstream>
#include "Edge.h"
#include "Node.h"

using namespace std;
//
//class UGraph {
//public:
//    //Constructors
//    UGraph(std::string filename);
//    UGraph(const UGraph& orig);
//    
//    //Destructor
////    virtual ~UGraph();
//    
//    //public methods
//    int numberOfNodes();
//    int numberOfEdges();
//    void addAdjacency(int value, vector<int> neighbors);
//    int minCut();
//    void contract(int one, int two);
//    
//    //operators
//    friend std::ostream& operator<<  (std::ostream& os, UGraph &g);
//    
//private:
//    //Attributes
//    vector<Node> nodes;
//    vector<Edge> edges;
//    
//    //private methods
//    void readInData(std::string filename);
//    void contract(Edge &e);
//    Node createOrFetchNode(int value);
//    Edge createOrFetchEdge(Node &one, Node &two);
//    
//};
//
//vector<std::string> split(const std::string& s, char delim);
//
//vector<int> strings_to_ints(vector<std::string> in);

#endif /* UGRAPH_H */

