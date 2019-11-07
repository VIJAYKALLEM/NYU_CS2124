#include <iostream>
#include <string>
#include "Noble.h"
#include "Warrior.h"

using namespace std;
namespace WarriorCraft{
    ostream& operator<<(ostream& os, const Noble& rhs){
           os << rhs.name << " has an army of " << rhs.army_size << endl;
           for (size_t index=0; index<rhs.army_size; ++index){
               os << "     " << *((rhs.army)[index]) << endl;
           }
           return os;
       }

    //regular constructor
    Noble::Noble(const string& name): name(name), army(new Warrior*[1]), army_size(0), army_capacity(1), army_strength(0), dead(false) {};
    //copy constructor
    Noble::Noble(const Noble& rhs): name(rhs.name), army(new Warrior*[rhs.army_capacity]), army_size(rhs.army_size), army_capacity(rhs.army_capacity), army_strength(rhs.army_strength), dead(rhs.dead) {
        for (size_t index = 0; index<rhs.army_size; ++index){
            army[index] = new Warrior(*rhs.army[index]);
        }
    };
    //assignment operator
    Noble& Noble::operator=(const Noble& rhs){
        if (this!= &rhs){
            for (size_t index=0; index<army_size; ++index){
                delete army[index];
            }
            delete [] army;
            army_size = rhs.army_size;
            army_capacity = rhs.army_capacity;
            army = new Warrior*[rhs.army_capacity];
            for (size_t index=0; index<rhs.army_size; ++index){
                army[index] = new Warrior(*rhs.army[index]);
            }
        }
        return *this;
    };
    //destructor
    Noble::~Noble(){
        for (size_t index=0; index<army_size; ++index){
        cout << army[index]->getName() << endl;
            delete army[index];
        }
        delete [] army;
    };

    const int Noble::getArmyStrength() const{
        //army strength getter
        return army_strength;
    }

    bool Noble::warriorInArmy(Warrior*& warrior) const{
        //returns true if the given warrior is in this noble's army
        for (size_t index=0; index<army_size; ++index){
            if (army[index]->getName() == warrior->getName()){
                return true;
            }
        }
        return false;
    }
    void Noble::reduceArmyStrength(double ratio){
        // multiply each warrior's strength by (1-losing ratio)
        // recalculate total army strength
        army_strength = 0;
        for (size_t index=0; index<army_size; ++index){
            army[index]->updateStrength(ratio);
            army_strength += army[index]->getStrength();
        }
    }

     bool Noble::hire(Warrior& new_warrior){
         // if the noble dead or warrior is already hired
         // return false
         // else, hire warrior
        if (dead || !new_warrior.getHired(this)){
            return false;
        }
         // resize array if necessary
        if (army_size == army_capacity){
             army_capacity *= 2;
             Warrior** new_army = new Warrior*[army_capacity];
             for (size_t old_index = 0; old_index < army_size; ++ old_index){
                 new_army[old_index] = army[old_index];
             }
             delete [] army;
             army = new_army;
         }
         //add warrior to array
         //modify army size and strength accordingly
         army[army_size] = &new_warrior;
         army_size += 1;
         army_strength += new_warrior.getStrength();
         return true;
     }

    bool Noble::fire(Warrior& fired_warrior){
        // fires given warrior
            //tells warrior it is not hired anymore
            //reduces army size and strength accordingly
        
        //if this noble is dead, it cannot fire the warrior, return false
        if (dead){ return false; }
        fired_warrior.getFired();
        army_size -= 1;
        army_strength -= fired_warrior.getStrength();
        
        //moves over warriors in array
            //(to make sure fired warrior is no longer within size)
        bool move_over_one = false;
        for (size_t index = 0; index< army_size; ++index){
            // if we found the warrior to remove, set bool to true
                // move the rest of the vector over one
                // delete last item in list
            if (army[index] == &fired_warrior){
                    move_over_one = true;
            }
            // if it is last item in list:
                    // either bool = true or this is the fired warrior
                    // --> either way, pop it off
                if (index == (army_size-1)){
                    break;
                }
                // if not last item: check if bool is true
                    // if so, set army index equal to the next index
                else if (move_over_one == true){
                    army[index] = army[index+1];
                }
            }
        cout << "You don't work for me anymore ";
        cout << fired_warrior.getName() << "! -- " << name << endl;
        //returns true if successfully fired the warrior
        return true;
    }

    void Noble::killed(){
           // called if noble has been killed
            // --> loops through and kills all the warriors
           dead = true;
           army_strength = 0;
           for (size_t index = 0; index< army_size; ++index){
               army[index]->killed();
           }
       }
        
    bool Noble::isDead() const {return dead;}; //returns true if noble is dead

    const string& Noble::getName() const { return name;} //name getter
    void Noble::battle(Noble& opponent){
        //called when this noble instigates battle on another
        
        cout << name << " battles " << opponent.getName() << endl;
        
        // if one or both opponents is dead, battle cannot occur
        if (opponent.isDead()){
            if (dead){
                cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            }
            else{ cout << "He's dead, " << name << endl;}
        }
        
        // if both opponents are equally strong, mutual annihilation
        else if(opponent.getArmyStrength() == army_strength){
            killed();
            opponent.killed();
            cout << "Mutual Annihalation: " << name << " and ";
            cout << opponent.getName() << "die at each other's hands" << endl;
        }
        
        
        // opponent defeats self
        else if (opponent.getArmyStrength() > army_strength){
            double losing_ratio = (double(army_strength) /
                                   double(opponent.getArmyStrength()));
            opponent.reduceArmyStrength(losing_ratio);
            killed();
            cout << opponent.getName() << " defeats " << name << endl;
        }
        
        
        // self defeats opponent
        else if (opponent.getArmyStrength() < army_strength){
            double losing_ratio = (double(opponent.getArmyStrength()) /
                                   double(army_strength));
            reduceArmyStrength(losing_ratio);
            opponent.killed();
            cout << name << " defeats " << opponent.getName() << endl;
        }
    }
    
    void Noble::warriorRanAway(Warrior& runaway){
        army_size -= 1;
        army_strength -= runaway.getStrength();
        
        //moves over warriors in array
            //(to make sure fired warrior is no longer within size)
        bool move_over_one = false;
        for (size_t index = 0; index< army_size; ++index){
            // if we found the warrior to remove, set bool to true
                // move the rest of the vector over one
                // delete last item in list
            if (army[index] == &runaway){
                    move_over_one = true;
            }
            // if it is last item in list:
                    // either bool = true or this is the fired warrior
                    // --> either way, pop it off
                if (index == (army_size-1)){
                    break;
                }
                // if not last item: check if bool is true
                    // if so, set army index equal to the next index
                else if (move_over_one == true){
                    army[index] = army[index+1];
                }
            }
    }
}
