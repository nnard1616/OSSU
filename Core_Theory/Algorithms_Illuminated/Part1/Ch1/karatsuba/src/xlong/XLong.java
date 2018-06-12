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
package xlong;

/**
 *
 * @author Nathan Nard
 */
public class XLong {
    
    private String number;
    
    /**************************************************************************/
    /*  Constructors                                                          */
    /**************************************************************************/
    public XLong() {
        this("0");
    }
    
    public XLong(String number){
        if (isValidNumber(number))
            this.number = number;
        else
            throw new IllegalStateException(number + " is not an integer.");
    }
    
    /**************************************************************************/
    /*  Checkers                                                              */
    /**************************************************************************/
    private boolean isValidNumber(String candidate){
        String validNums = "0123456789";
        
        //check that each digit is one of the valid numbers.
        for (char c : candidate.toCharArray())
            if (!validNums.contains(Character.toString(c)))
                return false;
        
        return true;
    }
    
    private boolean isPowerOf2(int n){
        if (n == 1)
            return true;
        
        if (n%2 == 0)
            n /= 2;
        else
            return false;
        
        return isPowerOf2(n);
    }
    
    
    /**************************************************************************/
    /*  Getters & Setter                                                      */
    /**************************************************************************/
    public int length(){
        return this.number.length();
    }
    
    public String getNumber() {
        return number;
    }
    
    public void setNumber(String number) {
        this.number = number;
    }

    
    /**************************************************************************/
    /*  Helpers                                                               */
    /**************************************************************************/
    /**
     * Adds leading zeroes to other number until both this and other
     * are the same length.
     * 
     * @param other
     */
    private void tackOnLeadingZeroesTo(XLong other){
        while(other.length() < this.length())
            other.setNumber("0" + other.getNumber());
    }
    
    /**
     * Adds n trailing zeroes to this number.
     * @param other 
     */
    private void tackOnTrailingZeroes(int n){
        while (n > 0){
            this.setNumber(this.getNumber() + "0");
            n--;
        }
    }
    
    private void trimLeadingZeroes(){
        if (length() == 1)
            return;
        
        // need to also check that length is > 1 so that numbers like '00' 
        // don't cause errors.
        while (this.getNumber().charAt(0) == '0' && length() > 1)
            this.setNumber(String.copyValueOf(this.getNumber().toCharArray(), 
                                              1, 
                                              this.length()-1));
    }
    
    /**
     * Converts chars '0','1','2','3','4','5','6','7','8','9' to their literal
     * int variants.
     * 
     * @param digit
     * @return int literal of digit
     */
    private int string2Int(String number){
        int result = 0;
        int zeroes = number.length()-1; // determines place value of digit.
        
        for (char c : number.toCharArray()){
            result += (c - '0')*Math.pow(10,zeroes);
            zeroes--;
        }
        return result;
    }
    
    
    /**************************************************************************/
    /*  Math Operations                                                       */
    /**************************************************************************/
    /**
     * Assumes both XLongs have lengths that are powers of 2 and are the same
     * length.
     * 
     * @param other
     * @return product of this and other XLong.
     */
    public XLong karatMultiplyBy(XLong other){
        
        //base case, both numbers are single digit values.
        if (length() == 1 && other.length() == 1){
            int n1 = string2Int(number);
            int n2 = string2Int(other.getNumber());
            int p = n1*n2;
            return new XLong(""+p);
        }
        
        //determine which number is the longer and shorter number.
        XLong longer;
        XLong shorter;
        if (length() > other.length()){
            longer = this;
            shorter = other;
        }else{
            longer = other;
            shorter = this;
        }
        
        //add leading zeroes to the longer number until its length is a power
        //of 2.
        while(!isPowerOf2(longer.length()))
            longer.setNumber("0" + longer.getNumber());
        
        //add leading zeroes to the shorter number until it matches the length
        //of the longer number.
        longer.tackOnLeadingZeroesTo(shorter);
        
        XLong a = new XLong(String.copyValueOf(number.toCharArray(), 
                                               0, 
                                               length()/2));
        
        XLong b = new XLong(String.copyValueOf(number.toCharArray(), 
                                               length()/2, 
                                               length()/2));
        
        XLong c = new XLong(String.copyValueOf(other.getNumber().toCharArray(), 
                                               0, 
                                               other.length()/2));
        
        XLong d = new XLong(String.copyValueOf(other.getNumber().toCharArray(), 
                                               other.length()/2, 
                                               other.length()/2));
        
        
        XLong ac   = a.karatMultiplyBy(c);
        XLong bd   = b.karatMultiplyBy(d);
        XLong foil = (a.add(b)).karatMultiplyBy(c.add(d));//(a+b)(c+d)
        XLong sub  = ac.add(bd);
        XLong diff = foil.subtract(sub);//(a+b)(c+d)-ac-bd
        
        
        //multiply ac by 10^n, if ac is not 0
        if (!ac.getNumber().equals("0"))
            ac.tackOnTrailingZeroes(length());
        
        //multiply ((a+b)(c+d)-ac-bd) by 10^n/2
        diff.tackOnTrailingZeroes(length()/2);
        
        //bring it all together to make the answer.
        XLong result = (ac.add(diff)).add(bd);
        
        return result;
    }
    
    /**
     * Adds the numbers together.
     * @param other
     * @return sum of this and other XLong.
     */
    public XLong add(XLong other){
        String sum = "";
        int carry = 0; //for when we need to carry a 1.  0 otherwise.
        
        //make sure both numbers are of the same length, add leading zeroes
        //to the shorter number if not.
        if (this.length() > other.length())
            this.tackOnLeadingZeroesTo(other);
        if (other.length() > this.length())
            other.tackOnLeadingZeroesTo(this);
        
        //cycle through digits, starting with ones place (last index), adding 
        //the numbers and a carry if one was generated in the previous cycle.
        for (int i = length()-1; i >= 0; i--){
            
            //convert chars to ints
            int d1 = number.charAt(i) - '0';
            int d2 = other.getNumber().charAt(i) -'0';
            
            int s = d1 + d2 + carry;
            
            //check if we need to carry a 1
            if (s >= 10){
                carry = 1;
                s -= 10;
            }else
                carry = 0;
            
            sum = s + sum;
        }
        
        if (carry == 1)
            sum = 1 + sum;
        
        //get rid of leading zeroes.
        this.trimLeadingZeroes();
        other.trimLeadingZeroes();
        
        
        return new XLong(sum);
    }
    
    /** Assumes number to be subtracted is smaller than the current number.
     * 
     * @param other
     * @return difference of other number from this number.
     */
    public XLong subtract(XLong other){
        XLong otherCopy = new XLong(other.toString());
        XLong step = new XLong("1");
        XLong accumulator = new XLong(); //keeps track of difference
        
        this.tackOnLeadingZeroesTo(otherCopy);
        
        //add steps to otherCopy and accumulator until otherCopy equals this 
        //number.  Step size increases by factor of 10 each time a place value
        //is matched with this number.
        
        //cycle through digits, starting with ones place.
        for(int i = length()-1; i >= 0; i--){
            
            //keep adding step to otherCopy until current place value
            //being examined matches that of this number's corresponding 
            //place value.
            while(otherCopy.getNumber().charAt(i) != number.charAt(i)){
                otherCopy = otherCopy.add(step);
                accumulator = accumulator.add(step);
            }
            step.setNumber(step.getNumber()+ "0");//multiply stepsize by 10
        }
        
        return accumulator;
    }

    
    /**************************************************************************/
    /*  Overrides                                                             */
    /**************************************************************************/
    @Override
    public String toString() {
        return this.number;
    }

    @Override
    public boolean equals(Object obj) {
        return number.equals(((XLong)obj).getNumber());
    }
}