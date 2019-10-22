/*
  Simran Soin
  rec07
  Separate compilation, namespaces, forward declaration
  Transaction processing program for Registrar
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string&);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};


class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string&);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string&);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
  




//COURSE METHODS




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
    students.clear()
}





//STUDENT METHODS




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






//REGISTRAR METHODS





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
