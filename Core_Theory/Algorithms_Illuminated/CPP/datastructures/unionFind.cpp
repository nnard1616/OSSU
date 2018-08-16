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
    try{
        nodeList.at(x);
        return nodeList[x]->getLeader()->getValue();
    } catch(std::out_of_range){
        return -1;
    }
}

int unionFind::numberOfClusters() {
    return clusters.size();
}

pair<leader_t,c_size_t> unionFind::sizeOfCluster(int i) {
    pair<leader_t, c_size_t> result;
    int n = find(i);
    if (n != -1){
        result.first  = n;
        result.second = clusters[ n ].size(); 
    } else{
        result.first  = -1;
        result.second = -1;
    }
    
    return result;
}

bool unionFind::unionClusters(int i, int j) {
    
    pair<leader_t,c_size_t> iPair = sizeOfCluster(i);
    pair<leader_t,c_size_t> jPair = sizeOfCluster(j);
    
    //determine bigger cluster
    int iClusterSize = iPair.second;
    int jClusterSize = jPair.second;
    
    // only union if both exist
    if (iClusterSize == -1 || jClusterSize == -1)
        return false;
    
    
    int largerClusterID;
    int smallerClusterID;
    
    if (iClusterSize > jClusterSize){
        largerClusterID  = iPair.first;
        smallerClusterID = jPair.first;
    } else if(iClusterSize < jClusterSize){
        largerClusterID  = jPair.first;
        smallerClusterID = iPair.first;
    } else { //they're equal in size
        largerClusterID  = iPair.first;
        smallerClusterID = jPair.first;
    }
    
    // if they have same leader, they are in the same cluster already, so skip
    if (largerClusterID == smallerClusterID)
        return false;
    
    //set leader pointers of smaller cluster to that of the larger
    PrimNode* newLeader = clusters[largerClusterID][0]->getLeader();
    for (auto& i : clusters[smallerClusterID]){
        i->setLeader(newLeader);
    }
    
    //copy stuff from smaller cluster to larger cluster
    auto bitr = clusters [ smallerClusterID ].begin();
    auto eitr = clusters [ smallerClusterID ].end();
    
    auto here = clusters [ largerClusterID ].end();
    
    clusters [ largerClusterID ].insert(here, bitr, eitr);
    
    //delete smaller cluster
    clusters.erase(smallerClusterID);
    
    return true;
}