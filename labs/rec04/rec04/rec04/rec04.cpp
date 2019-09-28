#include <iostream>
#include <climits>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class SpeakerSystem {
   public:
   void vibrateSpeakerCones(unsigned signal) const {

      cout << "Playing: " << signal << "Hz sound..." << endl;
      cout << "Buzz, buzzy, buzzer, bzap!!!\n";
   }
};

class Amplifier {
public:
  void attachSpeakers(const SpeakerSystem& spkrs)
   {
      if(attachedSpeakers)
         cout << "already have speakers attached!\n";
      else
         attachedSpeakers = &spkrs;
   }
  
   void detachSpeakers() { // should there be an "error" message if not attached?
      attachedSpeakers = nullptr;
   }
  
   void playMusic( ) const {
      if (attachedSpeakers)
         attachedSpeakers -> vibrateSpeakerCones(440);
      else
         cout << "No speakers attached\n";
   }
private:
   const SpeakerSystem* attachedSpeakers = nullptr;
};



/*
 int x;
 x = 10;
 cout << "x = " << x << endl;
 
 int* p;
 p = &x;
 cout << "p = " << p << endl;
 
 int* p;     // it's very clear that the * is part of the type's name - the type is "pointer to int"
             // PREFERRED
 int *p;     // it looks the * is part of the variable name but the compiler reads it as above
 int * p;    // it looks more like multiplication but the compiler again reads it as above
             // (probably NOT a good idea to use)
 int* p1, p2, *p3;   // This is compile-able code but's it's VERY unclear as the type of p2.
                     // Since the * is part of the type's name, it's clear that p1 is an int*; and it's pretty clear that
                     //  p3 is an int* but notice that it looks like p2 is also an int* - but it's not!
                     // (definitely NOT a good idea to mix int and int* definitions
 
 cout << "p = " << p << endl;
 

 cout << "p points to where " << *p << " is stored\n";
 cout << "*p contains " << *p << endl;
 
 *p = -2763;
 cout << "p points to where " << *p << " is      stored\n";
 cout << "*p now contains " << *p << endl;
 cout << "x now contains " << x << endl;
 
 int y(13);
 cout << "y contains " << y << endl;
 p = &y;
 cout << "p now points to where " << *p << " is stored\n";
 cout << "*p now contains " << *p << endl;
 *p = 980;
 cout << "p points to where " << *p << " is stored\n";
 cout << "*p now contains " << *p << endl;
 cout << "y now contains " << y << endl;
 
 int* q;
 q = p;
 cout << "q points to where " << *q << " is stored\n";
 cout << "*q contains " << *q << endl;
 
 double d(33.44);
 double* pD(&d);
 *pD = *p;
 *pD = 73.2343;
 *p  = *pD;
 *q  = *p;
 pD  = p;
 p   = pD;
 
 int joe = 24;
 const int sal = 19;
 int*  pI;
 pI = &joe;
 *pI = 234;
 //  pI = &sal;
 // *pI = 7623;

 const int* pcI;
 pcI = &joe;
 // *pcI = 234;
 pcI = &sal;
 // *pcI = 7623;

 int* const cpI;
 int* const cpI(&joe);
 //int* const cpI(&sal);
 //  cpI = &joe;
 *cpI = 234;
 //  cpI = &sal;
 *cpI = 7623;

 const int* const cpcI;
 //const int* const cpcI(&joe);
 //const int* const cpcI(&sal);
 //  cpcI = &joe;  // *cpcI = 234;
 //  cpcI = &sal;
 // *cpcI = 7623;
 
 struct Complex {
    double real;
    double img;
 };
 
 Complex c = {11.23,45.67};
 Complex* pC(&c);
 
// cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;
 cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;
 
 class PlainOldClass {
 public:
    PlainOldClass() : x(-72) {}
    int getX() const { return x; }
    void setX( int val )  { x = val; }
 private:
    int x;
 };

 PlainOldClass poc;
 PlainOldClass* ppoc( &poc );
 cout << ppoc->getX() << endl;
 ppoc->setX( 2837 );
 cout << ppoc->getX() << endl;
 
 class PlainOldClassV2 {
 public:
    PlainOldClassV2() : x(-72) {}
    int getX() const { return x; }
    void setX( int x )  { x = x; } // HMMMM???
 private:
    int x;
 };
 
 vector<Complex*> complV; // can hold pointers to Complex objects
 Complex* tmpPCmplx;      // space for a Complex pointer
 for (size_t ndx = 0; ndx < 3; ++ndx) {
    tmpPCmplx = new Complex; // create a new Complex object on the heap
    tmpPCmplx->real = ndx;   // set real and img to be the
    tmpPCmplx->img  = ndx;   // value of the current ndx
    complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
 }
 // display the objects using the pointers stored in the vector
 for (size_t ndx = 0; ndx < 3; ++ndx) {
     cout << complV[ ndx ]->real << endl;
     cout << complV[ ndx ]->img  << endl;
 }
 // release the heap space pointed at by the pointers in the vector
 for (size_t ndx = 0; ndx < 3; ++ndx) {
     delete complV[ndx];
 }
 // clear the vector
 complV.clear();

 class Colour {
 public:
     Colour(const string& name, unsigned r, unsigned g, unsigned b)
         : name(name), r(r), g(g), b(b) {}
     void display() const {
         cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
     }
 private:
     string name;      // what we call this colour
     unsigned r, g, b; // red/green/blue values for displaying
 };

 vector<Colour*> colours;
 string inputName;
 unsigned inputR, inputG, inputB;

 // fill vector with Colours from the file
 // this could be from an actual file but here we are using the keyboard instead of a file
 // (so we don't have to create an actual file)
 // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
 // somehow the while's test has to fail - from keyboard input
 while (cin >> inputName >> inputR >> inputG >> inputB) {
     colours.push_back(
     Colour* color = new Colour(inputName, inputR, inputG, inputB));
 }

 // display all the Colours in the vector:
 for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
     colours[ndx]->display();
     cout << endl;
 }
 
 
const SpeakerSystem spkstm1;
const SpeakerSystem spkstm2;
const SpeakerSystem spkstm3;
Amplifier amp;
amp.attachSpeakers(spkstm1);
amp.playMusic();

*/





class Person {
public:
    Person(const string& name) : name(name), roomie(nullptr) {}
    bool movesInWith(Person& newRoomate) {
        if (newRoomate.roomie == nullptr && roomie == nullptr){
            roomie = &newRoomate;        // now I have a new roomie
            newRoomate.roomie = this;    // and now they do too
            return true;
        }
        return false;
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const bool getRoomiesName(string& roomie_name) const {
        if(roomie != nullptr){
            roomie_name = roomie->getName();
            return true;
        }
        else{
            return false;
        }
    }
private:
    Person* roomie;
    string name;
};


int main(int argc, const char * argv[]) {
    
    Person joeBob("Joe Bob"), billyJane("Billy Jane");
    joeBob.movesInWith(billyJane);

    // did this work out?
    string joeBob_roomie_name;
    string billyJane_roomie_name;
    joeBob.getRoomiesName(joeBob_roomie_name);
    billyJane.getRoomiesName(billyJane_roomie_name);
    cout << joeBob.getName() << " lives with " << joeBob_roomie_name << endl;
    cout << billyJane.getName() << " lives with " << billyJane_roomie_name << endl;
    return 0;
}
