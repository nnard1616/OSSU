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
 * File:   dataPoint.cpp
 * Author: Nathan Nard
 * 
 * Created on August 25, 2018, 8:10 PM
 */

#include "dataPoint.h"
#include <math.h>

dataPoint::dataPoint(int id, double x, double y) : ID(id), X(x), Y(y){
}

double dataPoint::distance(dataPoint& other) {
    return pow(pow((this->X - other.getX()), 2) + pow((this->Y - other.getY()), 2), 0.5);
}

int dataPoint::squareDistance(dataPoint& other) {
    double dx = (this->X - other.getX());
    double dy = (this->Y - other.getY());
    return dx*dx + dy*dy;
}

int dataPoint::getID() const {
    return ID;
}

double dataPoint::getX() const {
    return X;
}

double dataPoint::getY() const {
    return Y;
}

bool dataPoint::operator==(const dataPoint& other) {
    return getID() == other.getID();
}

dataPoint* dataPoint::previous;

dataPoint* dataPoint::getPrevious() {
    return previous;
}

void dataPoint::setPrevious(dataPoint* d) {
    previous = d;
}



