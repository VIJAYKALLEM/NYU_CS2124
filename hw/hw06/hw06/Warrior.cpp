#include <iostream>
#include <string>
#include "Warrior.h"
using namespace std;
namespace WarriorCraft{
    ostream& operator<<(ostream& os, const Warrior& rhs){
        os << rhs.name << ": " << rhs.strength;
        return os;
    }
            
    Warrior::Warrior(const string& name, int strength):
    name(name), strength(strength), boss(nullptr), dead(false) {};
            
    bool Warrior::getHired(Noble* new_boss){
        // if already hired, return false
        // else, hires warrior and returns true
        if (boss != nullptr){return false;}
        else{
            boss = new_boss;
            return true;
        }
    }

    void Warrior::getFired(){boss = nullptr;} // updates hired status

    int Warrior::getStrength() const{return strength;} // strength getter
       
    void Warrior::killed(){
        // kills warrior
        dead = true;
        strength = 0;
    }
    void Warrior::updateStrength(double ratio){
        // updates strength using winning ratio from battle
        strength *= (1-ratio);
    }
       
    const string& Warrior::getName() const{return name;} // name getter
    const bool Warrior::unemployed() const {
        //returns true if warrior is unemployed
        return (boss==nullptr);
        
    }
    
    void Warrior::runaway(){
        boss->warriorRanAway(*this);
        cout << name << " flees in terror, abandoning his lord, " << boss->getName() << endl;
        boss = nullptr;
    }
}
