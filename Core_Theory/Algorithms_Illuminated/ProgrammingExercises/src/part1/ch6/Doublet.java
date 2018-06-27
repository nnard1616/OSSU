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
package part1.ch6;

/**
 *
 * @author Nathan Nard
 */
public class Doublet implements Comparable{
    public final int X;
    public final int W;

    public Doublet(){
        this(0, 0);
    }

    public Doublet(int x, int w){
        X = x;
        W = w;
    }

    @Override
    public int compareTo(Object o) {
        if (o.getClass() != this.getClass())
            throw new IllegalArgumentException("doublet compared with "
                                             + "non-doublet");

        Doublet d = (Doublet)o;

        if (this.X < d.X)
            return -1;
        if (this.X > d.X)
            return 1;
        return 0;
    }

    @Override
    public boolean equals(Object o) {
        if (o.getClass() != this.getClass())
            throw new IllegalArgumentException("doublet compared with "
                                             + "non-doublet");
        Doublet d = (Doublet)o;

        if (this.X == d.X)
            return true;
        return false;
    }

    @Override
    public String toString() {
        return "X: " + X + " W: " + W;
    }
}
