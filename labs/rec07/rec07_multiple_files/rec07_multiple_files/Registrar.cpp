#include <iostream>
#include <string>
#include <vector>
#include "Registrar.h"
#include "Course.h"
#include "Student.h"
using namespace std;
namespace BrooklynPoly{

    Registrar::Registrar(){};

    //prints registrars report followed by all existing courses and all existing students
    ostream& operator<<(ostream& os, const Registrar& rhs){
        os << "Registrar's Report" << endl;
        os << "Courses:" << endl;
        for (const Course* curr_course: rhs.courses){
            os << *curr_course << endl;
        }
        os << "Students:" << endl;
        for (const Student* curr_student: rhs.students){
            os << *curr_student << endl;
        }
        return os;
    }

    //finds index of student pointer in students vector
    // returns -1 if student not found
    size_t Registrar::findStudent(const string& studentName) const{
        for (size_t index=0; index< students.size(); ++index){
            const Student* const curr_stud = students[index];
            if (curr_stud->getName() == studentName){
                return index;
            }
        }
        return students.size();
    }

    //finds index of course pointer in courses vector
    // returns -1 if course not found
    size_t Registrar::findCourse(const string& courseName) const{
        for (size_t index=0; index< courses.size(); ++index){
            const Course* const curr_course = courses[index];
            if (curr_course->getName() == courseName){
                return index;
            }
        }
        return courses.size();
    }

    //creates course on heap and adds pointer to vector
    //returns false if course already exists with this name
    bool Registrar::addCourse(const string& courseName){
        if (findCourse(courseName) == courses.size()){
            Course* new_course = new Course(courseName);
            courses.push_back(new_course);
            return true;
        }
        return false; // course with this name already exists
    }

    //creates student on heap and adds pointer to vector
    //returns false if student already exists with this name
    bool Registrar::addStudent(const string& studentName){
        if (findStudent(studentName) == students.size()){
            Student* new_stud = new Student(studentName);
            students.push_back(new_stud);
            return true;
        }
        return false; // student with this name already exists
    }

    //enrolls student in course. returns false if course/student do not exist
    bool Registrar::enrollStudentInCourse(const string& studentName,
                               const string& courseName){
        size_t student_index = findStudent(studentName);
        size_t course_index = findCourse(courseName);
        //if student or course with given names do not exist, return false.
        if (course_index == courses.size()|| student_index == students.size()){return false;}
        students[student_index]->addCourse(courses[course_index]);
        courses[course_index]->addStudent(students[student_index]);
        return true;
    }

    //removes course from heap, removes course from vector, removes students from course
    bool Registrar::cancelCourse(const string& course_name){
        size_t course_index = findCourse(course_name);
        if (course_index == courses.size()){return false;} //course does not exist, return false
        if (course_index != courses.size()-1){
            // if course is not last item in courses vector, swap places with last item
            Course* temp = courses[courses.size()-1];
            courses[courses.size()-1] = courses[course_index];
            courses[course_index] = temp;
        }
        courses[course_index]->removeStudentsFromCourse(); //remove students from course
        //delete course from heap
        delete courses[course_index];
        //delete course from vector
        courses.pop_back();
        return true;
    }

    //delete all students/courses from vector AND heap
    void Registrar::purge(){
        for (size_t index=0; index<courses.size(); ++index){
            cancelCourse(courses[index]->getName());
        }
        for (size_t index=0; index<students.size(); ++index){
            delete students[index];
        }
        students.clear();
    }
}
