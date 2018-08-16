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
 * File:   PrimEdge.cpp
 * Author: Nathan Nard
 * 
 * Created on July 26, 2018, 3:47 PM
 */

#include "PrimEdge.h"

PrimEdge::PrimEdge(PrimNode* first, PrimNode* second, int weight) {
    this->first = first;
    this->second = second;
    this->weight = weight;
}

PrimNode* PrimEdge::getFirst() const {
    return first;
}

PrimNode* PrimEdge::getSecond() const {
    return second;
}

int PrimEdge::getWeight() const{
    return weight;
}

bool PrimEdge::operator<( PrimEdge& e) {
    return getWeight() < e.getWeight();
}

bool PrimEdge::bothVisited() {
    return first->isVisited() && second->isVisited();
}

bool PrimEdge::oneVisited() {
    return first->isVisited() != second->isVisited();
}

bool PrimEdge::noneVisited() {
    return  (! first->isVisited()) && (! second->isVisited());
}

bool PrimEdge::sameLeaderNodes() {
    return first->getLeader() == second->getLeader();
}

bool PrimEdge::differentLeaderNodes() {
    return ! sameLeaderNodes();
}


ostream& operator<< (ostream& os, const PrimEdge& e){
    os << e.first->getValue() << ' ' << e.second->getValue() << ' ' << e.getWeight();
    return os;
}