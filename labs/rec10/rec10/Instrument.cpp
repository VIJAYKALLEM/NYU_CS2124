#include "Instrument.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
namespace Music{
    void Instrument::makeSound() const{
        cout << "To make a sound...";
    }
    Brass::Brass(unsigned mouthpiece_size): mouthpiece_size(mouthpiece_size) {};
    void Brass::makeSound() const{
        Instrument::makeSound();
        cout << " blow on a mouthpiece of size " << mouthpiece_size << endl;
    }

    String::String(unsigned pitch): pitch(pitch) {};

    void String::makeSound() const{
        Instrument::makeSound();
        cout << " bow a string with pitch " << pitch << endl;
    }

    void Percussion::makeSound() const{
        Instrument::makeSound();
        cout << " hit me!" << endl;
    }
    void Trumpet::play() const {
        cout <<"Toot";
    }
    void Trombone::play() const{
        cout <<"Blat";
    }
    void Violin::play() const{
        cout <<"Screech";
    }
    void Cello::play() const{
        cout <<"Squawk";
    }
    void Drum::play() const{
        cout <<"Boom";
    }
    void Cymbal::play() const{
        cout <<"Crash";
    }
}
