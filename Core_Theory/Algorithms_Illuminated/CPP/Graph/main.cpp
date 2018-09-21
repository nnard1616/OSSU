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
#include <iomanip>
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
#include <algorithm>
#include <math.h>
#include <set>
#include <list>
#include <sstream>
#include <string.h>
#include <float.h>
#include <string>
#include <c++/7/stdexcept>
#include <c++/7/iosfwd>
#include "../datastructures/WeightedTreeNode.h"
#include "../datastructures/heapp.hpp"
#include "../datastructures/WeightComparator.h"
#include "../datastructures/dataPoint.h"
#include "DirectedGraph.h"
using namespace std;

/*
 * 
 */

//434821 968 459 313 211 
void solvePart2Week1Q1(){
//    string filename = "/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part2/Week1/SCC.txt";
    
//    string filename = "/home/nathan/Extracts/stanford-algs/testCases/course2/assignment1SCC/input_mostlyCycles_68_320000.txt";
    string filename = "/home/nathan/Extracts/stanford-algs/testCases/course2/assignment1SCC/input_mostlyCycles_39_3200.txt";
    
    DirectedGraph g;
    g.readInData(filename);
    g.findSCCs();
    
}


void solvePart2Week2PA(){
    DirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part2/Week2/dijkstraData2.txt");
    
    priority_queue<int> pq;
    
    g.readInDataPT2WK2();
    g.dijkstra(1);
    
    cout << g.getAnswerPT2WK2() << endl;
    
//    //other test cases
//    
//    string testCaseDirectory = "/home/nathan/Extracts/stanford-algs/testCases/course2/assignment2Dijkstra/";
//    
//    DIR* dir = opendir(testCaseDirectory.c_str());
//    
//    struct dirent* entry;
//    while((entry = readdir(dir))){
//        
//        struct stat entryinfo;
//        string entryName = entry->d_name;
//        string entryPath = testCaseDirectory + entryName;
//        
//        if (!stat(entryPath.c_str(), &entryinfo )){
//            if (! S_ISDIR(entryinfo.st_mode)){
//                
//                if (entryName.find("input", 0) == 0){
//                    DirectedWeightedGraph g(entryPath);
//                    g.dijkstra(1);
//                    string answer = g.getAnswer();
//                    
//                    string answerFile = testCaseDirectory + entryName.replace(0,5,"output");
//                    ifstream infile(answerFile);
//                    string actualAnswer;
//                    getline(infile, actualAnswer);
//                    infile.close();
//                    
//                    if (answer != actualAnswer){
//                        cout << entryName << endl;
//                        cout << "Computed: " << answer << endl;
//                        cout << "Beaunus:  " << actualAnswer << endl;
//                    }
//                    
//                }
//            }
//        }
//    }
//    
//    closedir(dir);
    
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
    
    //read in the values into Q, the pqueue
    while (getline(infile, line)){
        number = stoi(line);
        Q.push(number); //O(nlogn)
        
        //add median of current Q, median is found at index half of Q's size.
        //(Round to the floor for even number of values)
        if (Q.size() % 2 == 0) //Even number of values
            result += Q[Q.size()/2 - 1];
        else //Odd number of values
            result += Q[(Q.size()+1)/2 - 1];
        
        //instructions only want the last 4 digits of the sum of medians.
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
//    UndirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week2/clustering1.txt");
    UndirectedWeightedGraph g("/home/nathan/Extracts/stanford-algs/testCases/course3/assignment2Clustering/question1/input_completeRandom_1_8.txt");
    
    cout << g.kspacing(4) << endl;
}

// 6118 in 2.5 minutes
void solvePart3Week2Q2(){
    UndirectedWeightedGraph g("/home/nathan/Extracts/stanford-algs/testCases/course3/assignment2Clustering/question2/input_random_45_512_24.txt");
//    UndirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week2/clustering_big.txt");
    
    
    cout << g.findKWithSpacingOfThree() << endl;
}

//huffman codes
void solvePart3Week3Q12(){
    //    string filename = "/home/nathan/Extracts/stanford-algs/testCases/course3/assignment3HuffmanAndMWIS/question1And2/input_random_1_10.txt";
    
    string filename = "/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week3/huffman.txt";
    
    ifstream infile(filename);
    
    string line;
    
    getline(infile, line);
    
    int numberOfNodes = stoi(line);
    ull readWeight;
    int nodeValue = 1;
    pqueue<WeightedTreeNode*, WeightedTreeNodeComparator<WeightedTreeNode> > nodes;
    
    //read in value weights and create a WeightedTreeNode for each.
    //Nodes are sorted in ascending order of weight
    while (getline(infile, line)){
        readWeight = stoull(line);
        nodes.push(new WeightedTreeNode(nodeValue, readWeight)); //O(nlogn)
        nodeValue++;
    }
 
    
    WeightedTreeNode* n1;
    WeightedTreeNode* n2;
    
    WeightedTreeNode* combined;
    
    //assumes more than 1 node at start, create the encoding tree
    while (nodes.size() > 1){
        n1 = nodes.top();
        nodes.pop();
        
        n2 = nodes.top();
        nodes.pop();
        
        combined = new WeightedTreeNode(0, n1, n2);
        nodes.push(combined); //O(nlogn)
    } //end of creating encoding tree
    
    
    //now determine min and max code lengths, via depth first search
    int maxDepth = INT32_MIN;
    int minDepth = INT32_MAX;
    
    vector<WeightedTreeNode*> dfs; //depth first search, facilitated by stack
    
    dfs.push_back(nodes.top());
    WeightedTreeNode* current;
    
    while ( ! dfs.empty()){
        current = dfs.back();
        if(current->getValue() == 0 ){
            dfs.pop_back();
            dfs.push_back(current->getLeft());
            dfs.push_back(current->getRght());
        } else {
            maxDepth = max(current->getDepth(), maxDepth);
            minDepth = min(current->getDepth(), minDepth);
            dfs.pop_back();
        }
    }
    
    
    cout << maxDepth << endl << minDepth << endl;
    infile.close();
}

ull sum_weights(vector<WeightedTreeNode*>& nodes){
    ull result = 0;
    for (auto& i : nodes){
        result += i->getWeight();
    }
    return result;
}

void solvePart3Week3Q3(){
    //    string filename = "/home/nathan/Extracts/stanford-algs/testCases/course3/assignment3HuffmanAndMWIS/question3/input_random_1_10.txt";
    
    string filename = "/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week3/mwis.txt";
    
    ifstream infile(filename);
    
    string line;
    
    getline(infile, line);
    
    int numberOfNodes = stoi(line);
    ull readWeight;
    int nodeValue = 1;
    vector<WeightedTreeNode*> nodes;
    
    while (getline(infile, line)){
        readWeight = stoull(line);
        nodes.push_back(new WeightedTreeNode(nodeValue, readWeight));
        nodeValue++;
    }
    
    //Main Algorithm
    
    map<int, vector<WeightedTreeNode*>> mwis; //log
    
    mwis[0].clear();
    mwis[1].push_back(nodes[0]);
    
    vector<WeightedTreeNode*> vim2, vim1; //potential sets
    ull swim2, swim1; //working sums of pathways's weights
    
    for (int i = 2; i <= nodes.size(); i++){
        vim2.clear();
        vim1.clear();
        
        //recall set from two iterations ago
        vim2.insert(vim2.end(), mwis[i-2].begin(), mwis[i-2].end());
        
        //recall set from last iteration
        vim1.insert(vim1.end(), mwis[i-1].begin(), mwis[i-1].end());
        
        vim2.push_back(nodes[i-1]);
        
        swim2 = sum_weights(vim2);
        swim1 = sum_weights(vim1);
        
        if (swim2 > swim1)
            mwis[i] = vim2;
        else
            mwis[i] = vim1;
    }

    int targets[8] = {1, 2, 3, 4, 17, 117, 517, 997};
    
    char present = '0';
    
    for (auto& i : targets){
        for (auto& j : mwis[numberOfNodes]){
            if (j->getValue() == i)
                present = '1';
        }
        cout << present;
        present = '0';
    }
    
    infile.close();
}

//2493893
void solvePart3Week4Q1(){

//    string filename = "/home/nathan/Extracts/stanford-algs/testCases/course3/assignment4Knapsack/input_random_1_4_4.txt";
    
    string filename = "/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week4/knapsack1.txt";
    
    ifstream infile(filename);
    
    string line;
    
    getline(infile, line);
    vector<int> lineNumbers = strings_to_ints(split(line, ' '));
    
    int capacity      = lineNumbers[0]; 
    int numberOfNodes = lineNumbers[1];
    
    int weight;
    int value;
    int itemNumber = 1;
    
    map<int, pair<int, int> > items;
    
    while (getline(infile, line)){
        lineNumbers = strings_to_ints(split(line, ' '));
        
        value      = lineNumbers[0];
        weight     = lineNumbers[1];
        
        items[itemNumber] = pair<int, int>(value, weight);
        itemNumber++;
        
    }
    
    cout << items.size() << " : " << numberOfNodes << endl;
    
    
    //implement the algo
    long long A[numberOfNodes+1][capacity+1];
    
    for (int x = 0; x <= capacity; x++){
        A[0][x] = 0;
    }
    
    for (int i = 1; i < numberOfNodes+1; i++){
        for (int x = 0; x < capacity+1; x++){
            if (x-items[i].second >= 0)
                A[i][x] = max(A[i-1][x], A[i-1][x-items[i].second]+items[i].first);
            else
                A[i][x] = A[i-1][x];
        }
    }
    
    
    cout << A[numberOfNodes][capacity] << endl;
    
    
}

int rec (int i, int x, map<pair<int,int>,int>& tab, map<int, pair<int, int>>& items){
    if (i == 0)
        return 0;
    try{
        return tab.at(pair<int, int>(i,x));
    }catch (std::out_of_range){
        if (x - items[i].second >= 0)
            tab[pair<int, int>(i,x)] = max(rec(i-1, x, tab, items), rec(i-1, x - items[i].second, tab, items) + items[i].first);
        else
            tab[pair<int, int>(i,x)] = rec(i-1, x, tab, items);
        return tab[pair<int, int>(i,x)];
    }
}

void solvePart3Week4Q2(){
    
//    string filename = "/home/nathan/Extracts/stanford-algs/testCases/course3/assignment4Knapsack/input_random_1_4_4.txt";
    
    string filename = "/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part3/Week4/knapsack_big.txt";
    
    ifstream infile(filename);
    
    string line;
    
    getline(infile, line);
    vector<int> lineNumbers = strings_to_ints(split(line, ' '));
    
    int capacity      = lineNumbers[0]; 
    int numberOfNodes = lineNumbers[1];
    
    int weight;
    int value;
    int itemNumber = 1;
    
    map<int, pair<int, int> > items;
    
    while (getline(infile, line)){
        lineNumbers = strings_to_ints(split(line, ' '));
        
        value      = lineNumbers[0];
        weight     = lineNumbers[1];
        
        items[itemNumber] = pair<int, int>(value, weight);
        itemNumber++;
        
    }
    
    cout << items.size() << " : " << numberOfNodes << endl;
    
    map <pair<int, int>, int> tab;
    
    cout << rec(numberOfNodes, capacity, tab, items) << endl;
    
    infile.close();
    
}

void testHeapp(){
    heapp<WeightedNode*, DistanceComparator> h;
    if (h.size() != 0){
        cout << "Problem initializing heapp" << endl;
        return;
    }
    

//    void insert(Comparable object);  inserting new items in order.
    WeightedNode* n = new WeightedNode(1);
    n->setDistance(4);
    h.insert(n);
    if (h.size() != 1){
        cout << "Problem inserting into heapp" << endl;
        return;
    }
    
    int weights[8] = {4,8,9,4,12,9,11,13};
    
    for (int i = 0; i < 8; i++){
        n = new WeightedNode(i+2);
        n->setDistance(weights[i]);
        h.insert(n);
    }
    
    if (h.size() != 9){
        cout << "Problem inserting multiples into heapp" << endl;
        return;
    }
    
    std::stringstream ss;
    ss << h << endl;
    
    string expected = "4 \n4 8 \n9 4 12 9 \n11 13 \n";
    
    if (strcmp(ss.str().c_str(), expected.c_str()) != 0){
        cout << "Problem printing heapp" << endl;
        return;
    }
        
//    Comparable top();
    n = h.top();
    
    if (n->getValue() != 1){
        cout << "Problem getting top of heapp" << endl;
        return;
    }
    
//    void pop();
    h.pop();
    
    if (h.size() != 8){
        cout << "Problem with pop of heapp, not being removed or improper resizing" << endl;
        return;
    }
    
    std::stringstream ss2;
    ss2 << h << endl;
    
    expected = "4 \n4 8 \n9 13 12 9 \n11 \n";
    
    if (strcmp(ss2.str().c_str(), expected.c_str()) != 0){
        cout << "Problem popping and re-heappifying heapp" << endl;
        return;
    }
    
    //inserting items out of order.
    
    int weights2[3] = {7, 10, 5};
    
    for (int i = 0; i < 3; i++){
        n = new WeightedNode(i+h.size());
        n->setDistance(weights2[i]);
        h.insert(n);
    }
    
    std::stringstream ss3;
    ss3 << h << endl;
    
    expected = "4 \n4 8 \n7 5 12 9 \n11 9 13 10 \n";
    
    if (strcmp(ss3.str().c_str(), expected.c_str()) != 0){
        cout << "Problem inserting out of order and reordering items in heapp" << endl;
        return;
    }
    
//    void update(Comparable object);
    n->setDistance(20);
    h.update(n);
    
    std::stringstream ss4;
    ss4 << h << endl;
    
    expected = "4 \n4 8 \n7 10 12 9 \n11 9 13 20 \n";
    
    if (strcmp(ss4.str().c_str(), expected.c_str()) != 0){
        cout << "Problem modifying (make larger) and reordering items in heapp" << endl;
        return;
    }
    
    n = h.at(5);
    n->setDistance(1);
    h.update(n);
    
    std::stringstream ss5;
    ss5 << h << endl;
    
    expected = "1 \n4 4 \n7 10 8 9 \n11 9 13 20 \n";
    
    if (strcmp(ss5.str().c_str(), expected.c_str()) != 0){
        cout << "Problem modifying (make smaller) and reordering items in heapp" << endl;
        return;
    }
    
    cout << "all tests passed for heapp" << endl;
    
}


void solvePart4Week1Q1(){
//    solvePart2Week2PA();
//    cout << "2599,2610,2947,2052,2367,2399,2029,2442,2505,3068" << endl;
//    DirectedWeightedGraph g1("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part4/Week1/g1.txt");
//    DirectedWeightedGraph g2("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part4/Week1/g2.txt");
//    DirectedWeightedGraph g3("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part4/Week1/g3.txt");
    
    DirectedWeightedGraph g("/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part4/Week1/smallEx.txt");
//    DirectedWeightedGraph g("/home/nathan/Extracts/stanford-algs/testCases/course4/assignment1AllPairsShortestPath/input_random_40_1024.txt");
    
//    g1.readInDataPT4WK1();
//    g2.readInDataPT4WK1();
//    g3.readInDataPT4WK1();
//    
//    if (g1.johnson())
//        cout << g1.getMinPath() << endl;
//    if (g2.johnson())
//        cout << g2.getMinPath() << endl;
//    if (g3.johnson())
//        cout << g3.getMinPath() << endl;
    
    
    g.readInDataPT4WK1();
    
    if (g.johnsonSimplified())
        cout << g.getMinPath() << endl;
    
}

template <typename T>
map< int, vector<vector<T>>>  generateChoicesOfS(vector<T> set){
    map< int, vector<vector<T>>> result;
    vector<T> s;
    
    int n = set.size();
    
    for (int i = 0; i < (1<<n); i++){
        s.clear();
        
        //cycle through possible number of elements
        for (int j = 0; j < n; j++){
            
            if ((i & (1<<j)) > 0){
                s.push_back(set[j]);
            }
        }
        
        //skip empty set
        if (s.size() == 0)
            continue;
        
        //only take those that contain first element.
        if (s[0] == set[0]){
            result[s.size()].push_back(s);
        }
    }
    
    return result;
}

template <class T>
bool operator==(vector<T> v1, vector<T> v2){
    if (v1.size() != v2.size())
        return false;
    for (int i = 0; i < v1.size(); i++)
        if ( ! (v1[i] == v2[i]))
            return false;
    return true;
}

//26442
void solvePart4Week2Q1(){
    //Open up file of data point data
    string filename = "/home/nathan/Programming/OSSU/Core_Theory/"
            "Algorithms-Roughgarden/Part4/Week2/tsp.txt";
    ifstream infile(filename);
    string line;
    
    //read in number of nodes
    getline(infile, line);
    int numberOfNodes = stoi(line);
    
    //Array of data points
    vector<dataPoint*> V;
    
    double x,y;
    int id = 0;
    
    //Read in data point values and store in V.
    while (getline(infile, line)){
        
        vector<string> coors = split(line, ' ');
        
        x = std::stod(coors[0]);
        y = std::stod(coors[1]);
        
        V.push_back(new dataPoint(id, x, y));
        
        id++;
    }
    
    
    cout << setprecision(4) << fixed;
    cout << "Size of V: " << V.size() << " Expected: " << numberOfNodes << endl;
    cout << V[0]->getX() << ' ' << V[0]->getY() << endl;
    
    //Create Subsets of V that contain 1, mapped by length of subset.
    
    map< int, vector<vector<dataPoint*>>> subsets = generateChoicesOfS(V);
    cout << "finished making sets" << endl;
    
    //Create mappings from subsets to corresponding index values of Subset by 
    //Destination 2D array, A, which is initialized soon hereafter.
    
    unsigned int c = 0;
    
    //for quickest lookup of subset index, via subset pointer.
    map<vector<dataPoint*>*, int> subsetIndexing;
    
    //for finding index of a difference of two subsets, much slower lookup
    //differences are not easily mapped to a subset pointer (though a mapping 
    //could probably be made...)
    map<vector<dataPoint*>, int> diffIndexing;
    
    for (int m = 1; m <= numberOfNodes; m++){
        for (auto& s : subsets[m]){
            subsetIndexing[&s] = c;
            diffIndexing[s]   = c++;
        }
    }
    
    cout << c << endl;
    cout << "finished making subset to array index map, "
            "now initializing 2D array...." << endl;

    vector<vector<double>> A;
    vector<double> t;
    
    //Initialize A[{1},1] to 0, all other A[S, 1] to +infinity, 
    //where S is in subsets.
    
    for (int i = 0; i < c; i++){
        t.clear();
        for (int j = 0; j < numberOfNodes; j++){
            if (i == 0 && j == 0)
                t.push_back(0);
            else
                t.push_back(INT32_MAX);
        }
        A.push_back(t);
    }
    
    //Initialize A[{1,x}, x] to C_1x as well.
    
    for (auto& subsetOfSize2 : subsets[2])
        A[ subsetIndexing[ &subsetOfSize2 ] ][ subsetOfSize2[1]->getID() ] 
                = subsetOfSize2[0]->distance(*subsetOfSize2[1]);
    
    cout << "Finished initializing A, now running the dynamic programming "
            "algorithm..." << endl;
    
    vector<dataPoint*> diff;
    int subsetIndex, diffIndex;
    
    //cycle through m = 2,3,4,...., n
    for (int m = 3; m <= numberOfNodes; m++){
        cout << m << "..." << endl;
        
        //cycle through each subset S ⊆ {1,2,3,...,n} of size m and containing 1
        for (auto& S : subsets[m]){
    
            //cycle through j in S, skipping j = 1:
            for (int j = 1; j < S.size(); j++){
                
                //cycle through k in S...
                for (int k = 1; k < S.size(); k++){
                    
                    //... skipping k = j (since j = 1 was skipped above, 
                    //k = 1 will be implicitly skipped as well):
                    if ( j != k){
                        
                        diff = S;
                        diff.erase(diff.begin() + j);
                        subsetIndex = subsetIndexing [ &S ];
                        diffIndex   = diffIndexing [ diff ];
                        
                        //A[S, j] = min(A[S, j], A[S-{j}, k] + C_kj)  
                        //note: C_kj is distance from k to j.
                        A[ subsetIndex ][ S[j]->getID() ] 
                        = min( A[ subsetIndex ][ S[j]->getID() ], 
                               A[ diffIndex ][ S[k]->getID() ]
                               + S[k]->distance(*S[j]));
                        
                    }
                }
            }
        }
    }
    
    cout << "Finished the dynamic programming algorithm,"
            " now searching for min value..." << endl;
    
    //initialize result to max value
    int result = INT32_MAX;
    
    //cycle through j = 2,3,...,n
    for (int j = 1; j < numberOfNodes; j++){
        
        //result = min(result, A[V, j] + C_j1])
        result = min(result, (int)(A[c-1][j] + V[j]->distance(*V[0])));
    }
    
    //print result
    cout << "Answer: " << result << endl;
}

void solvePart4Week3Q1(){
    //Open up file of data point data
    string filename = "/home/nathan/Programming/OSSU/Core_Theory/"
            "Algorithms-Roughgarden/Part4/Week3/nn.txt";
    ifstream infile(filename);
    string line;
    
    //read in number of nodes
    getline(infile, line);
    int numberOfNodes = stoi(line);
    
    //create and populate array of data points
    vector<dataPoint*> V;
    
    double x,y;
    int id = 1;
    
    getline(infile, line);
    
    vector<string> coors = split(line, ' ');
        
    x = std::stod(coors[1]);
    y = std::stod(coors[2]);
    
    dataPoint start(id, x, y);
    id++;
    
    start.setPrevious(&start);
    
    //Read in data point values and store in V.
    while (getline(infile, line) ){
        
        vector<string> coors = split(line, ' ');
        
        x = std::stod(coors[1]);
        y = std::stod(coors[2]);
        
        V.push_back(new dataPoint(id, x, y));
        
        id++;
    }
    
    
    cout << setprecision(4) << fixed;
    cout << "Size of V: " << V.size() 
         << " Expected: " << numberOfNodes-1 << endl;
    cout << start.getPrevious()->getID() << endl;
    
    //initialize distance, d
    double totalPathDistance = 0;
    double dx;
    double minSD = 1000000000; //min square distance for current iteration
    double tempMinSD;
    
    int currNodeComp = 0; //number of comparisons made with current node
    int totalComparisons = 0; //counts total comparisons made.
    int nodesProcessed =  0;
    int nextIndex;
    
    
    //while V is not empty
    while(! V.empty()){
        
        currNodeComp=0;
        
        for (int i =0; i < V.size(); i++){
            currNodeComp++;
            tempMinSD = V[i]->squareDistance(*(start.getPrevious()));
            
            if ( tempMinSD < minSD){
                minSD = tempMinSD;
                nextIndex = i;
            }
            
            //datapoints happen to be sorted by x coordinate...
            dx = (V[i]->getX() - start.getPrevious()->getX());
            
            if (minSD < dx*dx){
                break;
            }
        }
        
        totalComparisons += currNodeComp;
        start.setPrevious(V[nextIndex]);
        V.erase(V.begin()+nextIndex);
        totalPathDistance+=pow(minSD,0.5);
        
        nodesProcessed++;
        if (nodesProcessed % 1000 == 0)
            cout << nodesProcessed << ": " <<  V.size() 
                 << " remaining, with distance of " << totalPathDistance 
                 << ", broken at " << currNodeComp << " when the minDN was at: " 
                 << nextIndex << endl;
        minSD = 1000000000;
    }
    
    totalPathDistance += start.distance(*start.getPrevious());
    //print d
    cout << (int)totalPathDistance << endl;
    cout << "total comparisons: " << totalComparisons << endl;
}

//101100
void solvePart4Week4Q1(){
    //Open up file of data point data
    string filename = "/home/nathan/Programming/OSSU/Core_Theory/Algorithms-Roughgarden/Part4/Week4/2sat6.txt";
    
//    string filename = "/home/nathan/Extracts/stanford-algs/testCases/course4/assignment4TwoSat/input_beaunus_32_10000.txt";
    
    DirectedGraph g;
    
    g.readInData2(filename);
    g.findSCCs();
    
//    cout << g << endl;
}


int main(int argc, char** argv) {
    solvePart4Week4Q1();
    
    return 0;
}

