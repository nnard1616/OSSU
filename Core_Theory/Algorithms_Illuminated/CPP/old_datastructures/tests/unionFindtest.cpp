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
 * File:   unionFindtest.cpp
 * Author: Nathan Nard
 *
 * Created on August 7, 2018, 3:17 PM
 */

#include <stdlib.h>
#include <iostream>
#include "unionFind.hpp"
#include "../../Graph/UndirectedWeightedGraph.h"

UndirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week2/input_completeRandom_9_32.txt");


/*
 * Simple C++ Test Suite
 */

void testUnionFind() {
    map<int, PrimNode*> nodeList = g.getNodeList();
    unionFind _unionFind(nodeList);
    if (_unionFind.numberOfClusters() != g.getNodeList().size()) {
        std::cout << "%TEST_FAILED% time=0 testname=testUnionFind (unionFindtest) message=error message sample" << std::endl;
    }
}

void testFind() {
    int x = 1;
    map<int, PrimNode*> nodeList = g.getNodeList();
    unionFind _unionFind(nodeList);
    int result = _unionFind.find(x);
    if (result != x) {
        std::cout << "%TEST_FAILED% time=0 testname=testFind (unionFindtest) message=error message sample" << std::endl;
    }
}

void testNumberOfClusters() {
    map<int, PrimNode*> nodeList = g.getNodeList();
    unionFind _unionFind(nodeList);
    int result = _unionFind.numberOfClusters();
    if (result != g.getNodeList().size()) {
        std::cout << "%TEST_FAILED% time=0 testname=testNumberOfClusters (unionFindtest) message=error message sample" << std::endl;
    }
}

void testSizeOfCluster() {
    int i = 1;
    map<int, PrimNode*> nodeList = g.getNodeList();
    unionFind _unionFind(nodeList);
    int result = _unionFind.sizeOfCluster(i);
    if (result != 1) {
        std::cout << "%TEST_FAILED% time=0 testname=testSizeOfCluster (unionFindtest) message=error message sample" << std::endl;
    }
}

void testUnionClusters() {
    int i = 1;
    int j = 2;
    map<int, PrimNode*> nodeList = g.getNodeList();
    unionFind _unionFind(nodeList);
    _unionFind.unionClusters(i, j);
    
    bool checkLeaders = (nodeList[1]->getLeader()->getValue() == 1) && 
                        (nodeList[2]->getLeader()->getValue() == 1);
    bool checkClusterSizes = (_unionFind.sizeOfCluster(i) == 2) && 
                             (_unionFind.sizeOfCluster(j) == 2);
    bool checkNumberOfClusters = _unionFind.numberOfClusters() == nodeList.size() - 1;
    
    if (! (checkLeaders && checkClusterSizes && checkNumberOfClusters) ) {
        std::cout << "%TEST_FAILED% time=0 testname=testUnionClusters (unionFindtest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% unionFindtest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testUnionFind (unionFindtest)" << std::endl;
    testUnionFind();
    std::cout << "%TEST_FINISHED% time=0 testUnionFind (unionFindtest)" << std::endl;

    std::cout << "%TEST_STARTED% testFind (unionFindtest)" << std::endl;
    testFind();
    std::cout << "%TEST_FINISHED% time=0 testFind (unionFindtest)" << std::endl;

    std::cout << "%TEST_STARTED% testNumberOfClusters (unionFindtest)" << std::endl;
    testNumberOfClusters();
    std::cout << "%TEST_FINISHED% time=0 testNumberOfClusters (unionFindtest)" << std::endl;

    std::cout << "%TEST_STARTED% testSizeOfCluster (unionFindtest)" << std::endl;
    testSizeOfCluster();
    std::cout << "%TEST_FINISHED% time=0 testSizeOfCluster (unionFindtest)" << std::endl;

    std::cout << "%TEST_STARTED% testUnionClusters (unionFindtest)" << std::endl;
    testUnionClusters();
    std::cout << "%TEST_FINISHED% time=0 testUnionClusters (unionFindtest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

