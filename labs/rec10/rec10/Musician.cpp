#include "Instrument.h"
#include "Musician.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
namespace Music{
    Musician::Musician() : instr(nullptr) {}

    void Musician::acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* Musician::giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void Musician::testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }

    void Musician::actualPlay() const {
        if (instr) {instr->play();}
    }
}
