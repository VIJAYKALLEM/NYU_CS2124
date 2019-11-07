#include "Protector.h"
#include "Noble.h"
#include <iostream>
#include <string>
using namespace std;
    namespace WarriorCraft{
    Protector::Protector(const string& name, int strength) : name(name), strength(strength), boss(nullptr), dead(false) {};

    const string& Protector::getName() const{
        return name;
    }
    const Lord* const Protector::getBoss() const{
        return boss;
    }

    bool Protector::hire(Lord* new_boss){
        if (boss == nullptr && !dead){
            boss = new_boss;
            return true;
        }
        return false;
    }
    
    void Protector::getFired(){
        boss = nullptr;
    }

    bool Protector::isDead() const{
        return dead;
    }

    int Protector::getStrength() const{
        return strength;
    }

    void Protector::loseStrength(double ratio){
        strength *= (1-ratio);
    }
    
    void Protector::die(){
        strength = 0;
        dead = true;
    }

    Archer::Archer(const string& name, int strength) : Protector(name, strength) {};

    void Archer::printDefendingYell() const{
        cout << "TWANG! " << getName() << " says: Take that in the name of my lord, " << getBoss()->getName() << endl;
    }
    Wizard::Wizard(const string& name, int strength): Protector(name, strength) {};
    void Wizard::printDefendingYell() const{
        cout << "POOF!" << endl;
    }

    Swordsman::Swordsman(const string& name, int strength): Protector(name, strength) {};
    void Swordsman::printDefendingYell() const{
        cout << "CLANG! " << getName() << " says: Take that in the name of my lord, " << getBoss()->getName() << endl;
    }
}
