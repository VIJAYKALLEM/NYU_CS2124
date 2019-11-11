#ifndef MILL_h
#define MILL_h
#include "Instrument.h"
#include <string>
#include <vector>
namespace Music{
    class MILL{
    public:
        void receiveInstr(Instrument& new_instr);
        void dailyTestPlay();
        Instrument* loanOut();
    private:
        std::vector<Instrument*> instruments;
    };
}
#endif /* MILL_h */
