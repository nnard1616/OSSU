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
 * File:   main.cpp
 * Author: Nathan Nard
 *
 * Created on July 22, 2018, 12:57 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../datastructures/pqueue.h"
#include "StringFunctions.h"
#include "JobsComparator.h"

using namespace std;


void twoSum(){
    vector<long long> numbers;
    set<long long> results;
    
    ifstream infile("/home/nathan/Programming/OSSU/Core_Theory/"
    "Algorithms-Roughgarden/Part2/Week4/algo1-programming_prob-2sum.txt");
    
    string line;
    
    
    while (getline(infile, line)){
        numbers.push_back(stoll(line));
    }
    
    std::sort(numbers.begin(), numbers.end());
    
    auto i = numbers.begin();
    auto j = --numbers.end();
    
    while (*i <= *j){
        if (*i + *j > 10000)
            j--;
        else if (*i + *j < -10000)
            i++;
        else{
            while(*i <= *j){
                
                if (*i + *j > 10000)
                    break;
                results.insert(*i + *j);
                i++;
            }
        }
    }
    
    cout << results.size() << endl;
    
}



void solvePt3Wk1PA1(){
    pqueue<pair<int, int>, BadJobsComparator<int>> Q;
    vector<int> readin;
    vector<string> shit;
    pair<int, int> job;
    
    ifstream infile("/home/nathan/Programming/OSSU/Core_Theory/"
    "Algorithms-Roughgarden/Part3/Week1/jobs.txt");
    
    string line;
    
    int numberOfJobs;
    
    getline(infile, line);
    numberOfJobs = stoi(line);
    
    while (getline(infile, line)){
        shit = CommonFunctions::split(line, ' ');
        readin = CommonFunctions::strings_to_ints(shit);
        job = *(new pair<int, int>(readin[0], readin[1]));
        Q.push(job);
    }
    
    long long sum = 0;
    long long timeSum = 0;
    
    for (auto& i : Q.getObjects()){
        timeSum += i.second;
        sum += i.first*timeSum;
    }
    
    
    cout << sum << endl;
}

void solvePt3Wk1PA2(){
    pqueue<pair<int, int>, GoodJobsComparator<int>> Q;
    vector<int> readin;
    vector<string> shit;
    pair<int, int> job;
    
    ifstream infile("/home/nathan/Programming/OSSU/Core_Theory/"
    "Algorithms-Roughgarden/Part3/Week1/jobs.txt");
    
    string line;
    
    int numberOfJobs;
    
    getline(infile, line);
    numberOfJobs = stoi(line);
    
    while (getline(infile, line)){
        shit = CommonFunctions::split(line, ' ');
        readin = CommonFunctions::strings_to_ints(shit);
        job = *(new pair<int, int>(readin[0], readin[1]));
        Q.push(job);
    }
    
    long long sum = 0;
    long long timeSum = 0;
    
    for (auto& i : Q.getObjects()){
        timeSum += i.second;
        sum += i.first*timeSum;
    }
    
    
    cout << sum << endl;
}

int main(int argc, char** argv) {
    solvePt3Wk1PA1();
    solvePt3Wk1PA2();
    return 0;
}