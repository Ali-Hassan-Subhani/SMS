#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits> // For numeric_limits
using namespace std;

class Course {
private:
    string courseName;
    int creditHours;

public:
    Course(string name, int credits) : courseName(name), creditHours(credits) {}

    string getCourseName() const {
        return courseName;
    }

    int getCreditHours() const {
        return creditHours;
    }
};

class Student {
private:
    string name;
    string rollNo;
    string dob;
    string email;
    string program;
    string semester;
    vector<Course> courses;
    int totalCreditHours; // To track total credit hours for the student

public:
    Student(string n, string r, string d, string e, string p, string s)
        : name(n), rollNo(r), dob(d), email(e), program(p), semester(s), totalCreditHours(0) {}

    string getRollNo() const {
        return rollNo;
    }

    string getSemester() const {
        return semester;
    }

    int getTotalCreditHours() const {
        return totalCreditHours;
    }

    bool addCourse(const Course& course) {
        if (totalCreditHours + course.getCreditHours() <= 18) {
            courses.push_back(course);
            totalCreditHours += course.getCreditHours();
            return true;
        } else {
            cout << "Cannot add course \"" << course.getCourseName()
                 << "\". Adding it would exceed the 18-credit-hour limit.\n";
            return false;
        }
    }

    void displayCourses() const {
        if (courses.empty()) {
            cout << "No courses enrolled.\n";
        } else {
            cout << "Enrolled Courses:\n";
            for (const auto& course : courses) {
                cout << "- " << course.getCourseName() << " (" << course.getCreditHours() << " credit hours)\n";
            }
        }
        cout << "Total Credit Hours Selected: " << totalCreditHours << "/18\n";
    }

    void display() const {
        cout << "Name: " << name << "\nRoll Number: " << rollNo
             << "\nDOB: " << dob << "\nEmail: " << email
             << "\nProgram: " << program << "\nSemester: " << semester
             << "\nCourses: ";
        displayCourses();
        cout << endl;
    }
};

class SMS {
private:
    vector<Student> studentList;
    map<int, vector<Course>> semesterCourses;

public:
    SMS() {
        // Initialize semester courses with credit hours
        semesterCourses[1] = {Course("AIN111-Introduction To ICT(3+1)", 4),
                              Course("AIN101-Applied Physics(3+1)", 4),
                              Course("AIN102-Calculus And Analytical Geometry(3)", 3),
                              Course("HMT121-Islamic Studies(2)", 2),
                              Course("HUM111-Functional English(3)", 3),
                              Course("ASC100-Pre-Calculus I (Pre-Medical only)(3)", 3)};

        semesterCourses[2] = {Course("HUM112-Personal Development(3)", 3),
                              Course("AIN131-Programming Fundamentals(3+1)", 4),
                              Course("HUM231-Communication Skills(3)", 3),
                              Course("AIN103-Linear Algebra and Differential Equations(3)", 3),
                              Course("HS103-Pak Studies(2)", 2),
                              Course("ASC101-Pre - Calculus II (Pre-Medical only)(3)", 3)};

        semesterCourses[3] = {Course("AIN231-Object Oriented Programming(3+1)", 4),
                              Course("AIN221-Operating Systems(3+1)", 4),
                              Course("AIN201-Probability & Statistics(3)", 3),
                              Course("AIN241-Discrete Structures(3)", 3),
                              Course("AIN202-Multivariate Calculus(3)", 3)};

        semesterCourses[4] = {Course("AIN232-Data Structure and Algorithms(3+1)", 4),
                              Course("AIN342-Design and Analysis Of Algorithms(3)", 3),
                              Course("SSC231 -World History (3)", 3),
                              Course("AN351-Software Engineering(3)", 3),
                              Course("AIN203-Applied Statistics(3)", 3)};
    }

    void displayEligibleCourses(int currentSemester) const {
        cout << "Eligible Courses:\n";
        for (int sem = 1; sem <= currentSemester + 1; ++sem) {
            if (semesterCourses.count(sem)) {
                cout << "\nSemester " << sem << ":\n";
                for (size_t i = 0; i < semesterCourses.at(sem).size(); ++i) {
                    const auto& course = semesterCourses.at(sem)[i];
                    cout << i + 1 << ". " << course.getCourseName() << " (" << course.getCreditHours() << " credit hours)\n";
                }
            }
        }
    }

    void enrollInCourses(Student& student, int currentSemester) {
        displayEligibleCourses(currentSemester);

        vector<Course> allEligibleCourses;
        for (int sem = 1; sem <= currentSemester + 1; ++sem) {
            if (semesterCourses.count(sem)) {
                allEligibleCourses.insert(allEligibleCourses.end(),
                                          semesterCourses.at(sem).begin(),
                                          semesterCourses.at(sem).end());
                                          //cout<<'ali';
            }
        }

        int numSubjects;
        while (true) {
            cout << "\nEnter how many subjects to enroll (1-5): ";
            cin >> numSubjects;

            if (cin.fail() || numSubjects < 1 || numSubjects > 5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number between 1 and 5.\n";
            } else {
                break;
            }
        }

        for (int i = 1; i <= numSubjects; ++i) {
            int choice;
            while (true) {
                cout << "Select subject " << i << " (enter number, 0 to finish): ";
                cin >> choice;

                if (cin.fail() || choice < 0 || choice > allEligibleCourses.size()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please select a valid course number.\n";
                } else if (choice == 0) {
                    return;
                } else {
                    if (student.addCourse(allEligibleCourses[choice - 1])) {
                        cout << "Course added successfully!\n";
                        
                        break;
                    } else {
                        cout << "Cannot add this course due to credit hour limits.\n";
                    }
                }
            }
        }
    }

    void addStudent(Student& student) {
        studentList.push_back(student);
        cout << "Student added successfully!\n";
    }

    void deleteStudentByRollNo(const string& rollNo) {
        for (auto it = studentList.begin(); it != studentList.end(); ++it) {
            if (it->getRollNo() == rollNo) {
                studentList.erase(it);
                cout << "Student deleted successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void searchStudentByRollNo(const string& rollNo) const {
        for (const auto& student : studentList) {
            if (student.getRollNo() == rollNo) {
                student.display();
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void displayAllStudents() const {
        if (studentList.empty()) {
            cout << "No students found!\n";
            return;
        }
        for (const auto& student : studentList) {
            student.display();
            cout << "---------------------\n";
        }
    }
};

int main() {
    SMS system;
    string name, rollNo, dob, email;
    int semester, choice;

    do {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Search Student\n";
        cout << "4. Display All Students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number.\n";
            continue;
        }

        if (choice == 1) {
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Roll Number: ";
            getline(cin, rollNo);
            cout << "Enter DOB: ";
            getline(cin, dob);
            cout << "Enter Email: ";
            getline(cin, email);
            cout << "Enter Current Semester (1-8): ";
            cin >> semester;

            Student newStudent(name, rollNo, dob, email, "Computer Science", to_string(semester));
            system.enrollInCourses(newStudent, semester);
            system.addStudent(newStudent);
        } else if (choice == 2) {
            cout << "Enter Roll Number to delete: ";
            cin >> rollNo;
            system.deleteStudentByRollNo(rollNo);
        } else if (choice == 3) {
            cout << "Enter Roll Number to search: ";
            cin >> rollNo;
            system.searchStudentByRollNo(rollNo);
        } else if (choice == 4) {
            system.displayAllStudents();
        } else if (choice == 5) {
            cout << "Exiting program...\n";
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}