#include "Instrument.h"
#include "Orch.h"
#include "MILL.h"
#include "Musician.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
namespace Music{
    void Orch::addPlayer(Musician& new_player){
        orchestra.push_back(&new_player);
    }
    void Orch::play() const{
        for (Musician* curr_player : orchestra){
            curr_player->actualPlay();
        }
        cout << endl;
    }
}
