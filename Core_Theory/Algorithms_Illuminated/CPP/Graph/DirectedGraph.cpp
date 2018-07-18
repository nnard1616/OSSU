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
 * File:   DirectedGraph.cpp
 * Author: Nathan Nard
 * 
 * Created on July 8, 2018, 1:09 PM
 */


#include "DirectedGraph.h"
#include "StaticFunctions.h"
#include <stack>

/******************************************************************************/
/*  Constructors/Destructor                                                   */
/******************************************************************************/

DirectedGraph::DirectedGraph(string filename) {
    readInData(filename);
}

DirectedGraph::DirectedGraph(const DirectedGraph& orig) {
    edges = orig.edges;
    nodes = orig.nodes;
    nodeList = orig.nodeList;
}

DirectedGraph::~DirectedGraph() {
}


/******************************************************************************/
/*  Public Graph Methods                                                      */
/******************************************************************************/

/**
 * Assumes file is a list of edges: Value1 Value2
 * @param filename
 */
void DirectedGraph::readInData(string filename) {
    cout << "reading data..." << endl;
    nodeList.clear();
    nToFinishTime.clear();
    nodes = 0;
    edges = 0;
    
    ifstream infile(filename);
    string line;
    
    vector<int> pair;
    
    while (getline(infile,line)){
        pair = strings_to_ints(split(line, ' '));
        
        int mInt = pair.at(0);
        int nInt = pair.at(1);
        
        
        if (nodeList.find(mInt) == nodeList.end()){
            nodeList[mInt] = new Node(mInt);
            nodes++;
        }
        
        if (nodeList.find(nInt) == nodeList.end()){
            nodeList[nInt] = new Node(nInt);
            nodes++;
        }
        
        nodeList[mInt]->addNeighbor(nodeList[nInt]);
        edges++;
        
        pair.clear();
    }
    
    
    cout << "Data read. " << endl << "Nodes: "  << nodes 
                                  << " Edges: " << edges << endl;
    
}

void DirectedGraph::findSCCs() {
    cout << "Performing DFS on original..." << endl;
    
    //side affect: 'nToFinishTime' contains mapping from original nodes to 
    //DFS finish times.
    DFSOnOriginal();
    
    cout << "Done. Performing reverse and map..." << endl;
    nodeList = reverseArcsAndTransform(nodeList);
    
    cout << "Done. Performing DFS on reversed transform..." << endl;
    priority_queue<int> result = DFSOnReversedTransform();
     
    cout << "Done.  Here are the top 5 results: " << endl;
    for(int i = 0; i < 5; i ++){
        if (result.size() > 0){
            cout << result.top() << ' ';
            result.pop();
        }else{
            cout << 0 << ' ';
        }
    }
    cout << endl;
}


/******************************************************************************/
/*  Private Graph Methods                                                     */
/******************************************************************************/

//Reverses the arcs in graph, and also uses 'nToFinishTime' to map to the
//respective finish time from DFS on original graph.
map<int, Node*> DirectedGraph::reverseArcsAndTransform(
                                                    const map<int, Node*>& al) {
    
    //reversed, transformed adjacency list.
    map<int, Node*> rtal;
    
    for (auto pair : al){
        
        //transform first node
        int mInt = nToFinishTime[pair.first];
        
        for ( auto i : *pair.second->getNeighbors()){
            
            //transform second node
            int nInt = nToFinishTime[i->getValue()];
            
            if (rtal.find(mInt) == rtal.end())
                rtal[mInt] = new Node(mInt);

            if (rtal.find(nInt) == rtal.end())
                rtal[nInt] = new Node(nInt);
            
            //reverse arc
            rtal[nInt]->addNeighbor(rtal[mInt]);
        }
    }
    
    return rtal;
}

//with recursion
//void DirectedGraph::DFS(Node* n, int& counter) {
//    n->setVisited(true);
//    for (auto& neighbor : *n->getNeighbors()){
//        if ( ! neighbor->isVisited()){
//            DFS(neighbor, counter);
//        }
//    }
//    
//    if (nToFinishTime.size() < nodes)
//        if (nToFinishTime.find(n->getValue()) == nToFinishTime.end())
//            nToFinishTime[n->getValue()] = counter;
//    counter++;
//}

//without recursion
void DirectedGraph::DFS(Node* n, int& counter) {
    stack<Node*> path;
    n->setVisited(true);
    path.push(n);
    
    while (! path.empty()){
        for (auto& i: *path.top()->getNeighbors()){
            if ( ! i->isVisited()){
                i->setVisited(true);
                path.push(i);
                break;//move to neighbor
            }
        }
        
        //if current node has no unvisited neighbors, start backtracking.
        if (path.top()->allNeighborsVisited()){
            
            //this portion is only needed for DFS on original graph.  It will 
            //be skipped over in DFS on reversed transformed graph.
            if (nToFinishTime.size() < nodes)
                if (nToFinishTime.find(path.top()->getValue()) == 
                    nToFinishTime.end())
                    nToFinishTime[path.top()->getValue()] = counter;
            
            counter++;
            path.pop();
        }
    }
}

void DirectedGraph::DFSOnOriginal() {
    int counter = 1;
    int node = nodes;
    
    while (counter <= nodes){
        
        //start at highest node, jump to next highest unvisited node after
        //a round of DFS.
        while (nodeList[node]->isVisited())
            node--;
        
        DFS(nodeList[node], counter);
    }
}

priority_queue<int> DirectedGraph::DFSOnReversedTransform() {
    priority_queue<int> SCCs;
    int prevCounter;
    int counter = 1;
    int node = nodes;
    
    while (counter <= nodes){
        
        prevCounter = counter;
        
        //start at highest node, jump to next highest unvisited node after
        //a round of DFS.
        while (nodeList[node]->isVisited())
            node--;
        
        DFS(nodeList[node], counter);
        
        SCCs.push(counter - prevCounter);
        
    }
    return SCCs;
}


/******************************************************************************/
/*  Getters/Setters                                                           */
/******************************************************************************/

int DirectedGraph::getEdges() const {
    return edges;
}

int DirectedGraph::getNodes() const {
    return nodes;
}

bool DirectedGraph::areAllVisited() {
    for (auto i : nodeList)
        if ( ! i.second->isVisited())
            return false;
    return true;
}

bool DirectedGraph::areAllNotVisited() {
    for (auto i : nodeList)
        if (i.second->isVisited())
            return false;
    return true;
}

void DirectedGraph::setAllNotVisited() {
    for (auto i : nodeList){
        if (i.second->isVisited())
            i.second->setVisited(false);
    }
}

void DirectedGraph::setAllVisited() {
    for (auto i : nodeList){
        if ( ! i.second->isVisited())
            i.second->setVisited(true);
    }
}


/******************************************************************************/
/*  Operators                                                                 */
/******************************************************************************/

ostream& operator<< (ostream& os, const DirectedGraph& g ){
    for (auto pair : g.nodeList){
        os << *pair.second << endl;
    }
    return os;
}