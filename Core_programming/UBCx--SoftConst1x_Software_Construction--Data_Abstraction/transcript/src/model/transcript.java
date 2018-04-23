package model;

import java.util.ArrayList;

//INVARIANT: course and grade lists are same size.  Indices in both lists correspond to each other.
public class transcript
{
    private String name;
    private int ID;
    private ArrayList<String> courses = new ArrayList<>();
    private ArrayList<Double> grades = new ArrayList<>();

    //CONSTRUCTOR
    public transcript (String student_name, int student_ID) { name = student_name; ID = student_ID; }

    //GETTER
    public String getStudentName(){return name;}

    //GETTER
    public int getStudentID(){return ID;}

    //SETTER
    public void setStudentName(String new_name){ name = new_name; }

    //SETTER
    public void setStudentID(int new_ID){ ID = new_ID; }


    //REQUIRES: grade is float in [0,4]
    //MODIFIES: this
    //EFFECTS : appends course title and corresponding grade to student's transcript.
    public void addGrade(String in_course, Double in_grade)
    {
        courses.add(in_course);
        grades.add(in_grade);
    }

    //GETTER
    public String getCourseAndGrade(String course)
    {

        int gradeIndex = courses.indexOf(course);
        double grade = grades.get(gradeIndex);
        String courseAndGrade = course + ": " + grade;

        return courseAndGrade;
    }

    //EFFECTS : print out full transcript and average GPA to console.
    public void printTranscript()
    {
        //go through each course in courses
        for (String course : courses)
        {
            //save course index
            int ind = courses.indexOf(course);

            //use course index to get corresponding grade from grades list
            double grade = grades.get(ind);

            //print course title and corresponding grade to console.
            System.out.println(course + ": " + grade );
        }

        System.out.println("Overall GPA: " + getGPA());
    }

    //GETTER
    public double getGPA()
    {
        double totalGrade = 0.0;

        for (double grade: grades)
        {
            totalGrade += grade;
        }
        return totalGrade/grades.size();
    }


}
