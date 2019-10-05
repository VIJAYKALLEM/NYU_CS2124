/*
 Simran Soin (sks684)
 4 October 2019
 Recitation 5: Design interacting classes using
        Association
        Composition
        Encapsulation and Data Hiding
        Delegation
        Copy control: destructor and copy constructor.
        Output operator
 
 Modeling the NYU Tandon CS lab Administration
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int NUM_GRADES = 14;

class Section{
    // OSTREAM << OPERATOR FOR SECTION
    friend ostream& operator<<(ostream& os, const Section& rhs){
        os << "Section: " << rhs.name << ", " << rhs.section_time << ", Students: " <<endl;
        if (rhs.student_records.size() == 0){
            os << "None";
        }
        else{
            for (const Student* curr_student: rhs.student_records){
                os << *curr_student;
            }
        }
        return os;
    }
public:
    // CONSTRUCTOR
    Section(const string& name, const string& day, int start_time): name(name),
    section_time(TimeSlot(start_time, day)) {};
    
    // COPY CONSTRUCTOR
    Section(const Section& rhs) : section_time(rhs.section_time), name(rhs.name) {
        vector<Student*> lhs_student_records;
        for (const Student* curr_student: rhs.student_records){
            Student* deep_copied_student_pointer = new Student(*curr_student);
            lhs_student_records.push_back(deep_copied_student_pointer);
        }
        student_records = lhs_student_records;
    };
    
    // DESTRUCTOR
    ~Section(){
        cout << "Section " << name << " is being deleted" << endl;
        for (Student*& curr_student: student_records){
            cout << "Deleting " << curr_student->getNameCopy() << endl;
            delete curr_student;
            curr_student = nullptr;
        }
        student_records.clear();
    };
    
    // CREATES STUDENT FROM NAME AND ADDS POINTER TO STUDENT_RECORDS
    void addStudent(const string& name){
        Student* curr_student = new Student(name);
        student_records.push_back(curr_student);
    }
    
    // FINDS NAME IN STUDENT RECORDS
    // TELLS STUDENT TO ADD A CERTAIN GRADE TO A CERTAIN WEEK
    void addGrade(const string& name, int grade, int week){
        for (Student*& curr_student: student_records){
            if (curr_student->getNameCopy() == name){
                curr_student->addGrade(grade, week);
                break;
            }
        }
    }
private:
    // STUDENT IS EMBEDDED IN SECTION
    class Student{
        // OSTREAM << OPERATOR FOR STUDENT
        friend ostream& operator<<(ostream& os,
                                   const Student& rhs){
            os << "Name: " << rhs.name << ", Grades: ";
            for (size_t i = 0; i <= NUM_GRADES; ++i){
                os << rhs.student_grades[i] << ", ";
            }
            os << endl;
            return os;
        }
    public:
        // CONSTRUCTOR (INTIALIZES ALL GRADES TO -1)
        Student(const string& name): name(name) {
            student_grades = vector<int>(NUM_GRADES, -1);
        };
        
        // GIVEN GRADE AND WEEK, ADDS TO GRADE VECTOR
        void addGrade(int grade, int week){
            student_grades[week-1] = grade;
        }
        
        // CONST FUNCTION RETURNS COPY OF NAME
        string getNameCopy() const{
            return name;
        }
    private:
        string name;
        vector<int> student_grades;
    };
    
    //TIMESLOT IS EMBEDDED IN SECTION
    class TimeSlot{
        // OSTREAM << OPERATOR FOR TIMESLOT
        friend ostream& operator<<(ostream& os, const TimeSlot& rhs){
            os << "Time slot: [Day: " << rhs.day <<", Start Time: ";
            if (rhs.start_time <= 11){
                os << rhs.start_time << "am";
            }
            else if (rhs.start_time == 12){
                os << rhs.start_time << "pm";
            }
            else {
                os << (rhs.start_time - 12) << "pm";
            }
            os << "]";
            return os;
        }
    public:
        // CONSTRUCTOR
        TimeSlot(int start_time, const string& day): start_time(start_time), day(day) {};
    private:
        // HAS STRING DAY AND INT TIME (24 HR)
        int start_time;
        string day;
    };
    
    string name;
    TimeSlot section_time;
    // SECTION HAS A VECTOR OF STUDENT POINTERS (POINTS TO HEAP)
    vector<Student*> student_records;
};


class LabWorker{
    // OSTREAM << OPERATOR FOR LABWORKER
    friend ostream& operator<<(ostream& os, const LabWorker& rhs){
        os << rhs.name;
        if (rhs.assigned_section == nullptr){
            os << " does not have a section.";
        }
        else{
            os << " has " << *rhs.assigned_section;
        }
        return os;
    }
public:
    // CONSTRUCTOR
    LabWorker(const string& name): name(name), assigned_section(nullptr){};
    
    // ASSIGNS AN EXISTING SECTION TO LABWORKER
    void addSection(Section& section_name){
        assigned_section = &section_name;
    }
    
    // ADDING A GRADE --> DELEGATES TO THE SECTION
    void addGrade(const string& student_name, int grade, int week){
        assigned_section->addGrade(student_name, grade, week);
    }
private:
    string name;
    // POINTER TO A SECTION.
    // IF POINTER IS NULL, LABWORKER HASNT BEEN ASSIGNED SECTIOM
    Section* assigned_section;
};






// Test code
void doNothing(Section sec) {
    cout << sec << endl;;
}

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
