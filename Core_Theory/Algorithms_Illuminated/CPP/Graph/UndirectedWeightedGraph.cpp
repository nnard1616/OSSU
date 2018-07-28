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
 * File:   UndirectedWeightedGraph.cpp
 * Author: Nathan Nard
 * 
 * Created on July 25, 2018, 5:58 PM
 */

#include "UndirectedWeightedGraph.h"

UndirectedWeightedGraph::UndirectedWeightedGraph(string filename) {
    nodes = 0;
    edges = 0;
    
    readInData(filename);
}


void UndirectedWeightedGraph::readInData(string filename) {
    
    ifstream infile(filename);
    
    string line;
    
    getline(infile, line);
    
    vector<int> stats = strings_to_ints(split(line, ' '));
    int numberOfNodes = stats[0];
    int numberOfEdges = stats[1];
    int node1;
    int node2;
    int weight;
    PrimEdge* pEdge;
    int minWeight = INT16_MAX;
    
    while(getline(infile, line)){
        stats = strings_to_ints(split(line, ' '));
        node1 = stats[0];
        node2 = stats[1];
        weight = stats[2];
        minWeight = min(minWeight, weight);
        
        try{
            nodeList.at(node1);
        }catch (out_of_range){
            nodeList[node1] = new PrimNode(node1);
            unvisitdedNodeList[node1] = nodeList[node1];
            nodes++;
        }
        
        try{
            nodeList.at(node2);
        }catch (out_of_range){
            nodeList[node2] = new PrimNode(node2);
            unvisitdedNodeList[node2] = nodeList[node2];
            nodes++;
        }
        
        pEdge = new PrimEdge(nodeList[node1], nodeList[node2], weight);
        edgeList.push(pEdge);
        edges++;
        
        nodeList[node1]->addNeighbor(nodeList[node2], pEdge);
        nodeList[node2]->addNeighbor(nodeList[node1], pEdge);
        
        
        
    }
    
//    cout << numberOfEdges << ' ' << edges <<  ' ' << edgeList.size() << endl;
//    cout << numberOfNodes << ' ' << nodes << endl;
//    cout << (*edgeList.begin())->getWeight() <<  ' ' << minWeight << endl;
    infile.close();
}

bool UndirectedWeightedGraph::areAllVisited() {
    for (auto i : nodeList)
        if ( ! i.second->isVisited())
            return false;
    return true;
}

int UndirectedWeightedGraph::prim() {
    PrimEdge* nextPath = nullptr;
    PrimNode* examinee = unvisitdedNodeList.begin()->second;
    auto edgeItr = edgeList.begin(); //TODO need better way to select an edge based on weight and whether it touches a visited and unvisited node.
    
    unvisitdedNodeList.erase(unvisitdedNodeList.begin());
    visitedNodeList[examinee->getValue()] = examinee;
    examinee->setVisited(true);
    edgeList.update();
    
    
    while (! unvisitdedNodeList.empty()){
        nextPath = edgeList.top();
        minCostEdgeList.push(nextPath);
        
        if (! nextPath->getFirst()->isVisited())
            examinee = nextPath->getFirst();
        else
            examinee = nextPath->getSecond();
        
        examinee->setVisited(true);
        unvisitdedNodeList.erase(examinee->getValue());
        visitedNodeList[examinee->getValue()] = examinee;
        edgeList.update();
        minCostEdgeList.update();
    }
    
    return sumMin();
}

void UndirectedWeightedGraph::printMinTree() {
    for (auto& i : minCostEdgeList){
        cout << i->getFirst()->getValue() << ' ' << i->getSecond()->getValue() << ' ' << i->getWeight() << endl;
    }
}


int UndirectedWeightedGraph::sumMin() {
    int result = 0;
    for (auto& i : minCostEdgeList){
        result += i->getWeight();
    }
    
    return result;
}

ostream& operator<< (ostream& os, const UndirectedWeightedGraph& g){
    for (auto& i : g.nodeList){
        os << *i.second << endl;
    }
    return os;
}
