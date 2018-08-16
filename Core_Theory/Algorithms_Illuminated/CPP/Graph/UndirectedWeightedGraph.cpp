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

#include "../datastructures/unionFind.hpp"
#include "StaticFunctions.h"
#include <algorithm>
#include <bitset>
UndirectedWeightedGraph::UndirectedWeightedGraph(string filename) {
    nodes = 0;
    edges = 0;
    
    readInData(filename);
}


//void UndirectedWeightedGraph::readInData(string filename) {
//    
//    ifstream infile(filename);
//    
//    string line;
//    
//    getline(infile, line);
//    
//    vector<int> stats = strings_to_ints(split(line, ' '));
//    int numberOfNodes = stats[0];
//    int numberOfEdges = stats[1];
//    int node1;
//    int node2;
//    int weight;
//    PrimEdge* pEdge;
//    int minWeight = INT16_MAX;
//    
//    while(getline(infile, line)){
//        stats = strings_to_ints(split(line, ' '));
//        node1 = stats[0];
//        node2 = stats[1];
//        weight = stats[2];
//        minWeight = min(minWeight, weight);
//        
//        try{
//            nodeList.at(node1);
//        }catch (out_of_range){
//            nodeList[node1] = new PrimNode(node1);
//            unvisitdedNodeList[node1] = nodeList[node1];
//            nodes++;
//        }
//        
//        try{
//            nodeList.at(node2);
//        }catch (out_of_range){
//            nodeList[node2] = new PrimNode(node2);
//            unvisitdedNodeList[node2] = nodeList[node2];
//            nodes++;
//        }
//        
//        pEdge = new PrimEdge(nodeList[node1], nodeList[node2], weight);
//        edgeList.push(pEdge);
//        edges++;
//        
//        nodeList[node1]->addNeighbor(nodeList[node2], pEdge);
//        nodeList[node2]->addNeighbor(nodeList[node1], pEdge);
//        
//        
//        
//    }
//    
////    cout << numberOfEdges << ' ' << edges <<  ' ' << edgeList.size() << endl;
////    cout << numberOfNodes << ' ' << nodes << endl;
////    cout << (*edgeList.begin())->getWeight() <<  ' ' << minWeight << endl;
//    infile.close();
//}


void UndirectedWeightedGraph::readInData(string filename) {
    
    ifstream infile(filename);
    
    string line;
    
    getline(infile, line);
    
    vector<int> stats = strings_to_ints(split(line, ' '));
    int numberOfNodes = stats[0];
    int numberOfBits = stats[1];
    int nodeValue;
    
    while(getline(infile, line)){
        //remove the ' ' characters from the line
        auto new_end_iterator = remove_if(line.begin(), line.end(),
                                          [] (char x) {
                                              return (x == ' ');
                                          }
                                                                    );
        //trim end of line string
        line.erase(new_end_iterator, line.end());
        
        //convert from string to binary representation
        bitset<24> binaryValue(line);
        
        //convert from binary representation to int
        nodeValue = (int)binaryValue.to_ulong();
        
        try{
            nodeList.at(nodeValue);
        }catch (out_of_range){
            nodeList[nodeValue] = new PrimNode(nodeValue);
            unvisitdedNodeList[nodeValue] = nodeList[nodeValue];
            nodes++;
        }
    }
    
//    cout << numberOfEdges << ' ' << edges <<  ' ' << edgeList.size() << endl;
    cout << numberOfNodes << ' ' << nodes << endl;
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
    PrimNode* currentNode = unvisitdedNodeList.begin()->second;
    
    while ( ! unvisitdedNodeList.empty()) {
        
        //erase current node from unvisitedNodeList map structure.
        unvisitdedNodeList.erase(currentNode->getValue());
        
        //add current node to visitedNodeList map structure.
        visitedNodeList[currentNode->getValue()] = currentNode;
        
        //mark current node as visited
        currentNode->setVisited(true);
        
        //have pqueue structures re-order edges.
        edgeList.update();
        minCostEdgeList.update();
        
        //get next path to add to our minCostEdgeList, a pqueue
        nextPath = edgeList.top();
        
        //prevent duplicate of least cost edge
        if (nextPath->oneVisited())
            
            //add nextPath to MST
            minCostEdgeList.push(nextPath);
        
        //assign currentNode to the other unvisited node of this edge
        if ( ! nextPath->getFirst()->isVisited())
            currentNode = nextPath->getFirst();
        else
            currentNode = nextPath->getSecond();
    }
    return sumMin();
}

int UndirectedWeightedGraph::kspacing(int k) {
    unionFind uf(nodeList);
    pqueue<PrimEdge*, KruskalEdgeComparator<PrimEdge>> kEdgeList;
    
    //copy over edges to new pqueue with appropriate comparator for the algo.
    kEdgeList.insert(kEdgeList.begin(), edgeList.begin(), edgeList.end());
    
    int cluster1;
    int cluster2;
    
    
    while (uf.numberOfClusters() != k){
        cluster1 = uf.find(kEdgeList.top()->getFirst()
                                          ->getLeader()
                                          ->getValue());
        
        cluster2 = uf.find(kEdgeList.top()->getSecond()
                                          ->getLeader()
                                          ->getValue());
        
        
        // try to union the two clusters, if it works then we need to re order 
        // the pqueue.
        if (uf.unionClusters(cluster1, cluster2)){
        
            //reorders pqueue so that min edge between two clusters is on top.
            kEdgeList.update();
        }
    }
    
    return kEdgeList.top()->getWeight();
}

int UndirectedWeightedGraph::findKWithSpacingOfThree() {
    unionFind uf(nodeList);
    
    int n;
    int neighbor;
    
    cout << "Done with 0 buddies" << endl;
    
    //iterate through each cluster looking for distance of 1 buddies
    for (auto i = nodeList.begin(); i != nodeList.end(); i++){
        n = i->first;
        bitset<24> bn(n);
        for (int d = 0; d < 24 ; d++){
            
            bn.flip(d);
            
            neighbor = (int)bn.to_ulong();
                            
            uf.unionClusters(n, neighbor);
                
            bn.flip(d);
        }
        
    }
    
    cout << "Done with 1 buddies" << endl;
    
    //iterate through each cluster looking for distance of 2 buddies
    for (auto i = nodeList.begin(); i != nodeList.end(); i++){
        n = i->first;
        bitset<24> bn(n);
        for (int d = 0; d < 24 ; d++){
            bn.flip(d);
            for (int dd = d+1; dd < 24; dd++){
                bn.flip(dd);

                neighbor = (int)bn.to_ulong();

                uf.unionClusters(n, neighbor);

                bn.flip(dd);
            }
            bn.flip(d);
        }
        
    }
    
    cout << "Done with 2 buddies" << endl;
    
    return uf.numberOfClusters();
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

map<int, PrimNode*> UndirectedWeightedGraph::getNodeList() {
    return nodeList;
}

ostream& operator<< (ostream& os, const UndirectedWeightedGraph& g){
    for (auto& i : g.nodeList){
        os << *i.second << endl << endl;
    }
    return os;
}
