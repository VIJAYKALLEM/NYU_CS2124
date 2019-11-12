#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace WarriorCraft{
    Noble::Noble(const std::string& name): name(name) {};
    void Noble::battle(Noble& opponent){
        //called when this noble instigates battle on another
        cout << getName() << " battles " << opponent.getName() << endl;
        // if both opponents is dead, battle cannot occur
        if (opponent.isDead() && dead){
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            return;
        }
        // if one of opponents is dead, battle cannot occur
        else if (opponent.isDead()){
            printBattleCrysIfNecessary();
            cout << "He's dead, " << getName() << endl;
            return;
        }
        else if (isDead()){
            opponent.printBattleCrysIfNecessary();
            cout << "He's dead, " << opponent.getName() << endl;
            return;
        }
        // if self object wins battle
            // print self battle crys (if self object is a lord)
            // print defeating statement
            // calculate winning ratio and update strength accordingly
            // kill opponent
        if (this->getStrength() > opponent.getStrength()){
            printBattleCrysIfNecessary();
            opponent.printBattleCrysIfNecessary();
            cout << getName() << " defeats " << opponent.getName() << endl;
            double winning_ratio = opponent.getStrength() / getStrength();
            updateStrength(winning_ratio);
            opponent.die();
            return;
        }
        // Mutual annihilation
            // kill both self and opponent
        else if(this->getStrength() == opponent.getStrength()){
            cout << "Mutual Annihalation: " << getName() << " and ";
            cout << opponent.getName() << "die at each other's hands" << endl;
            return;
        }
        // Opponent wins battle
            // print self battle crys (if self object is a lord)
            // print defeating statement
            // calculate winning ration and update opponent strength accordingly
            // kill self.
        else{
            printBattleCrysIfNecessary();
            opponent.printBattleCrysIfNecessary();
            cout << opponent.getName() << " defeats " << getName() << endl;
            double winning_ratio = getStrength() / opponent.getStrength();
            opponent.updateStrength(winning_ratio);
            die();
        }
    }
    
    // sets dead status
    void Noble::die(){
        dead = true;
    }

    // returns dead status
    bool Noble::isDead() const{
        return dead;
    }
    
    // returns const name reference
    const string& Noble::getName() const{
        return name;
    }

    
    Lord::Lord(const std::string& name): Noble(name) {};

    bool Lord::hires(Protector& new_protector) {
        // updates the Protector's boss, army vector, army strength total
        if (!new_protector.isDead() && !isDead() && new_protector.hire(this)){
            army.push_back(&new_protector);
            army_strength += new_protector.getStrength();
            return true;
        }
        return false;
    }

    void Lord::fires(Protector& fired_protector){
        // updates the Protector's boss, army vector, army strength total
        fired_protector.getFired();
        army_strength -= fired_protector.getStrength();
        // required to keep order of army vector
            // any index >= fired protector index must be set to the following index
            // delete the last index
        bool move_over = false;
        for (size_t index=0; index<army.size(); ++index){
            if (index == (army.size()-1)){
                army.pop_back();
                return;
            }
            if (army[index] == &fired_protector){
                move_over = true;
            }
            if (move_over){
                army[index] = army[index+1];
            }
        }
    }

    void Lord::warriorRanAway(const Protector* const former_protec){
        for (size_t i = 0; i < army.size(); ++i){
            if (army[i] == former_protec){
                Protector* temp = army[army.size()-1];
                army[army.size()-1] = army[i];
                army[i] = temp;
                army.pop_back();
                return;
            }
        }
    }

    int Lord::getStrength() const{
        // strength getter
        return army_strength;
    }

    // print battle crys of all protectors
    void Lord::printBattleCrysIfNecessary() const{
        for (Protector* curr_protector : army){
            curr_protector->printDefendingYell();
        }
    }

    // update strengths of all protectors and recalculate army_strength
    void Lord::updateStrength(double ratio){
        army_strength = 0;
        for (Protector* curr_protector : army){
            curr_protector->loseStrength(ratio);
            army_strength += curr_protector->getStrength();
        }
    }

    // kill all protectors, set army_strength to 0, set dead status to true
            // calls Noble::die() to set dead status (bool in base class)
    void Lord::die(){
        for (Protector* curr_protector : army){
            curr_protector->die();
        }
        army_strength = 0;
        Noble::die();
    }

    PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string& name, int strength): Noble(name), strength(strength) {};

    // strength getter
    int PersonWithStrengthToFight::getStrength() const{
        return strength;
    }

    void PersonWithStrengthToFight::printBattleCrysIfNecessary() const{
        cout << "Ugh!"<< endl;
    }

    // sets strength to 0 and dead status to true (calls base class to set dead status)
    void PersonWithStrengthToFight::die(){
        strength = 0;
        Noble::die();
    }

    // updates strength using winning ratio
    void PersonWithStrengthToFight::updateStrength(double ratio){
        strength *= (1-ratio);
    }

}
