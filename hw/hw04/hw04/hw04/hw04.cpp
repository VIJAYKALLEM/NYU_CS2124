/*
 Simran Soin (sks684)
 CS2124 HW4
 7 Oct 2019
 Classes, association, good coding
 Battling Nobles
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& rhs){
        os << rhs.name << ": " << rhs.strength;
        return os;
    }
public:
    Warrior(const string& name, int strength):
    name(name), strength(strength), hired(false), dead(false) {};
    
    bool getHired(){
        // if already hired, return false
        // else, hires warrior and returns true
        if (hired == true){return false;}
        else{
            hired = true;
            return true;
        }
    }
    
    void getFired(){hired = false;} // updates hired status
    
    int getStrength(){return strength;} // strength getter
    
    void killed(){
        // kills warrior
        dead = true;
        strength = 0;
    }
    void updateStrength(double ratio){
        // updates strength using winning ratio from battle
        strength *= (1-ratio);
    }
    
    const string& getName(){return name;} // name getter
    
private:
    string name;
    int strength;
    bool hired, dead;
};



class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs){
        os << rhs.name << " has an army of " << rhs.army.size() << endl;
        for (const Warrior* curr_warrior : rhs.army){
            os << "     " << *curr_warrior << endl;
        }
        return os;
    }
public:
    Noble(const string& name) : name(name), army_strength(0), dead(false){};
    
    int getArmyStrength(){return army_strength;} // army strength getter
    
    const string& getName(){return name;} // name getter
    
    void reduceArmyStrength(double ratio){
        // multiply each warrior's strength by (1-losing ratio)
        // recalculate total army strength
        army_strength = 0;
        for (Warrior* curr_warrior : army){
            curr_warrior->updateStrength(ratio);
            army_strength += curr_warrior->getStrength();
        }
    }
    bool hire(Warrior& new_warrior){
        // if the noble is not dead AND warrior is not already hired
        // hire warrior
        if (!dead && new_warrior.getHired()){
            // add newly hired warrior to army vector
            army.push_back(&new_warrior);
            // update total army strength
            army_strength += new_warrior.getStrength();
            return true;
        }
        //cannot hire anyone if noble is dead or warrior already hired
        return false;
    }
    
    bool fire(Warrior& fired_warrior){
        // if noble is dead, it cannot fire warriors
        if (dead){return false;}
        // else, fire the warrior
        // update the total army strength count
        fired_warrior.getFired();
        army_strength -= fired_warrior.getStrength();
        bool move_over_one = false;
        for(size_t index = 0; index<army.size(); ++index){
            // if we found the warrior to remove, set bool to true
                // move the rest of the vector over one
                // delete last item in list
            if (army[index] == &fired_warrior){
                    move_over_one = true;
            }
            // if it is last item in list:
                // either bool = true or this is the fired warrior
                // --> either way, pop it off
            if (index == (army.size()-1)){
                army.pop_back();
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
        return true;
    }
    
    void killed(){
        // noble has been killed
        // kill all the warriors
        dead = true;
        army_strength = 0;
        for (Warrior* curr_warrior : army){
            curr_warrior->killed();
        }
    }
    
    bool isDead(){return dead;};
    
    void battle(Noble& opponent){
        cout << name << " battles " << opponent.getName() << endl;
        
        // if one or both opponents is dead
        if (opponent.isDead()){
            if (dead){
                cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            }
            else{ cout << "He's dead, " << name << endl;}
        }
        
        // if both opponents are equally skilled
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
private:
    string name;
    vector<Warrior*> army;
    int army_strength; //running count of the total strength of army
    bool dead;
};


int main() {
    
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    
    art.fire(cheetah);
    cout << art << endl;
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    
}


