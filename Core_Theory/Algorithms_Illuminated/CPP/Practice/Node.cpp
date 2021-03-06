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
 * File:   Node.cpp
 * Author: Nathan Nard
 * 
 * Created on July 4, 2018, 11:54 AM
 */

#include "Node.h"

Node::Node() {
    value = 0;
}

Node::Node(int value){
    this->value = value;
}

Node::Node(const Node& orig) {
    this->value = orig.getValue();
}

int Node::getValue() const {
    return value;
}

Node::~Node() {
}

bool Node::operator==(const Node& n1) {
    return n1.getValue() == getValue();
}

bool Node::operator!=(const Node& n1) {
    return ! (n1.getValue() == getValue());
}

bool Node::operator<(const Node& n1) {
    return getValue() < n1.getValue();
}

ostream& operator<<(ostream& os, const Node& n) {
    os << n.value << endl;
    return os;
}
