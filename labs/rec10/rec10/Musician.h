#ifndef Musician_h
#define Musician_h
#include "Instrument.h"
#include <string>
#include <vector>
namespace Music{

    class Musician {
    public:
        Musician();
        void acceptInstr(Instrument* instPtr);
        Instrument* giveBackInstr();
        void testPlay() const;
        void actualPlay() const;
    private:
        Instrument* instr;
    };
}
#endif /* Musician_h */
