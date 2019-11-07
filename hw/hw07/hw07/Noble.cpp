#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace WarriorCraft{
    Noble::Noble(const std::string& name): name(name) {};
    void Noble::battle(Noble& opponent){
        cout << getName() << " battles " << opponent.getName() << endl;
        if (opponent.isDead() && dead){
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            return;
        }
        else if (opponent.isDead() || dead){
            cout << "He's dead, ";
            if (dead){ cout << opponent.getName();}
            else {cout << name;}
            cout << endl;
            return;
        }
        if (this->getStrength() > opponent.getStrength()){
            printBattleCrysIfNecessary();
            cout << getName() << " defeats " << opponent.getName() << endl;
            double winning_ratio = opponent.getStrength() / getStrength();
            updateStrength(winning_ratio);
            opponent.die();
        }
        else if(this->getStrength() == opponent.getStrength()){
            cout << "Mutual Annihalation: " << getName() << " and ";
            cout << opponent.getName() << "die at each other's hands" << endl;        }
        else{
            printBattleCrysIfNecessary();
            cout << opponent.getName() << " defeats " << getName() << endl;
            double winning_ratio = getStrength() / opponent.getStrength();
            opponent.updateStrength(winning_ratio);
            die();
        }
    }
    void Noble::die(){
        dead = true;
    }

    void Noble::printBattleCrysIfNecessary(){}

    bool Noble::isDead() const{
        return dead;
    }

    const string& Noble::getName() const{
        return name;
    }
    Lord::Lord(const std::string& name): Noble(name) {};
    bool Lord::hires(Protector& new_protector) {
        if (!new_protector.isDead() && new_protector.hire(this)){
            army.push_back(&new_protector);
            army_strength += new_protector.getStrength();
            return true;
        }
        return false;
    }

    int Lord::getStrength() const{
        return army_strength;
    }

    void Lord::printBattleCrysIfNecessary(){
        for (Protector* curr_protector : army){
            curr_protector->printDefendingYell();
        }
    }

    void Lord::updateStrength(double ratio){
        for (Protector* curr_protector : army){
            curr_protector->loseStrength(ratio);
        }
    }

    void Lord::die(){
        for (Protector* curr_protector : army){
            curr_protector->die();
        }
        Noble::die();
    }

    PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string& name, int strength): Noble(name), strength(strength) {};

    int PersonWithStrengthToFight::getStrength() const{
        return strength;
    }

    void PersonWithStrengthToFight::die(){
        strength = 0;
        Noble::die();
    }
    void PersonWithStrengthToFight::updateStrength(double ratio){
        strength *= (1-ratio);
    }

}
