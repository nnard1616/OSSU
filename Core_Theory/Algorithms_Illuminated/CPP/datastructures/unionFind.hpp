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
 * File:   unionFind.hpp
 * Author: Nathan Nard
 *
 * Created on August 7, 2018, 12:50 PM
 */
#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include "../Graph/PrimNode.h"
#include <iterator>

#include <map>
using std::map;

#include <vector>
using std::vector;

using std::pair;

typedef int c_size_t; //size of cluster 
typedef int leader_t; //value of leader node

class unionFind {
public:
    unionFind(map<int, PrimNode*> nodeList);
    
    /**
     * Finds the head value of x's cluster.
     * @param x
     * @return Head of x's cluster, or -1 if x does not exist.
     */
    int find(int x);
    
    /**
     * Unions the two clusters that i and j belong in, if they exist and are 
     * separate clusters.
     * @param i
     * @param j
     * @return true if successful, false otherwise.
     */
    bool unionClusters(int i, int j);
    
    int numberOfClusters();
    
    /**
     * Returns a pair containing the ID of the cluster that i is in and the size
     * of that cluster.  This function calls this.find(int) and 
     * this.unionClusters(int,int) in turn calls this.sizeOfCluster(int), so 
     * it made sense to me to have sizeOfCluste also return the ID of the 
     * cluster so that unionClusters doesn't have to call find unnecessarily.
     * @param i
     * @return 
     */
    pair<leader_t,c_size_t> sizeOfCluster(int i);
    
private:
    map<int, vector< PrimNode*> > clusters;
    
    map<int, PrimNode*> nodeList;
};

#endif /* UNIONFIND_HPP */

