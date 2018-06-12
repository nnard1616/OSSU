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


import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author Nathan Nard
 */
public class XLongTest {
    private String good = "3141592653589793238462643383279502884197169399375105"
            + "820974944592";
    private String bad1 = "343.4";
    private String bad2 = "duck";
    private String bad3 = "34it";
    
    public XLongTest() {
    }
    @Test
    public void testProperInitialization() {
        boolean pass = true;
        String failmessage = "";
        
        try{
            XLong first = new XLong(good);
        }catch(IllegalStateException ISE){
            pass = false;
            failmessage = "A good number did not pass.";
        }
        
        assertEquals(failmessage, true, pass);
        
        try{
            XLong second = new XLong(bad1);
            pass = false;
            failmessage = "Bad1 got through.";
        }catch(IllegalStateException ISE){
        }
        
        assertEquals(failmessage, true, pass);
        
        try{
            XLong third = new XLong(bad2);
            pass = false;
            failmessage = "Bad2 got through.";
        }catch(IllegalStateException ISE){
        }
        
        assertEquals(failmessage, true, pass);
        
        try{
            XLong fourth = new XLong(bad3);
            pass = false;
            failmessage = "Bad3 got through.";
        }catch(IllegalStateException ISE){
        }
        
        assertEquals(failmessage, true, pass);
    }
    

    
    @Test
    public void testAdd(){
        XLong x = new XLong( "987654321");
        XLong y = new XLong(  "55555555");
        XLong e = new XLong("1043209876");
        
        assertEquals(e, x.add(y));
    }
    
    @Test
    public void testSubtract(){
        XLong x = new XLong( "9876");
        XLong y = new XLong(  "555");
        XLong e = new XLong( "9321");
        
        assertEquals(e, x.subtract(y));
    }
    
    @Test
    public void testKarat(){
        XLong x = new XLong( "5678");
        XLong y = new XLong( "1234");
        XLong e = new XLong( "7006652");
        
        assertEquals(e, x.karatMultiplyBy(y));
    }
}
