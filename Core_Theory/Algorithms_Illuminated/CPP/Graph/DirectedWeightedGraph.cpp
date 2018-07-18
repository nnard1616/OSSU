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

#include "DirectedWeightedGraph.h"


/******************************************************************************/
/*  Constructors/Destructor                                                   */
/******************************************************************************/

DirectedWeightedGraph::DirectedWeightedGraph(string filename) {
    readInData(filename);
}

DirectedWeightedGraph::DirectedWeightedGraph(const DirectedWeightedGraph& orig){
}

DirectedWeightedGraph::~DirectedWeightedGraph() {
}


/******************************************************************************/
/*  Read & Solver Functions                                                   */
/******************************************************************************/

void DirectedWeightedGraph::readInData(string filename) {
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

void DirectedWeightedGraph::dijkstra(int n) {
    WeightedNode* start = nodeList[n];
    start->setDistance(0);
    start->setPreviousOptimalNeighbor(nullptr);
    
    //priority queue, Q
    pqueue<WeightedNode*, DistanceComparator> Q;
    
    WeightedNode* current;
    int potentialDistance;
    WeightedNode *j, *k;
    
    //create set of all nodes, store in Q
    for (auto& i : nodeList){
        Q.push(i.second);
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
                potentialDistance = current->getDistance() + neighbor->second;
                
                //if computed distance is less than neighbor's current path...
                if (potentialDistance < neighbor->first->getDistance()){
                    
                    //...update its path and previous node pointer.
                    neighbor->first->setDistance(potentialDistance);
                    neighbor->first->setPreviousOptimalNeighbor(current);
                    
                    //re-sort Q.
                    Q.update();
                }
            }
        }
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
string DirectedWeightedGraph::getAnswer() {
    string result;
    int nodes [10] = {7,37,59,82,99,115,133,165,188,197};
    
    for (int i : nodes){
        result += to_string(nodeList[i]->getDistance()) + ',';
    }
    
    result.pop_back();
    
    return result;
}

//for debugging purposes
int DirectedWeightedGraph::numberOfEdges() {
    int result = 0;
    for (auto& i : nodeList){
        result += i.second->getNeighbors()->size();
    }
    return result;
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