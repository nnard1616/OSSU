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

#include <map>
using std::map;

#include <vector>
using std::vector;

class unionFind {
public:
    unionFind(map<int, PrimNode*> nodeList);
    int find(int x);
    void unionClusters(int i, int j);
    
    int numberOfClusters();
    int sizeOfCluster(int i);
private:
    map<int, vector< PrimNode*> > clusters;
    
    map<int, PrimNode*> nodeList;
    

};

#endif /* UNIONFIND_HPP */

