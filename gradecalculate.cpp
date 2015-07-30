// ******************************************************************
//
//  This program computes student grades. For each student, two
//  quiz grades (graded on a 10 point basis), one midterm exam grade
//  and one final exam grade (each on a 100 point basis) are read
//  in. The final numeric grade is computed weighing the final 
//  exam 50%, the midterm 25%, and the quizzes 25%. The numeric
//  grade and corresponding letter grade are output.
//
// ******************************************************************

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>

using namespace std;

struct StudentRecord
{
    int quiz1, quiz2, midtermExam, finalExam;
    double courseAverage;
    char letterGrade;
};

void inputRecord (StudentRecord& record);
char letterGrade (double numericGrade);
void outputRecord (StudentRecord record);
void computeAverage (StudentRecord& record);


int main()
{
    StudentRecord student;
    
    inputRecord(student);
    computeAverage(student);
    outputRecord(student);
    
    return 0;
}


void inputRecord (StudentRecord& record)
{
    int readNum;
    fstream inputStream;
    
    inputStream.open("score.txt");
    if (!inputStream.is_open())
    {
        cerr << "Error file opening" << endl;
        exit(1);
    }

    inputStream >> readNum;
    record.quiz1 = readNum;
    
    assert(0 <= record.quiz1 && record.quiz1 <= 10);
    
    inputStream >> readNum;
    record.quiz2 = readNum;
    
    assert(0 <= record.quiz2 && record.quiz2 <= 10);

    inputStream >> readNum;
    record.midtermExam = readNum;

    inputStream >> readNum;
    record.finalExam = readNum;
    
    inputStream.close();

}
char letterGrade (double numericGrade)
{
    char letter;
    
    if (numericGrade < 60)
        letter = 'F';
    else if (numericGrade < 70)
        letter = 'D';
    else if (numericGrade < 80)
        letter = 'C';
    else if (numericGrade < 90)
        letter = 'B';
    else
        letter = 'A';
    
    return letter;
}


void outputRecord (StudentRecord record)
{
    ofstream outputStream;
    outputStream.open("output.txt");
    
    if (!outputStream.is_open())
    {
        cerr << "Error file writing" << endl;
        exit(1);
    }
    
    outputStream << "Quiz Scores: " << record.quiz1 << "  "
                 << record.quiz2 << endl;
    outputStream << "Midterm Exam Score: " << record.midtermExam << endl;
    outputStream << "Final Exam Score: " << record.finalExam << endl;
    outputStream << endl;
    outputStream << "Course Average: " << record.courseAverage << endl;
    outputStream << "Final Letter Grade: " << record.letterGrade << endl;
    
    cout << "Quiz Scores: " << record.quiz1 << "  " << record.quiz2 << endl;
    cout << "Midterm Exam Score: " << record.midtermExam << endl;
    cout << "Final Exam Score: " << record.finalExam << endl;
    cout << endl;
    cout << "Course Average: " << record.courseAverage << endl;
    cout << "Final Letter Grade: " << record.letterGrade << endl;
    cout << "Successfully written on the text file" << endl;
    
    outputStream.close();

}


void computeAverage (StudentRecord& record)
{
    const double EXAM_WT = 0.5;
    const double MIDTERM_WT = 0.25;
    const double QUIZ_WT = 0.25;
    double quiz1Percent, quiz2Percent;
    
    //
    // Convert the 10 point quizzes to a percent, then find the average
    //
    quiz1Percent = 10 * record.quiz1;
    quiz2Percent = 10 * record.quiz2;
    double quizAvg = (quiz1Percent + quiz2Percent) / 2.0;
    
    //
    // Compute the weighted average to get the numeric course grade
    //
    record.courseAverage = quizAvg * QUIZ_WT + record.midtermExam * MIDTERM_WT +
    record.finalExam * EXAM_WT;
    
    //
    // Call the letterGrade function to find the corresponding letter grade
    record.letterGrade = letterGrade (record.courseAverage);
    
}
