#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

class Student {
private:
    string firstName;
    string lastName;
    int rollNo;
    string course;
    string address;
    float percentage;

public:
    void input();
    void display() const;
    int getRollNo() const;
    void modify();
};

void Student::input() {
    cout << "\nEnter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    cout << "Enter Roll Number: ";
    cin >> rollNo;
    cout << "Enter Course: ";
    cin >> course;
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, address);
    cout << "Enter Percentage: ";
    cin >> percentage;
}

void Student::display() const {
    cout << left << setw(15) << firstName
         << left << setw(15) << lastName
         << left << setw(10) << rollNo
         << left << setw(15) << course
         << left << setw(20) << address
         << left << setw(10) << percentage << endl;
}

int Student::getRollNo() const {
    return rollNo;
}

void Student::modify() {
    cout << "\nModify Student Details:\n";
    cout << "Enter New First Name: ";
    cin >> firstName;
    cout << "Enter New Last Name: ";
    cin >> lastName;
    cout << "Enter New Course: ";
    cin >> course;
    cout << "Enter New Address: ";
    cin.ignore();
    getline(cin, address);
    cout << "Enter New Percentage: ";
    cin >> percentage;
}

void addStudent();
void displayAllStudents();
void searchStudent();
void modifyStudent();
void deleteStudent();
void showMenu();

int main() {
    int choice;
    do {
        showMenu();
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                modifyStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                cout << "\nExiting the program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (choice != 6);

    return 0;
}

void showMenu() {
    system("cls"); // For Windows; use "clear" for Unix/Linux
    cout << "=========================================\n";
    cout << "       Student Management System\n";
    cout << "=========================================\n";
    cout << "1. Add New Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by Roll Number\n";
    cout << "4. Modify Student Record\n";
    cout << "5. Delete Student Record\n";
    cout << "6. Exit\n";
    cout << "=========================================\n";
}

void addStudent() {
    ofstream outFile("students.dat", ios::binary | ios::app);
    Student stud;
    stud.input();
    outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
    outFile.close();
    cout << "\nStudent record added successfully.\n";
}

void displayAllStudents() {
    ifstream inFile("students.dat", ios::binary);
    Student stud;
    cout << "\nAll Student Records:\n";
    cout << left << setw(15) << "First Name"
         << left << setw(15) << "Last Name"
         << left << setw(10) << "Roll No"
         << left << setw(15) << "Course"
         << left << setw(20) << "Address"
         << left << setw(10) << "Percentage" << endl;
    cout << string(85, '-') << endl;
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        stud.display();
    }
    inFile.close();
}

void searchStudent() {
    ifstream inFile("students.dat", ios::binary);
    Student stud;
    int roll;
    bool found = false;
    cout << "\nEnter Roll Number to search: ";
    cin >> roll;
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNo() == roll) {
            cout << "\nStudent Found:\n";
            cout << left << setw(15) << "First Name"
                 << left << setw(15) << "Last Name"
                 << left << setw(10) << "Roll No"
                 << left << setw(15) << "Course"
                 << left << setw(20) << "Address"
                 << left << setw(10) << "Percentage" << endl;
            cout << string(85, '-') << endl;
            stud.display();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "\nStudent with Roll Number " << roll << " not found.\n";
    }
}

void modifyStudent() {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    Student stud;
    int roll;
    bool found = false;
    cout << "\nEnter Roll Number to modify: ";
    cin >> roll;
    while (!file.eof()) {
        streampos pos = file.tellg();
        file.read(reinterpret_cast<char*>(&stud), sizeof(Student));
        if (file && stud.getRollNo() == roll) {
            stud.modify();
            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&stud), sizeof(Student));
            cout << "\nStudent record updated successfully.\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "\nStudent with Roll Number " << roll << " not found.\n";
    }
}

void deleteStudent() {
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Student stud;
    int roll;
    bool found = false;
    cout << "\nEnter Roll Number to delete: ";
    cin >> roll;
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNo() == roll) {
            found = true;
        } else {
            outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
        }
    }
    inFile.close();
    outFile.close();
    remove("students.dat");
    rename("temp.dat", "students.dat");
    if (found) {
        cout << "\nStudent record deleted successfully.\n";
    } else {
        cout << "\nStudent with Roll Number " << roll << " not found.\n";
    }
}
