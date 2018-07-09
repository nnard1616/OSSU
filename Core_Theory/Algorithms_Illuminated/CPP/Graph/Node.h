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
 * File:   Node.h
 * Author: Nathan Nard
 *
 * Created on July 4, 2018, 11:22 AM
 */

#ifndef NODE_H
#define NODE_H

#include <ostream>
#include <set>
#include <iostream>

using namespace std;

//for sorting Node pointers in the neighbors set.
template <class T> struct ptrLess {
    bool operator() (const T* x, const T* y) const {return *x<*y;}
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef bool result_type;
};
    
    
class Node{
public:
    

    //Constructors
    Node();
    Node(int value);
    Node(const Node& orig);
    
    virtual ~Node();
    
    int getValue () const;
    void setValue (int i) ;
    bool isVisited() const { return visited;}
    void setVisited( bool b){visited = b;}
    set<Node*, ptrLess<Node>>* getNeighbors();
    bool allNeighborsVisited();
    
    void addNeighbor(Node* n) ;
    Node* selectNeighbor(set<Node*>& alreadyVisited);
    

    //Operators
    bool operator<   (const Node &n1) const;
    bool operator==  (const Node &n1);
    bool operator!=  (const Node &n1);
    friend ostream& operator<<  (ostream& os, const Node& n);
    
private:
    
    //Attributes
    int value;
    bool visited;
    set<Node*, ptrLess<Node>> neighbors;
    
    
};


#endif /* NODE_H */

