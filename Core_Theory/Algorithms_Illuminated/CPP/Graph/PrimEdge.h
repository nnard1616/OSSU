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
 * File:   PrimEdge.h
 * Author: Nathan Nard
 *
 * Created on July 26, 2018, 3:47 PM
 */

#ifndef PRIMEDGE_H
#define PRIMEDGE_H
#include "PrimNode.h"
#include <fstream>

using namespace std;

class PrimNode;

class PrimEdge {
public:
    PrimEdge(PrimNode* first, PrimNode* second, int weight);
    
    PrimNode* getFirst() const;
    PrimNode* getSecond() const;
    
    bool bothVisited();
    bool oneVisited();
    bool noneVisited();
    
    int getWeight() const;
    
    bool operator< ( PrimEdge &e);
    
    friend ostream& operator<< (ostream& os, const PrimEdge& e);
private:

    PrimNode* first;
    PrimNode* second;
    int weight;
    
};
#endif /* PRIMEDGE_H */

