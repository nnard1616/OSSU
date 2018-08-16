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
 * File:   unionFind.cpp
 * Author: Nathan Nard
 * 
 * Created on August 7, 2018, 12:50 PM
 */

#include "unionFind.hpp"

unionFind::unionFind(map<int, PrimNode*> nodeList) {
    // set nodeList field
    this->nodeList = nodeList;
    
    // populate clusters
    vector<PrimNode*> cluster;
    int       id;
    PrimNode* p;
    
    for (auto& i : nodeList){
        id = i.first;
        p  = i.second;
        
        cluster = *(new vector<PrimNode*>);
        cluster.push_back(p);
        
        clusters[id] = cluster;
    }
}

int unionFind::find(int x) {
    return nodeList[x]->getLeader()->getValue();
}

int unionFind::numberOfClusters() {
    return clusters.size();
}

int unionFind::sizeOfCluster(int i) {
    return clusters[ find(i) ].size();
}

void unionFind::unionClusters(int i, int j) {
    //determine bigger cluster
    int iClusterSize = sizeOfCluster(i);
    int jClusterSize = sizeOfCluster(j);
    
    int larger;
    int smaller;
    
    if (iClusterSize > jClusterSize){
        larger  = i;
        smaller = j;
    } else if(iClusterSize < jClusterSize){
        larger  = j;
        smaller = i;
    } else { //they're equal
        larger  = i;
        smaller = j;
    }
    
    //set leader pointers of smaller cluster to that of the larger
    PrimNode* newLeader = clusters[larger][0]->getLeader();
    
    for (auto& i : clusters[smaller]){
        i->setLeader(newLeader);
    }
    
    //copy stuff from smaller cluster to larger cluster
    auto bitr = clusters [ smaller ].begin();
    auto eitr = clusters [ smaller ].end();
    
    auto here = clusters [ larger ].end();
    
    clusters [ larger ].insert(here, bitr, eitr);
    
    //delete smaller cluster
    clusters.erase(smaller);
}


