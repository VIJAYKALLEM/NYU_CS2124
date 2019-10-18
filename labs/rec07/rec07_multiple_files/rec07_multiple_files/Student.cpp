#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
#include "Course.h"
using namespace std;

namespace BrooklynPoly{

    //prints student name followed by all courses the student enrolled in
    ostream& operator<<(ostream& os, const Student& rhs){
        os << rhs.name <<": ";
        if (rhs.courses.size() == 0){
            os << "No Courses";
        }
        else{
            for (const Course* const curr_course: rhs.courses){
                os << curr_course->getName() << " ";
            }
        }
        return os;
    }

    //student constructor --> sets name = name
    Student::Student(const string& name): name(name){}

    //remove course from vector of courses
    void Student::removedFromCourse(Course* course_to_delete){
        //loop through courses vector until course to delete is found
        for (size_t index=0; index<courses.size(); ++ index){
            if (courses[index] == course_to_delete){
                if (course_to_delete != courses[courses.size()-1]){
                    //if the course is not the last course in the vector:
                        //swap positions with last course in the vector
                    Course* temp = courses[courses.size()-1];
                    courses[courses.size()-1] = courses[index];
                    courses[index] = temp;
                }
                //delete course from vector and break loop
                courses.pop_back();
                break;
            }
        }
    }

    //add course to vector of courses
    //returns false if students already enrolled in course
    bool Student::addCourse(Course* new_course){
        for (const Course* const curr_course : courses){
            if (curr_course == new_course){
                return false;
            }
        }
        courses.push_back(new_course);
        return true;
    }

    //student name getter
    const string& Student::getName() const{
        return name;
    }
    }
