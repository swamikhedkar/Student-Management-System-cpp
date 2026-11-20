
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Student class
class Student {

public:
    int id;
    string name;
    int age;
    float marks;

    // Display student details
    void display() {

        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nMarks: " << marks << endl;
    }
};

// Global student vector
vector<Student> students;


// Save students to file
void saveStudents() {

    ofstream file("students.txt");

    if (!file) {
        cout << "\nError saving student records!\n";
        return;
    }

    for (int i = 0; i < students.size(); i++) {

        file << students[i].id << "|"
             << students[i].name << "|"
             << students[i].age << "|"
             << students[i].marks << endl;
    }

    file.close();
}


// Load students from file
void loadStudents() {

    ifstream file("students.txt");

    if (!file) {
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        Student s;
        string id, age, marks;

        if (getline(ss, id, '|') &&
            getline(ss, s.name, '|') &&
            getline(ss, age, '|') &&
            getline(ss, marks)) {

            try {
                s.id = stoi(id);
                s.age = stoi(age);
                s.marks = stof(marks);

                students.push_back(s);
            }
            catch (...) {
                cout << "\nSkipping invalid record.\n";
            }
        }
    }

    file.close();
}


// 1. Add Student
void addStudent() {

    Student s;

    cout << "\nEnter Student ID: ";
    cin >> s.id;

    // Check duplicate ID
    for (int i = 0; i < students.size(); i++) {

        if (students[i].id == s.id) {
            cout << "\nStudent ID already exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    getline(cin >> ws, s.name);

    cout << "Enter Age: ";
    cin >> s.age;

    cout << "Enter Marks: ";
    cin >> s.marks;

    if (s.age <= 0 || s.marks < 0 || s.marks > 100) {
        cout << "\nInvalid age or marks!\n";
        return;
    }

    students.push_back(s);

    saveStudents();

    cout << "\nStudent Added Successfully!\n";
}


// 2. Display Students
void displayStudents() {

    if (students.empty()) {

        cout << "\nNo Student Records Found!\n";
        return;
    }

    cout << "\n===== STUDENT RECORDS =====\n";

    for (int i = 0; i < students.size(); i++) {

        cout << "\nStudent " << i + 1;

        students[i].display();
    }
}


// 3. Search Student
void searchStudent() {

    int searchID;

    cout << "\nEnter Student ID: ";
    cin >> searchID;

    bool found = false;

    for (int i = 0; i < students.size(); i++) {

        if (students[i].id == searchID) {

            cout << "\nStudent Found!\n";

            students[i].display();

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}


// 4. Update Student
void updateStudent() {

    int searchID;

    cout << "\nEnter Student ID to Update: ";
    cin >> searchID;

    bool found = false;

    for (int i = 0; i < students.size(); i++) {

        if (students[i].id == searchID) {

            cout << "\nCurrent Student Details:";
            students[i].display();

            cout << "\nEnter New Name: ";
            getline(cin >> ws, students[i].name);

            cout << "Enter New Age: ";
            cin >> students[i].age;

            cout << "Enter New Marks: ";
            cin >> students[i].marks;

            if (students[i].age <= 0 ||
                students[i].marks < 0 ||
                students[i].marks > 100) {

                cout << "\nInvalid details! Update cancelled.\n";
                return;
            }

            saveStudents();

            cout << "\nStudent Updated Successfully!\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}


// 5. Delete Student
void deleteStudent() {

    int deleteID;

    cout << "\nEnter Student ID to Delete: ";
    cin >> deleteID;

    bool found = false;

    for (int i = 0; i < students.size(); i++) {

        if (students[i].id == deleteID) {

            students.erase(students.begin() + i);

            saveStudents();

            cout << "\nStudent Deleted Successfully!\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}


// 6. Calculate Grade
void calculateGrade() {

    int searchID;

    cout << "\nEnter Student ID: ";
    cin >> searchID;

    bool found = false;

    for (int i = 0; i < students.size(); i++) {

        if (students[i].id == searchID) {

            float marks = students[i].marks;

            cout << "\nStudent Name: " << students[i].name;
            cout << "\nMarks: " << marks;

            if (marks >= 90) {
                cout << "\nGrade: A+";
            }
            else if (marks >= 80) {
                cout << "\nGrade: A";
            }
            else if (marks >= 70) {
                cout << "\nGrade: B";
            }
            else if (marks >= 60) {
                cout << "\nGrade: C";
            }
            else if (marks >= 40) {
                cout << "\nGrade: D";
            }
            else {
                cout << "\nGrade: Fail";
            }

            cout << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}


// Main Function
int main() {

    int choice;

    // Load records when program starts
    loadStudents();

    cout << "\nStudent Records Loaded: "
         << students.size() << endl;

    do {

        cout << "\n\n================================";
        cout << "\n    STUDENT MANAGEMENT SYSTEM";
        cout << "\n================================";

        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Calculate Grade";
        cout << "\n7. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                calculateGrade();
                break;

            case 7:
                cout << "\nThank You for Using the System!";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 7);

    return 0;
}