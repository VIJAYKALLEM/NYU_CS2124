#include "Instrument.h"
#include "MILL.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
namespace Music{
    void MILL::receiveInstr(Instrument& new_instr){
        for (size_t index = 0; index<instruments.size(); ++index){
            if(instruments[index] == nullptr){
                instruments[index] = &new_instr;
                return;
            }
        }
        instruments.push_back(&new_instr);
        return;
    }

    void MILL::dailyTestPlay(){
        for (size_t index = 0; index<instruments.size(); ++index){
            if(instruments[index] != nullptr){
                instruments[index]->makeSound();
            }
        }
    }

    Instrument* MILL::loanOut(){
        for (size_t index = 0; index<instruments.size(); ++index){
            if(instruments[index] != nullptr){
                Instrument* retval = instruments[index];
                instruments[index] = nullptr;
                return retval;
            }
        }
        return nullptr;
    }
}
