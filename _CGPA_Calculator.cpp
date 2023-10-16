#include <iostream>        // Include input/output stream library
#include <limits>          // Include limits library for numeric limits
#include <string>          // Include string library for string operations
#include<fstream>             // Including the necessary header for file input/output operation
using namespace std;

class Student {
protected:
    int subjects;          // Number of subjects
    string* grade;         // Array to store grades
    double* credithrs;     // Array to store credit hours

public:
    Student() {
        subjects = 0;
        grade = nullptr;
        credithrs = nullptr;
    }

    // Function to get input from the user
    void getinput() {
        // Get the number of subjects from the user
        cout << "Enter the number of subjects: ";
        cin >> subjects;

        // Validate the input to ensure it is a positive value
        while (cin.fail() || subjects <= 0) {
            cout << "Error: Invalid number of subjects. Please enter a positive value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> subjects;
        }

        // Allocate memory for the grade and credit hours arrays based on the number of subjects
        grade = new string[subjects];
        credithrs = new double[subjects];

        // Get the credit hours and grade for each subject
        for (int i = 0; i < subjects; i++) {
            cout << "Enter credit hours of subject " << i + 1 << ": ";
            cin >> credithrs[i];

            // Validate the credit hours input to ensure it is 1, 2, or 3
            while (credithrs[i] != 1 && credithrs[i] != 2 && credithrs[i] != 3) {
                cout << "Error: Invalid credit hours.\nPlease enter 1, 2, or 3: ";

                // Clear the error state and discard invalid input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> credithrs[i];
            }

            cout << "Enter Grade in subject " << i + 1 << ": i.e A, A-, B+, B, B-, C+, C, C-, D, F\t";
            cin >> grade[i];

            // Validate the grade input to ensure it is valid
            try {
                if (grade[i] != "A" && grade[i] != "a" && grade[i] != "A-" && grade[i] != "a-" && grade[i] != "B+" &&
                    grade[i] != "b+" && grade[i] != "B" && grade[i] != "b" && grade[i] != "B-" && grade[i] != "b-" &&
                    grade[i] != "C+" && grade[i] != "c+" && grade[i] != "C" && grade[i] != "c" && grade[i] != "C-" &&
                    grade[i] != "c-" && grade[i] != "D+" && grade[i] != "d+" && grade[i] != "D" && grade[i] != "d" &&
                    grade[i] != "D-" && grade[i] != "d-" && grade[i] != "F" && grade[i] != "f")
                    throw " ";
            } catch (const char* ex) {
                cout << "\nError: invalid grade\n" << endl;
                i--;
            }
        }

        cout << "\n\n";
    }

    ~Student() {
        delete[] grade;
        delete[] credithrs;
    }
};

class GPACalculator : public Student {
public:
    double totcredithrs;
    double sum;
    double totpoints;
    double z;

public:
    GPACalculator() {
        totcredithrs = 0;
        sum = 0;
        totpoints = 0;
    }

    // Function to calculate GPA (Grade Point Average)
    void gpa() {
        for (int i = 0; i < subjects; i++) {
            if (grade[i] == "A" || grade[i] == "a")
                totpoints = credithrs[i] * 4.0;
            else if (grade[i] == "A-" || grade[i] == "a-")
                totpoints = credithrs[i] * 3.7;
            else if (grade[i] == "B+" || grade[i] == "b+")
                totpoints = credithrs[i] * 3.3;
            else if (grade[i] == "B" || grade[i] == "b")
                totpoints = credithrs[i] * 3.0;
            else if (grade[i] == "B-" || grade[i] == "b-")
                totpoints = credithrs[i] * 2.7;
            else if (grade[i] == "C+" || grade[i] == "c+")
                totpoints = credithrs[i] * 2.3;
            else if (grade[i] == "C" || grade[i] == "c")
                totpoints = credithrs[i] * 2.0;
            else if (grade[i] == "C-" || grade[i] == "c-")
                totpoints = credithrs[i] * 1.7;
            else if (grade[i] == "D+" || grade[i] == "d+")
                totpoints = credithrs[i] * 1.3;
            else if (grade[i] == "D" || grade[i] == "d")
                totpoints = credithrs[i] * 1.0;
            else if (grade[i] == "D-" || grade[i] == "d-")
                totpoints = credithrs[i] * 0.7;
            else
                totpoints = credithrs[i] * 0.0;

            sum += totpoints;
        }

        for (int i = 0; i < subjects; i++) {
            totcredithrs += credithrs[i];
        }

        for (int i = 0; i < subjects; i++) {
            cout << "Grade of subject " << i + 1 << " is: " << grade[i] << endl;
        }

        cout << "\nTotal Points: " << sum << "\nTotal Credit Hours: " << totcredithrs << "\n SGPA: " << (sum / totcredithrs) << endl;
        z = sum / totcredithrs;
    }

    void GPA_File(ofstream& outFile) {
        outFile<< "Welcome to your Grade Book\n";
        outFile << "GPA Results:" << endl;
        for (int i = 0; i < subjects; i++) {
            outFile << "Grade of subject " << i + 1 << " is: " << grade[i] << endl;
        }
        outFile << "Total Points: " << sum << "\nTotal Credit Hours: " << totcredithrs << "\nSGPA: " << (sum / totcredithrs) << endl;
        outFile << endl;
    }

};

class CGPACalculator : public GPACalculator {
protected:
    int numSemesters;
    GPACalculator* semesters;
    double sumall = 0;
    double totalPoints = 0;
    double totalCreditHours = 0;

public:
    CGPACalculator() {
        numSemesters = 0;
        semesters = nullptr;
    }

    // Function to get input for multiple semesters and calculate CGPA (Cumulative Grade Point Average)
    void getInput() {
        cout << "Enter number of semesters: \t";
        cin >> numSemesters;

        // Validate the input to ensure it is a positive value
        while (cin.fail() || numSemesters <= 0) {
            cout << "Error: Invalid number of semesters.\n Please enter a positive value:\n ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> numSemesters;
        }

        semesters = new GPACalculator[numSemesters];

        for (int i = 0; i < numSemesters; i++) {
            cout << "\nSemester " << i + 1 << ":\n";
            semesters[i].getinput();

            cout << "GPA for Semester " << i + 1 << ":\n";
            semesters[i].gpa();
        }

        // Calculate CGPA by summing up the total points and credit hours of all semesters
        for (int i = 0; i < numSemesters; i++) {
            totalCreditHours += semesters[i].totcredithrs;
            totalPoints += semesters[i].sum;
            sumall += semesters[i].z;
        }

        cout << "\n Total Points in all semesters:\t" << totalPoints;
        cout << "\nTotal Credit Hours in all semesters:\t" << totalCreditHours;
        cout << "\nCGPA: " << sumall / numSemesters << endl;
    }

       
    // Function to write CGPA results to file
    void CGPA_File(ofstream& outFile) {
        outFile<<"Welcome To Your Grade Book\n";
        outFile<<"CGPA Results:"<< endl;
        outFile<<"Total Points in all semesters: " << totalPoints << endl;
        outFile<<"Total Credit Hours in all semesters: " << totalCreditHours << endl;
        for(int i=0; i<numSemesters; i++){
            outFile<<"SGPA Of Semester "<<i+1<<" is: "<<semesters[i].z<<endl;
        }
        outFile << "CGPA: " << sumall / numSemesters << endl;
        outFile << endl;
    }
    

    ~CGPACalculator() {
        delete[] semesters;
    }
};

int main() {
    GPACalculator gpa;
    CGPACalculator cgpa;
    int input;
       ofstream outFile("cs_project.txt"); // Create/open the output file

    if (!outFile) {
        cout << "Error opening the file." << endl;
        return 1;
    }   // Create/open the output file

    do {
        cout << "\n------------ CGPA and GPA Calculator by MMK and Group -------------\n" << endl;
        cout << "1. Calculate GPA (Grade Point Average)" << endl;
        cout << "2. Calculate CGPA (Cumulative Grade Point Average)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice:\t ";
        cin >> input;

        // Validate the input to ensure it is a valid choice (1-3)
        while (cin.fail() || input < 1 || input > 3) {
            cout << "Error: Invalid option.\n Please enter a valid choice (1-3): \n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> input;
        }

        switch (input) {
            case 1:
                gpa.getinput();
                gpa.gpa();
              gpa.GPA_File(outFile); 
                break;
            case 2:
                cgpa.getInput();
                cgpa.CGPA_File(outFile);
                break;
            case 3:
                cout << "\nThanks for using MMK calculator\n\n" << endl;
                break;
            default:
                cout << "\nInvalid option\n" << endl;
                break;
        }
    } while (input != 3);
 
   outFile.close(); // Close the output file

    return 0;
}

