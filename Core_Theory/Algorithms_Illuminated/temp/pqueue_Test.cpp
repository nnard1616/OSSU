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
 * File:   pqueue_Test.cpp
 * Author: Nathan Nard
 *
 * Created on July 16, 2018, 1:26 PM
 */

#include <stdlib.h>
#include <iostream>
#include "pqueue.h"

/*
 * Simple C++ Test Suite
 */



void testPush() {
    vector<int> objects;
    int a[5] = {3,5,6,8,9};
    for ( int i : a){
        objects.push_back(i);
    }
    
    pqueue<int> _pqueue(objects);
    _pqueue.push(7);
    if (true) {
        std::cout << "%TEST_FAILED% time=0 testname=testPush (pqueue_Test) message=error message sample" << std::endl;
    }
}

void testPop() {
    vector<int> objects;
    int a[5] = {3,5,6,8,9};
    for ( int i : a){
        objects.push_back(i);
    }
    
    pqueue<int> _pqueue(objects);
    _pqueue.pop();
    
    int result = _pqueue.top();
    if (result != a[1]) {
        std::cout << "%TEST_FAILED% time=0 testname=testPop (pqueue_Test) message=error message sample" << std::endl;
    }
}

void testTop() {
    vector<int> objects;
    int a[5] = {3,5,6,8,9};
    for ( int i : a){
        objects.push_back(i);
    }
    
    pqueue<int> _pqueue(objects);
    int result = _pqueue.top();
    if (result != a[0]) {
        std::cout << "%TEST_FAILED% time=0 testname=testTop (pqueue_Test) message=error message sample" << std::endl;
    }
}

void testBinarySearch() {
    vector<int> objects;
    int a[5] = {3,5,6,8,9};
    for ( int i : a){
        objects.push_back(i);
    }
    
    pqueue<int> _pqueue(objects);
    vector<int>::iterator result = _pqueue.binarySearch(7);
    if (*result != 8) {
        std::cout << "%TEST_FAILED% time=0 testname=testBinarySearch (pqueue_Test) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% pqueue_Test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testPush (pqueue_Test)" << std::endl;
    testPush();
    std::cout << "%TEST_FINISHED% time=0 testPush (pqueue_Test)" << std::endl;

    std::cout << "%TEST_STARTED% testPop (pqueue_Test)" << std::endl;
    testPop();
    std::cout << "%TEST_FINISHED% time=0 testPop (pqueue_Test)" << std::endl;

    std::cout << "%TEST_STARTED% testTop (pqueue_Test)" << std::endl;
    testTop();
    std::cout << "%TEST_FINISHED% time=0 testTop (pqueue_Test)" << std::endl;

    std::cout << "%TEST_STARTED% testBinarySearch (pqueue_Test)" << std::endl;
    testBinarySearch();
    std::cout << "%TEST_FINISHED% time=0 testBinarySearch (pqueue_Test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

