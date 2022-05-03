#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

enum Grade
{
    F,
    D,
    CMINUS,
    C,
    CPLUS,
    BMINUS,
    B,
    BPLUS,
    AMINUS,
    A
};

const int BAR = 60;
const int CLASSSIZE = 75;

struct StudentData
{
    string lastName;
    string firstName;
    double score;
    double percentage;
    Grade pointGrade;
    Grade curveGrade;
    Grade finalGrade;
};

bool grade_less(StudentData const& l, StudentData const& r) 
{ return l.score > r.score; }

bool name_less(StudentData const& l, StudentData const& r) 
{ return l.lastName < r.lastName; }

StudentData student[CLASSSIZE];




void grabData(string ifileName, StudentData s[], int& size)
{

    ifstream infile;
    infile.open(ifileName);
    int i = 0;
    if (infile.fail())
    {
        cout << " BEEP BOOP FILE NOT FOUND ";
    }
    else
    {
        while (infile >> s[i].lastName >> s[i].firstName >> s[i].score)
        {

            i++;
        }
        size = i;
    }

    infile.close();
    return;
}

string letterGrade(Grade g)
{
    string s;
    switch (g)
    {
    case F:
        s = "F";
        break;
    case D:
        s = "D";
        break;
    case CMINUS:
        s = "C-";
        break;
    case C:
        s = "C";
        break;
    case CPLUS:
        s = "C+";
        break;
    case BMINUS:
        s = "B-";
        break;
    case B:
        s = "B";
        break;
    case BPLUS:
        s = "B+";
        break;
    case AMINUS:
        s = "A-";
        break;
    case A:
        s = "A";
        break;
    default:
        s = "Error";
    }
    return s;
}

void outputGradeBook(string ofileName, StudentData s[], int number_of_students)
{
    ofstream ofile;
    ofile.open(ofileName);

    if (ofile.fail())
    {
        cout << " BEEP BOOP SOMETHING WENT WRONG";

    }
    else
    {
        ofile << left << setw(20) << "Last Name" << setw(20) << "First Name" << setw(12) << "Points" << setw(10) << "Grade" << setw(10);
        ofile << "percent" << setw(12) << "Rank" << setw(12) << "Final" << endl;
        ofile << '\n';

        for (int i = 0; i < number_of_students; i++)
        {
            
             ofile << left << setw (20) << s[i].lastName << setw(20) << s[i].firstName << setw(12) <<setprecision(4)<<s[i].score << setw(10) << letterGrade(s[i].pointGrade);
             ofile<< left << setw(10) << s[i].percentage << setw(12) << letterGrade(s[i].curveGrade) << setw(12) << letterGrade(s[i].finalGrade) << endl;
        }

    }
    ofile.close();
    return;
}

int main()
{
    StudentData s[CLASSSIZE];
    string ifileName, ofileName;
    int number_of_students;

    cout << "Enter the student grade data file: ";
    cin >> ifileName;
    

    grabData(ifileName, s, number_of_students);

    for (int i=0; i < number_of_students; i++)
    {

        Grade grade;
        if (s[i].score > 93)
        {
            grade = A;
            s[i].pointGrade = grade;
        }
        else if (s[i].score > 90)
        {
            grade = AMINUS;
            s[i].pointGrade = grade;
        }
        else if (s[i].score > 87)
        {
            grade = BPLUS;
            s[i].pointGrade = grade;
        }
        else if (s[i].score > 83)
        {
            grade = B;
            s[i].pointGrade = grade;
        }
        else if (s[i].score > 80)
        {
            grade = BMINUS;
            s[i].pointGrade = grade;
        }
        else if (s[i].score > 77)
        {
            grade = CPLUS;
            s[i].pointGrade = grade;
        }
        else if (s[i].score > 73)
        {
            grade = C;
            s[i].pointGrade = grade;
        }
        else if (s[i].score > 67)
        {
            grade = CMINUS;
            s[i].pointGrade = grade;
        }
        else if (s[i].score > 60)
        {
            grade = D;
            s[i].pointGrade = grade;
        }
        else
        {
            grade = F;
            s[i].pointGrade = grade;
        }
    }

    sort(s, s + number_of_students, &grade_less);

    for (int i = 0; i < number_of_students; i++)
    {
        s[i].percentage = ((double(number_of_students) - i) / double(number_of_students)) * 100;
        Grade grade;
        if (s[i].percentage > 90)
        {
            grade = A;
            s[i].curveGrade = grade;
        }
        else if (s[i].percentage > 80)
        {
            grade = AMINUS;
            s[i].curveGrade = grade;
        }
        else if (s[i].percentage > 65)
        {
            grade = BPLUS;
            s[i].curveGrade = grade;
        }
        else if (s[i].percentage > 50)
        {
            grade = B;
            s[i].curveGrade = grade;
        }
        else if (s[i].percentage > 35)
        {
            grade = BMINUS;
            s[i].curveGrade = grade;
        }
        else if (s[i].percentage > 25)
        {
            grade = CPLUS;
            s[i].curveGrade = grade;
        }
        else if (s[i].percentage > 15)
        {
            grade = C;
            s[i].curveGrade = grade;
        }
        else if (s[i].percentage > 10)
        {
            grade = CMINUS;
            s[i].curveGrade = grade;
        }
        else if (s[i].percentage > 5)
        {
            grade = D;
            s[i].curveGrade = grade;
        }
        else
        {
            grade = F;
            s[i].curveGrade = grade;
        }
    }

    for (int i = 0; i < number_of_students; i++)
    {
        Grade grade;
        if (s[i].score < BAR)
        {
            grade = F;
            s[i].finalGrade = grade;
        }
        else
        {
            s[i].finalGrade = s[i].curveGrade;
        }
    }

    sort(s, s + number_of_students, name_less);

    outputGradeBook("Assign5_Zou_Ericson_output.txt", s, number_of_students);

    return 0;
}
