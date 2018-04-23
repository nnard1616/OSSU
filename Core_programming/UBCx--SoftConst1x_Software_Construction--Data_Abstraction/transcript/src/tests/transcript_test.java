package tests;

import model.transcript;
import org.junit.*;


import static org.junit.Assert.*;

public class transcript_test
{
    private transcript testTranscript;

    @Before
    public void setUp(){
        testTranscript = new transcript("Titty Fuck Elisa", 1337);

    }

    @Test
    public void testTemplate(){
        testTranscript.setStudentName("Ass Fuck Elisa");
        testTranscript.setStudentID(6969);
        assertEquals(testTranscript.getStudentName(), "Ass Fuck Elisa");
        assertEquals(testTranscript.getStudentID(), 6969);

        testTranscript.addGrade("DICK-12", 4.0);
        testTranscript.addGrade("ASS-69", 3.6);
        assertEquals(testTranscript.getCourseAndGrade("DICK-12"), "DICK-12: 4.0");
        assertTrue(testTranscript.getGPA() == 3.8);

    }
}
