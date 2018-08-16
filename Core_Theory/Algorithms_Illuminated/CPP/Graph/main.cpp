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
 * Created on July 3, 2018, 6:12 PM
 */

#include <cstdlib>

#include "Node.h"
#include "Edge.h"
#include "DirectedWeightedGraph.h"
#include "UndirectedWeightedGraph.h"
#include "StaticFunctions.h"
#include "WeightedNode.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
#include <climits>
#include <math.h>
using namespace std;

/*
 * 
 */

void solvePart2Week2PA(){
    DirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part2/Week2/dijkstraData2.txt");
    
    priority_queue<int> pq;
    
    
    g.dijkstra(1);
    
    cout << g.getAnswer() << endl;
    
    //other test cases
    
    string testCaseDirectory = "/home/nathan/Extracts/stanford-algs/testCases/course2/assignment2Dijkstra/";
    
    DIR* dir = opendir(testCaseDirectory.c_str());
    
    struct dirent* entry;
    while((entry = readdir(dir))){
        
        struct stat entryinfo;
        string entryName = entry->d_name;
        string entryPath = testCaseDirectory + entryName;
        
        if (!stat(entryPath.c_str(), &entryinfo )){
            if (! S_ISDIR(entryinfo.st_mode)){
                
                if (entryName.find("input", 0) == 0){
                    DirectedWeightedGraph g(entryPath);
                    g.dijkstra(1);
                    string answer = g.getAnswer();
                    
                    string answerFile = testCaseDirectory + entryName.replace(0,5,"output");
                    ifstream infile(answerFile);
                    string actualAnswer;
                    getline(infile, actualAnswer);
                    infile.close();
                    
                    if (answer != actualAnswer){
                        cout << entryName << endl;
                        cout << "Computed: " << answer << endl;
                        cout << "Beaunus:  " << actualAnswer << endl;
                    }
                    
                }
            }
        }
    }
    
    closedir(dir);
    
    //    cout << endl;
//    
//    for (int i = 1; i < 201; i++){
//        cout << i << ": " << g.getNodeList()[i]->getDistance() << endl;
//    } 
    //12875,18782,12478,19093,2367,3620,2029,10758,10728,8068
    //12875,18782,12478,19093,2367,3620,2029,10758,10728,8068
    //12875,18782,12478,19093,2367,3620,2029,10758,10728,8068
    //3024,3684,2947,2052,2367,2399,2937,2442,2610,3068
    //3024,3684,2947,2052,2367,2399,2937,2442,2610,3068
    
    //3024,3920,2947,2660,2367,2399,2937,2442,4477,3068
    
    //correct:
    //2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
    
    //bft
    // wrong   bft: 561210,512598,559247,674810,485338,534807,364902,307456,511454,453935
    // correct bft: 561210,512598,559247,660768,485338,534807,364902,307456,511454,453935
    
    
    //medTest
//    0 0
//    1 1000000
//    2 4
//    3 1000000
//    4 1000000
//    5 11
//    6 21
//    7 14
    
    //medTest2
//    0 0
//    1 6
//    2 6
//    3 5
//    4 1000000
//    5 13
//    6 13
//    7 15
}

void solvePart2Week3PA(){
    pqueue<int> Q;
    
    ifstream infile("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part2/Week3/Median.txt");
    
    string line;
    int number;
    int result = 0;
    
    while (getline(infile, line)){
        number = stoi(line);
        Q.push(number);
        
        if (Q.size() % 2 == 0) //is even
            result += Q[Q.size()/2 - 1];
        else //is odd
            result += Q[(Q.size()+1)/2 - 1];
        
        result = result % 10000;
    }

    cout << result << endl;
    
    infile.close();
}

void solvePart3Week1(){
    UndirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week1/input_random_17_100.txt");
    cout << g.prim() << endl;
}
// 106 in 1.5 minutes
void solvePart3Week2Q1(){
    UndirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week2/clustering1.txt");
//    UndirectedWeightedGraph g("/home/nathan/Extracts/stanford-algs/testCases/course3/assignment2Clustering/question1/input_completeRandom_1_8.txt");
    
    cout << g.kspacing(4) << endl;
}

// 6118 in 2.5 minutes
void solvePart3Week2Q2(){
    UndirectedWeightedGraph g("/home/nathan/Extracts/stanford-algs/testCases/course3/assignment2Clustering/question2/input_random_45_512_24.txt");
//    UndirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week2/clustering_big.txt");
    
    
    cout << g.findKWithSpacingOfThree() << endl;
}

int main(int argc, char** argv) {
    solvePart3Week2Q2();
    return 0;
}

