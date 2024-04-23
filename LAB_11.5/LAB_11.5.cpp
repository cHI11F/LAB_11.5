#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Student {
    string surname;
    double averageGrade;
    double scholarship;
};

struct Teacher {
    string surname;
    string position;
    double salary;
    string discipline;
    vector<Student> students;
};

void addTeacher(vector<Teacher>& teachers) {
    Teacher teacher;
    cout << "Enter teacher's surname: ";
    getline(cin, teacher.surname);
    cout << "Enter teacher's position: ";
    getline(cin, teacher.position);
    cout << "Enter teacher's salary: ";
    cin >> teacher.salary;
    cin.ignore(); // Clearing input buffer
    cout << "Enter the discipline taught by this teacher: ";
    getline(cin, teacher.discipline);
    teachers.push_back(teacher);
}

void addStudentToTeacher(vector<Teacher>& teachers) {
    if (teachers.empty()) {
        cout << "No teachers available. Please add a teacher first." << endl;
        return;
    }

    string discipline;
    cout << "Enter the discipline for the student: ";
    getline(cin, discipline);

    auto it = find_if(teachers.begin(), teachers.end(), [&discipline](const Teacher& teacher) {
        return teacher.discipline == discipline;
        });

    if (it == teachers.end()) {
        cout << "No teacher found for the given discipline." << endl;
        return;
    }

    Student student;
    cout << "Enter student's surname: ";
    getline(cin, student.surname);
    cout << "Enter student's average grade: ";
    cin >> student.averageGrade;
    cout << "Enter student's scholarship: ";
    cin >> student.scholarship;
    cin.ignore(); // Clearing input buffer

    it->students.push_back(student);
}

void saveData(const string& filePath, const vector<Teacher>& teachers) {
    ofstream file(filePath, ios::binary);
    if (!file.is_open()) {
        cout << "Failed to open file for writing." << endl;
        return;
    }

    for (const auto& teacher : teachers) {
        file.write((char*)&teacher, sizeof(Teacher));
    }

    file.close();
    cout << "Data saved successfully." << endl;
}

void loadData(const string& filePath, vector<Teacher>& teachers) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        cout << "Failed to open file for reading." << endl;
        return;
    }

    Teacher teacher;
    while (file.read((char*)&teacher, sizeof(Teacher))) {
        teachers.push_back(teacher);
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}

void displayTeachers(const vector<Teacher>& teachers) {
    cout << "Teachers:\n";
    for (const auto& teacher : teachers) {
        cout << "Surname: " << teacher.surname << ", Position: " << teacher.position << ", Salary: " << teacher.salary << endl;
        cout << "Discipline: " << teacher.discipline << endl;
        cout << "Students: ";
        for (const auto& student : teacher.students) {
            cout << student.surname << ", ";
        }
        cout << endl;
    }
}

void filterTeachersByAverageGrade(const vector<Teacher>& teachers, double maxAverageGrade) {
    cout << "Teachers and disciplines with average grades less than " << maxAverageGrade << ":" << endl;
    for (const auto& teacher : teachers) {
        double totalAverageGrade = 0.0;
        for (const auto& student : teacher.students) {
            totalAverageGrade += student.averageGrade;
        }
        double averageGrade = totalAverageGrade / teacher.students.size();
        if (averageGrade < maxAverageGrade) {
            cout << "Teacher: " << teacher.surname << ", Discipline: " << teacher.discipline << endl;
        }
    }
}

void removeLowGradedStudents(vector<Teacher>& teachers) {
    for (auto& teacher : teachers) {
        teacher.students.erase(remove_if(teacher.students.begin(), teacher.students.end(), [](const Student& student) {
            return student.averageGrade < 3.0;
            }), teacher.students.end());
    }
    cout << "Low graded students removed." << endl;
}

double calculateScholarshipFund(const vector<Teacher>& teachers, const string& discipline) {
    double fund = 0.0;
    for (const auto& teacher : teachers) {
        if (teacher.discipline == discipline) {
            for (const auto& student : teacher.students) {
                fund += student.scholarship;
            }
        }
    }
    return fund;
}

int main() {
    string filePath;
    cout << "Enter the file path to save/load the data: ";
    getline(cin, filePath);

    vector<Teacher> teachers;

    loadData(filePath, teachers);

    while (true) {
        // Displaying menu
        cout << "\nMenu:\n";
        cout << "1. Add teacher\n";
        cout << "2. Add student to teacher\n";
        cout << "3. Save data to file\n";
        cout << "4. Display teachers\n";
        cout << "5. Filter teachers by average grade\n";
        cout << "6. Remove low graded students\n";
        cout << "7. Calculate scholarship fund for a specific discipline\n";
        cout << "8. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clearing input buffer

        switch (choice) {
        case 1:
            addTeacher(teachers);
            break;
        case 2:
            addStudentToTeacher(teachers);
            break;
        case 3:
            saveData(filePath, teachers);
            break;
        case 4:
            displayTeachers(teachers);
            break;
        case 5:
        {
            double maxAverageGrade;
            cout << "Enter the maximum average grade: ";
            cin >> maxAverageGrade;
            cin.ignore(); // Clearing input buffer
            filterTeachersByAverageGrade(teachers, maxAverageGrade);
            break;
        }
        case 6:
            removeLowGradedStudents(teachers);
            break;
        case 7:
        {
            string discipline;
            cout << "Enter the discipline: ";
            getline(cin, discipline);
            cout << "Scholarship fund for discipline " << discipline << ": " << fixed << setprecision(2) << calculateScholarshipFund(teachers, discipline) << endl;
            break;
        }
        case 8:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 8.\n";
        }
    }

    return 0;
}
