package ui;

import model.transcript;

public class main
{
    public static void main(String[]args)
    {
        transcript t1 = new transcript("Jane Doe", 7830);
        transcript t2 = new transcript("Ada Lovelace", 8853);
        transcript t3 = new transcript("Fuck UBC", 1337);

        t1.addGrade("CPSC-210", 3.5);
        t1.addGrade("ENGL-201", 4.0);
        t1.addGrade("CPSC-110", 3.1);

        t2.addGrade("SEX-69", 3.9);
        t3.addGrade("DICK-12", 4.0);

        System.out.print(t1.getStudentName() + ": ");
        System.out.print(t1.getStudentID() + ": \n");
        t1.printTranscript();

        t1.setStudentName("Fuck Wit");
        t1.setStudentID(69);

        System.out.println(t1.getGPA());
        System.out.println(t1.getCourseAndGrade("ENGL-201"));



    }



}
