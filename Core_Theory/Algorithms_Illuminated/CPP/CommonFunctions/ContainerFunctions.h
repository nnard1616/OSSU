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
 * File:   ContainerFunctions.h
 * Author: Nathan Nard
 *
 * Created on August 17, 2018, 11:11 PM
 */

#ifndef CONTAINERFUNCTIONS_H
#define CONTAINERFUNCTIONS_H

namespace CommonFunctions{
    template <typename ForwardIterator>
    unsigned long long sum_items(ForwardIterator first, ForwardIterator last)
    {
        unsigned long long result = 0;
        while (first != last)
            result += *first++;
        return result;
    }

    template <typename Container>
    unsigned long long sum_items(Container in)
    {
      return sum_items(in.begin(), in.end());
    }

}

#endif /* CONTAINERFUNCTIONS_H */

