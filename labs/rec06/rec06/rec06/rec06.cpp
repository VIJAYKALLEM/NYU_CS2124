/*
  Simran Soin
  Recitation 06
  CS2124
  Representation of a directory of employees
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& rhs){
        os << "Directory size is: " << rhs.size << endl;
        for (size_t index=0; index<rhs.size; ++index){
            cout << "    " << *((rhs.entries)[index]) << endl;
        }
        
        return os;
    }
public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    Directory(): size(0), capacity(1), entries(new Entry*[1]){
        cout << "* * * *" << endl;
        cout << "regular constructor being called" << endl;
        cout << "* * * *" << endl;
    };
    
    Directory(const Directory& rhs): size(rhs.size), capacity(rhs.capacity),
    entries(new Entry*[rhs.capacity]){
        cout << "* * * *" << endl;
        cout << "copy constructor being called" << endl;
        cout << "* * * *" << endl;
        for (size_t rhs_index = 0; rhs_index < rhs.size; ++rhs_index){
            entries[rhs_index] = new Entry(*rhs.entries[rhs_index]);
        }
    };
    
    Directory& operator=(const Directory& rhs){
        cout << "* * * *" << endl;
        cout << "assignment operator being called" << endl;
        cout << "* * * *" << endl;
        if (this != &rhs){
            for (size_t index = 0; index < size; ++index){
                delete entries[index];
            }
            delete [] entries;
            
            size = rhs.size;
            capacity = rhs.capacity;
            entries = new Entry*[rhs.capacity];
            for (size_t rhs_index = 0; rhs_index < rhs.size; ++rhs_index){
                entries[rhs_index] = new Entry(*rhs.entries[rhs_index]);
            }
        }
        return *this;
    };

    ~Directory(){
        cout << "* * * *" << endl;
        cout << "destructor being called" << endl;
        cout << "* * * *" << endl;
        for (size_t index = 0; index < size; ++index){
            delete entries[index];
        }
        delete [] entries;
    };
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)    {
            capacity *= 2;
            Entry** new_entries = new Entry*[capacity];
            for (size_t old_index = 0; old_index < size; ++old_index){
                new_entries[old_index] = entries[old_index];
            }
            delete[] entries;
            entries = new_entries;
            cout << "* * * *" << endl;
            cout << "RESIZED" <<endl;
            cout << "* * * *" << endl;
            // something is missing!!!  Add it!

        } // if
        Entry new_entry = Entry(name, room, ph, pos);
        entries[size] = new Entry(new_entry);
        ++size;
    } // add
    
    const unsigned operator[](const string& name) const{
        for (size_t index=0; index<size; ++index){
            if((*entries[index]).getName() == name){
                return (entries[index])->getPhone();
            }
        }
        return (*entries)->getPhone();
    }

private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;    // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;
    cout << d3 << endl;

    // Should display 1592
    cout << d2["Carmack"] << endl;
    
} // main

