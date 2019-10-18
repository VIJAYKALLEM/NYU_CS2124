/*
  Simran Soin
  rec07
  Separate compilation, namespaces, forward declaration
  Transaction processing program for Registrar
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Student.h"
#include "Course.h"
#include "Registrar.h"

using namespace std;
using namespace BrooklynPoly;

int main() {
    ifstream file("registrar_input.txt");
    string command;
    Registrar registrar;
    while (file >> command){
        if (command == "PrintReport"){
            cout << registrar << endl;
        }
        else if (command == "AddCourse"){
            string course_name;
            file >> course_name;
            registrar.addCourse(course_name);
        }
        
        else if (command == "AddStudent"){
            string student_name;
            file >> student_name;
            registrar.addStudent(student_name);
        }
        else if (command == "EnrollStudentInCourse"){
            string student_name;
            string course_name;
            file >> student_name >> course_name;
            registrar.enrollStudentInCourse(student_name, course_name);
        }
        else if (command == "CancelCourse"){
            string course_name;
            file >> course_name;
            registrar.cancelCourse(course_name);
        }
        
        else if (command == "Purge"){
            registrar.purge();
        }
    }
}
