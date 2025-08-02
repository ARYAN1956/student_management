# 📘 Student Management System
-A console-based Student Management System built in C++ that allows you to add, view, search, modify, and delete student records stored in a binary file.

# Features
 1.Add New Student
 2.Display All Students
 3.Search Student by Roll Number
 4.Modify Existing Student Details
 5.Delete Student Record
 6.Data is stored in a binary file (students.dat)

# 🛠️ Technologies Used
-Language: C++
-File Handling: Binary files
-OOP Concepts: Classes, encapsulation
-Console I/O: iostream, fstream, iomanip

# How to Run
Compile the code:
g++ main.cpp -o student_mgmt

# Run the executable:
./student_mgmt   # For Linux/Mac
student_mgmt.exe # For Windows

# 📌 How It Works
-On startup, the main menu is displayed.
-Select options 1-6 to perform operations.
-Student records are written/read in binary format from students.dat.

# 🚫 Limitations
-No input validation (e.g., invalid percentage or roll number).
-Not portable across systems unless compiled accordingly.
-Only runs in console, no GUI.

# 📄 License
-This project is open-source and available for educational and non-commercial use.
