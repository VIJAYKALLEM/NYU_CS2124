#include <iostream>
#include <string>
#include <vector>
using namespace std;

class School;
class Instructor{
public:
    Instructor(const string& name);
    const string& getName() const;
    void getEmployed(School* boss);
private:
    string name;
    School* employer;
};

class School{
    friend ostream& operator<<(ostream& os, const School& rhs);
public:
    School(const string& name);
    School(const School& rhs): name(rhs.name){
        for (Instructor* inst : rhs.instructors){
            instructors.push_back(new Instructor(*inst));
        }
    }
    ~School(){
        for (Instructor* inst : instructors){
            delete inst;
            inst = nullptr;
        }
        instructors.clear();
    }
    const School& operator=(const School& rhs);
    Instructor* operator[](const string& inst_name) const;
    void hire(Instructor* employee);
    void removeEmp(Instructor* fired_employee){
        for (size_t index = 0; index<instructors.size(); ++index){
            if (instructors[index] == fired_employee){
                instructors.erase (instructors.begin()+index);
                return;
            }
        }
    }
private:
    string name;
    vector<Instructor*> instructors;
};

Instructor::Instructor(const string& name): name(name), employer(nullptr) {}
const string& Instructor::getName() const{
    return name;
}
void Instructor::getEmployed(School* boss){
    if (employer != nullptr) employer->removeEmp(this);
    employer = boss;
}

ostream& operator<<(ostream& os, const School& rhs){
    os << "School: " << rhs.name << "; Instructors:";
    for (const Instructor* inst: rhs.instructors){
        os << " " << inst->getName();
    }
    os << ".";
    return os;
}

School::School(const string& name) : name(name) {}

const School& School::operator=(const School& rhs){
    if (this != &rhs){
        for (const Instructor* inst : instructors){
            delete inst;
            inst = nullptr;
        }
        for (const Instructor* inst : rhs.instructors){
            instructors.push_back(new Instructor(*inst));
        }
    }
    name = rhs.name;
    return *this;
}

Instructor* School::operator[](const string& inst_name) const{
    for (Instructor* inst: instructors){
        if (inst->getName() == inst_name){
            return inst;
        }
    }
    return nullptr;
}

void School::hire(Instructor* employee){
    employee->getEmployed(this);
    instructors.push_back(employee);
}
int main() {
    School nyu("NYU");
    School poly("Poly");
    poly.hire(new Instructor("Gallagher"));
    Instructor* sterling = new Instructor("Sterling");
    poly.hire(sterling);
    cout << poly << endl;
    Instructor* gallagherPtr = poly["Gallagher"];
    nyu.hire(gallagherPtr);
    cout << poly << endl;
    cout << nyu << endl;
}
