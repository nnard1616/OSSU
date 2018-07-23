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
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

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

int main(int argc, char** argv) {
    twoSum();
    return 0;
}