#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Student.h"
using namespace std;
namespace BrooklynPoly{
    //course constructor --> sets name = courseName
    Course::Course(const string& courseName): name(courseName){}

    ostream& operator<<(ostream& os, const Course& rhs){
        // print course name and print every student name enrolled in course
        os << rhs.name<< ": ";
        if (rhs.students.size() == 0){
            os << "No Students";
        }
        else{
            for (const Student* curr_student : rhs.students){
                os << curr_student->getName() << " ";
            }
        }
        return os;
    }

    //course name getter
    const string& Course::getName() const{
        return name;
    }

    //add student to course
    //returns false if student/course dont exist
    //returns false if student already in course
    bool Course::addStudent(Student* new_student){
        // if student does not exist, return false
        if(new_student == nullptr){return false;}
        for (const Student* const curr_stud : students){
            // if student already in course, return false
            if (curr_stud == new_student){return false;}
        }
        // if successfully add student, return true.
        students.push_back(new_student);
        return true;
    }

    //removes all students from course
    //calls removedFromCourse on student
    void Course::removeStudentsFromCourse(){
        for (size_t index=0; index < students.size(); ++index){
            (students[index])->removedFromCourse(this);
        }
        students.clear();
    }
    }
