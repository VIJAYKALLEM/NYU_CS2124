#include "Instrument.h"
#include "Musician.h"
#include <string>
#include <vector>
#ifndef Orch_h
#define Orch_h
namespace Music{
    class Orch{
    public:
        void addPlayer( Musician& new_player);
        void play() const;
    private:
        std::vector<Musician*> orchestra;
    };
}
#endif /* Orch_h */
