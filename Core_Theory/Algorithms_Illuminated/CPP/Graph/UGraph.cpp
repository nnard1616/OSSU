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
 * File:   UGraph.cpp
 * Author: Nathan Nard
 * 
 * Created on July 3, 2018, 6:13 PM
 */

#include "UGraph.h"
//UGraph::UGraph(std::string filename){
//    readInData(filename);
//}
//
//UGraph::UGraph(const UGraph& orig) {
//    this->nodes = orig.nodes;
//    this->edges = orig.edges;
//}
//
////UGraph::~UGraph() {
////}
//
//void UGraph::readInData(std::string filename) {
//    this->nodes = new vector<Node>();
//    this->edges = new vector<Edge>();
//    
//    std::ifstream infile(filename);
//    std::string line;
//    
//    vector<int> adjacency;
//    int n;
//    
//    
//    while (std::getline(infile,line)){
//        adjacency = strings_to_ints(split(line, ' '));
//        n = adjacency.at(0);
//        adjacency.erase(adjacency.cbegin());
//        
//        addAdjacency(n, adjacency);
//    }
//    
//}
//
//void UGraph::addAdjacency(int value, vector<int> neighbors) {
//    Node n = createOrFetchNode(value);
//    Node m;
//    Edge e;
//
//    for (int neighbor : neighbors){
//        m = createOrFetchNode(neighbor);
//        e = createOrFetchEdge(n, m);
//
//        n.edges.push_back(e);
//    }
//}
//
//Node UGraph::createOrFetchNode(int value) {
//    Node n = new Node(value);
//    for (Node i : nodes)
//        if (i == n)
//            return i;
//    nodes.push_back(n);
//    return n;
//}
//
//Edge UGraph::createOrFetchEdge(Node& one, Node& two) {
//    Edge e = new Edge(one, two);
//    for (Edge i : edges)
//        if (i == e)
//            return i;
//    edges.push_back(e);
//    return e;
//}
//
//std::ostream& operator<<(std::ostream& os, UGraph& g) {
//    for (Node n : g->nodes)
//        os << n << std::endl;
//
//    return os;
//}


/******************************************************************************/
/*  Helper Functions                                                          */
/******************************************************************************/
vector<string> split(const string& s, char delim){
    std::stringstream ss;
    ss.str(s);

    string item;
    vector<string> items;

    while (std::getline(ss, item, delim))
      items.push_back(item);  // populate items
    return items;
}


vector<int> strings_to_ints(vector<string> in){
    vector<int> ints;
    for (auto it = in.begin(); it != in.end(); ++it)
      ints.push_back(std::stoi(*it));
    return ints;
}

