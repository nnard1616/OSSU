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
 * File:   dataPoint.h
 * Author: Nathan Nard
 *
 * Created on August 25, 2018, 8:10 PM
 */

#ifndef DATAPOINT_H
#define DATAPOINT_H

class dataPoint {
public:
    
    dataPoint(int id, double x, double y);
    dataPoint(const dataPoint& d):dataPoint(d.getID(), d.getX(), d.getY()){}
    
    double distance(dataPoint other);
    int getID() const;
    double getX()  const;
    double getY()  const;
    
    bool operator==(const dataPoint& other);
    
private:
    const int ID;
    const double X, Y;
    
};

#endif /* DATAPOINT_H */

