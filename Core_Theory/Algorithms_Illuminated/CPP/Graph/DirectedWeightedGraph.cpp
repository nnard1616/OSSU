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
 * File:   DirectedWeightedGraph.cpp
 * Author: Nathan Nard
 * 
 * Created on July 13, 2018, 10:51 AM
 */

#include <stdint.h>

#include "DirectedWeightedGraph.h"
#include "../datastructures/heapp.hpp"

/******************************************************************************/
/*  Constructors/Destructor                                                   */
/******************************************************************************/

DirectedWeightedGraph::DirectedWeightedGraph(string filename) {
    this->filename = filename;
}

DirectedWeightedGraph::DirectedWeightedGraph(const DirectedWeightedGraph& orig){
}

DirectedWeightedGraph::~DirectedWeightedGraph() {
}


/******************************************************************************/
/*  Read & Solver Functions                                                   */
/******************************************************************************/

void DirectedWeightedGraph::readInDataPT2WK2() {
    cout << "reading data..." << endl;
    nodeList.clear();
    nodes = 0;
    edges = 0;
    
    ifstream infile(filename);
    string line;
    
    vector<string> adjacency;
    vector<int> readWeightAndValue;
    
    int nodeValue;
    int nodeWeight;
    
    WeightedNode* parentNode;
    WeightedNode* neighborNode;
    
    pair<WeightedNode*, int>* weightAndValue;
    
    
    while (getline(infile,line)){
        adjacency = split(line, '\t');
        nodeValue = stoi(adjacency.at(0));
        adjacency.erase(adjacency.begin());
        
        //check if node is already in our list of nodes, add it if it isn't
        if (nodeList.find(nodeValue) == nodeList.end()){
            nodeList[nodeValue] = new WeightedNode(nodeValue);
            nodes++;
        }
        
        parentNode = nodeList[nodeValue];
        
        for (auto& i : adjacency){
            
            try{
                readWeightAndValue = strings_to_ints(split(i, ','));
            }catch(invalid_argument){//each line may end with a space, skip it.
                continue;
            }
            
            nodeValue = readWeightAndValue.at(0);
            nodeWeight = readWeightAndValue.at(1);
        
            //check if neighbor is already in our list of nodes, add it if not.
            if (nodeList.find(nodeValue) == nodeList.end()){
                nodeList[nodeValue] = new WeightedNode(nodeValue);
                nodes++;
            }
            
            neighborNode = nodeList[nodeValue];
            
            weightAndValue = 
                         new pair<WeightedNode*, int>(neighborNode, nodeWeight);
            
            edges++;
            parentNode->addNeighbor(weightAndValue);
        }
        adjacency.clear();
    }
    
    infile.close();
    cout << "done reading." << endl;
}

void DirectedWeightedGraph::readInDataPT4WK1() {
    
    cout << "reading data..." << endl;
    nodeList.clear();
    nodes = 0;
    edges = 0;
    
    ifstream infile(filename);
    string line;
    
    int numberOfNodes, numberOfEdges;
    int tail, head, weight;
    
    WeightedNode* parentNode;
    WeightedNode* neighborNode;
    
    getline(infile, line);
    auto nodesAndEdges = strings_to_ints(split(line, ' '));
    
    numberOfNodes = nodesAndEdges[0];
    numberOfEdges = nodesAndEdges[1];
    
    pair<WeightedNode*, int>* weightAndValue;
    vector<int> tailHeadWeight;
    
    while (getline(infile,line)){
        tailHeadWeight = strings_to_ints(split(line, ' '));
        
        tail   = tailHeadWeight[0];
        head   = tailHeadWeight[1];
        weight = tailHeadWeight[2];
        
        if ( weight < 0 )
            negativeEdgeWeightsPresent = true;
        
        if (! negativeEdgeWeightsPresent)
            minPath = min(minPath, weight);
        
        //check if tail node is already in our list of nodes, add it if it isn't
        if (nodeList.find(tail) == nodeList.end()){
            nodeList[tail] = new WeightedNode(tail);
            nodes++;
        }
        
        parentNode = nodeList[tail];
        

        //check if neighbor is already in our list of nodes, add it if not.
        if (nodeList.find(head) == nodeList.end()){
            nodeList[head] = new WeightedNode(head);
            nodes++;
        }

        neighborNode = nodeList[head];

        weightAndValue = 
                     new pair<WeightedNode*, int>(neighborNode, weight);

        edges++;
        parentNode->addNeighbor(weightAndValue);
        
        
    }
    
    cout << numberOfNodes << " : " << nodes << endl;
    cout << numberOfEdges << " : " << edges << endl;
    infile.close();
    cout << "done reading." << endl;
}


void DirectedWeightedGraph::dijkstra(int n) {
    
    WeightedNode* start = nodeList[n];
    start->setDistance(0);
    start->setPreviousOptimalNeighbor(nullptr);
    
    //priority queue, Q
    heapp<WeightedNode*, DistanceComparator> Q;
    
    
    WeightedNode* current;
    int potentialDistance;
    
    //create set of all nodes, store in Q
    for (auto& i : nodeList){
        Q.insert(i.second);
    }
    
    while( ! Q.empty() ){
        current = Q.top();
        Q.pop();
        current->setVisited(true);
        
        //Relax neighbors if path distance is less than neighbor's current path
        for (auto& neighbor : *current->getNeighbors()){
            
            //only look at those who are in Q (ie, not visited yet)
            if ( ! neighbor->first->isVisited() ){
                
                
                
                //compute distance to this neighbor via current path
                if (current->getDistance() == INT32_MAX && neighbor->second > 0)
                    potentialDistance = INT32_MAX;
                else 
                    potentialDistance = current->getDistance() + neighbor->second;
                
                //if computed distance is less than neighbor's current path...
                if (potentialDistance < neighbor->first->getDistance()){
                    
                    //...update its path and previous node pointer.
                    neighbor->first->setDistance(potentialDistance);
                    neighbor->first->setPreviousOptimalNeighbor(current);
                    
                    //re-sort Q.
                    
                    Q.update(neighbor->first);
                }
            }
        }
    }
}

// returns true if successful, false if there's a negative cycle.
bool DirectedWeightedGraph::bellmanford(int n) {
    bool changesMade = true;
    int iterations = 0;
    
    WeightedNode* curr;
    nodeList[n]->setDistance(0);
    
    int before, after;
    
    // if no changes are made, then we're done, end it.
    // should only need n-1 iterations to get answer, if more iterations are 
    // used, then there's a negative cycle present.
    while (changesMade && iterations < nodes){
        changesMade = false;
        
        //go through each node, i,'s neighbors and update the neighbor distances
        //if i's distance + neighbor's edge weight is less than the neighbor's
        //current distance, update its distance.
        for (auto& i : nodeList){
            curr = i.second;
            
            if (curr->getDistance() == INT32_MAX)
                continue;   // Don't know how to get to this node yet, skip.

            for (auto& neighbor : *curr->getNeighbors()){
                
                before  = neighbor->first->getDistance();
                after   = min(neighbor->first->getDistance(), curr->getDistance() + neighbor->second);
                
                neighbor->first->setDistance(after);
                
                if (before != after){
                    changesMade = true;
                }
            }
        }
        iterations++;
    }
    
    if (iterations == nodes)
        return false; //negative cycle detected
    else
        return true;
}

//used strictly for finding shortest path between any two nodes u and v.
//if you want to find all paths, you'll need the full johnson algorithm.
bool DirectedWeightedGraph::johnsonSimplified() {
    
    //if there's no negative weights, then shortest path will be the 
    //smallest edge weight and that was already recorded when reading in the
    //data
    if ( ! negativeEdgeWeightsPresent)
        return true;
    
    // add 0 node with 0 weights to all nodes in nodeList
    WeightedNode* origin;
    origin = new WeightedNode(0);
    for (auto& i : nodeList){
        origin->addNeighbor(new pair<WeightedNode*, int>(i.second, 0));
    }
    
    nodeList[0] = origin;
    nodes++;
    
    //perform bellmanford with 0 node
    if ( ! bellmanford(0))
        return false; //negative cycle detected
    
    // if there are negative weights, then the minimum distance will be the 
    // the min of the distances churned out by bellmanford algorithm.
    for (auto& i : nodeList){
        minPath = min(minPath, i.second->getDistance());
    }
    
    return true;//success
}

//bool DirectedWeightedGraph::johnson() {
//    
//    // add 0 node with 0 weights to all nodes in nodeList
//    WeightedNode* origin;
//    origin = new WeightedNode(0);
//    for (auto& i : nodeList){
//        origin->addNeighbor(new pair<WeightedNode*, int>(i.second, 0));
//    }
//    
//    nodeList[0] = origin;
//    nodes++;
//    
//    //perform bellmanford with 0 node
//    if ( ! bellmanford(0))
//        return false; //negative cycle detected
//    
//    nodeList.erase(0);
//    nodes--;
//    
//    
//    
//    for (auto& i : nodeList){
//        minPath = min(minPath, i.second->getDistance());
//    }
//    
//    return true;//success
//}

void DirectedWeightedGraph::flloydwarshall(){
    int scores[nodes][nodes];
    
    for (int i = 0; i < nodes; i++){
        for(int j = 0; j < nodes; j++){
            if (i == j)
                scores[i][j] = 0;
            else
                scores[i][j] = INT32_MAX;
        }
    }
    
    for (auto& i : nodeList){
        for (auto& j : *i.second->getNeighbors()){
            scores[i.first][j->first->getValue()] = j->second;
        }
    }
    
    for (int k = 0; k < nodes; k++){
        for (int i = 0; i < nodes; i++){
            for(int j = 0; j < nodes; j++){
                if (scores[i][k] == INT32_MAX || scores[k][j] == INT32_MAX)
                    continue;
                if (scores[i][j] > scores[i][k] + scores[k][j])
                    scores[i][j] = scores[i][k] + scores[k][j];
            }
        }
    }
        
    
    for (int i = 0; i < nodes; i++){
        for(int j = 0; j < nodes; j++){
            cout << scores[i][j] << ' ';
        }
        cout << endl;
    }
    
    
}

/******************************************************************************/
/*  Getters/Setters                                                           */
/******************************************************************************/

int DirectedWeightedGraph::getEdges() const {
    return edges;
}

int DirectedWeightedGraph::getNodes() const {
    return nodes;
}

bool DirectedWeightedGraph::areAllVisited() {
    for (auto i : nodeList)
        if ( ! i.second->isVisited())
            return false;
    return true;
}

bool DirectedWeightedGraph::areAllNotVisited() {
    for (auto i : nodeList)
        if (i.second->isVisited())
            return false;
    return true;
}

void DirectedWeightedGraph::setAllNotVisited() {
    for (auto i : nodeList){
        if (i.second->isVisited())
            i.second->setVisited(false);
    }
}

void DirectedWeightedGraph::setAllVisited() {
    for (auto i : nodeList){
        if ( ! i.second->isVisited())
            i.second->setVisited(true);
    }
}

//for debugging purposes
map<int, WeightedNode*> DirectedWeightedGraph::getNodeList() {
    return nodeList;
}

void DirectedWeightedGraph::printPathScores() {
    for (auto& i : nodeList){
        cout << i.second->getValue() << ' ' << i.second->getDistance() << endl;
    }
}

//assumes dijkstra has already been run.
string DirectedWeightedGraph::getOptimalPath(int n) {
    string result;
    WeightedNode* i = nodeList[n];
    
    while (i != nullptr){
        result =  to_string(i->getValue()) + " " + result;
        i = i->getPreviousOptimalNeighbor();
    }
    
    return result;
}

//assumes dijkstra has already been run.
string DirectedWeightedGraph::getAnswerPT2WK2() {
    string result;
    int nodes [10] = {7,37,59,82,99,115,133,165,188,197};
    
    for (int i : nodes){
        result += to_string(nodeList[i]->getDistance()) + ',';
    }
    
    result.pop_back();
    
    return result;
}

int DirectedWeightedGraph::getMinPath() {
    return minPath;
}

void DirectedWeightedGraph::computeMinPath(int start) {
    for (auto& i : nodeList){
        if (i.second->getDistance() == INT32_MAX)
            minPath = min(minPath, INT32_MAX);
        else{
            minPath = min(minPath, i.second->getDistance() - nodeList[start]->getBF0Distance() + i.second->getBF0Distance());
        }
    }
}


//for debugging purposes
int DirectedWeightedGraph::numberOfEdges() {
    int result = 0;
    for (auto& i : nodeList){
        result += i.second->getNeighbors()->size();
    }
    return result;
}

void DirectedWeightedGraph::printDistances(int start) {
    for (auto& i : nodeList){
        if (i.second->getDistance() < INT32_MAX)
            cout << start << ": " << i.first << " : " << i.second->getDistance() << " - " << nodeList[start]->getBF0Distance() << " + " << i.second->getBF0Distance() << " = " << i.second->getDistance() - nodeList[start]->getBF0Distance() + i.second->getBF0Distance() << endl;
    }
}

void DirectedWeightedGraph::resetDistances() {
    for (auto& i : nodeList){
        i.second->setDistance(INT32_MAX);
    }
}

void DirectedWeightedGraph::resetAllOptimalPreviousNeighbors() {
    for (auto& i : nodeList){
        i.second->setPreviousOptimalNeighbor(nullptr);
    }
}

void DirectedWeightedGraph::printMinPath(int end) {
    for (auto& i : nodeList[end]->getPath()){
        cout << i->getValue() << " ";
    }
    cout << nodeList[end]->getValue();
}

void DirectedWeightedGraph::printMinPath2(int start) {
    WeightedNode* n = nullptr;
    
    for (auto& i : nodeList){
        if (i.second->getDistance() - nodeList[start]->getBF0Distance() + i.second->getBF0Distance() == minPath){
            n = i.second;
            cout << start << ": " << minPath << endl;
            cout << "----------------------------------------------------------------------------------" << endl;
            cout << n->getValue() <<  "," << n->getDistance() - nodeList[start]->getBF0Distance() + n->getBF0Distance() << ' ';
            while (n->getPreviousOptimalNeighbor() != nodeList[start]){
                n = n->getPreviousOptimalNeighbor();
                cout << n->getValue() <<  "," <<    n->getDistance() - nodeList[start]->getBF0Distance() + n->getBF0Distance() << ' ';
            }
            n = n->getPreviousOptimalNeighbor();
            cout << n->getValue() <<  "," << n->getDistance() - nodeList[start]->getBF0Distance() + n->getBF0Distance()<< endl;
        }
    }
}




/******************************************************************************/
/*  Operators                                                                 */
/******************************************************************************/

ostream& operator<< (ostream& os, const DirectedWeightedGraph& g ){
    
    for (auto pair : g.nodeList){
        os << *pair.second << endl;
    }
    return os;
}