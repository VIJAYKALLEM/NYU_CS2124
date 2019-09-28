/*
 Simran Soin
 CS2124 HW03
 Battling warriors and keeping track of their respective strengths
 Data Hiding, Encapsulation, Delegation, Operator Overloading
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
    Warrior(string name, string weapon_name, int strength): name(name), weapon(Weapon(weapon_name, strength)){}
    const string& getName()const{
        return name;
    }
    const int& getStrength() const{
        const int retval = weapon.getStrength();
        return retval;
    }
    void setStrength(int new_strength){
        weapon.setStrength(new_strength);
    }
private:
    class Weapon{
        friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);
        friend int getStrength(const Warrior& warrior);
    public:
        Weapon(string name, int strength): name(name), strength(strength) {};
        const int getStrength() const{
            return strength;
        }
        void setStrength(int new_strength){
            strength = new_strength;
        }
    private:
        string name;
        int strength;
    };
    string name;
    Weapon weapon;
    friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);
};

ostream& operator<<(ostream& os, const Warrior::Weapon& weapon){
    os << "weapon: "<< weapon.name << ", " << weapon.strength;
    return os;
}

ostream& operator<<(ostream& os, const Warrior& warrior){
    os << "Warrior: " << warrior.name << ", weapon: " << warrior.weapon;
    return os;
}

// PROTOTYPES
void battleDifferentStrengths(Warrior& smaller, Warrior& bigger);
void findIndexesFromNames(const vector<Warrior>& all_warriors, const string& instigator_name,
                          const string& opponent_name, size_t& inst_index, size_t& opp_index);
void warriorsBattle(vector<Warrior>& all_warriors, size_t instigator_index,
                    size_t opponent_index);
void openFileAndLoop(vector<Warrior>& all_warriors);

//MAIN
int main(){
    vector<Warrior> all_warriors;
    openFileAndLoop(all_warriors);
}


// Battle Scenario where there are two warriors of different strengths
    // to avoid rewriting code in warriorsBattle() depending on which is smaller
    // smaller/bigger = Warrior of smaller/bigger strength weapon
void battleDifferentStrengths(Warrior& smaller, Warrior& bigger){
    bigger.setStrength(bigger.getStrength() - smaller.getStrength());
    smaller.setStrength(0);
    cout << bigger.getName() << " defeats " << smaller.getName() << endl;
}


// Given warrior names, finds their indexes in all_warriors vector
void findIndexesFromNames(const vector<Warrior>& all_warriors, const string& instigator_name,
                          const string& opponent_name, size_t& inst_index, size_t& opp_index){
    inst_index = opp_index = -1;
    for (size_t index = 0; index<all_warriors.size(); ++index){
        if (all_warriors[index].getName() == instigator_name){
            inst_index = index;
        }
        else if (all_warriors[index].getName() == opponent_name){
            opp_index = index;
        }
        if (inst_index != -1 && opp_index != -1){
            // if neither variable == -1, then both have been assigned
            // we can stop looping
            break;
        }
    }
}


// Battles two warriors
void warriorsBattle(vector<Warrior>& all_warriors, size_t instigator_index,
                size_t opponent_index){
Warrior& instigator = all_warriors[instigator_index];
Warrior& opponent = all_warriors[opponent_index];

    if (opponent.getStrength() == 0){
        // case where one or both of the warriors is dead
        if(instigator.getStrength() == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else {cout << "He's dead, " << instigator.getName() << endl;}
    }
    
    else if (opponent.getStrength() == instigator.getStrength()){
        // case where both get killed by each other
        opponent.setStrength(0);
        instigator.setStrength(0);
        cout << "Mutual Annihilation: " << instigator.getName() << " and  " << opponent.getName()
        << " die at each other's hands" << endl;
    }
    else {
        // case where one is larger than the other (calls function to handle)
        if (opponent.getStrength() < instigator.getStrength()){
            battleDifferentStrengths(opponent, instigator);
        }
        else{battleDifferentStrengths(instigator, opponent);}
    }
}


void openFileAndLoop(vector<Warrior>& all_warriors){
    ifstream file("warriors.txt");
    string command;
    while (file >> command){
        if (command == "Warrior"){
            // creates a new warrior and adds it to the all_warriors vector
            
            string name, weapon_name;
            int strength;
            file >> name >> weapon_name >> strength;
            all_warriors.push_back(Warrior(name, weapon_name, strength));
        }
        else if (command == "Status"){
            // prints number of total existing warriors
            // prints each warrior name, weapon, weapon strength
            
            cout << "There are: " << all_warriors.size() << " warriors" << endl;
            for (const Warrior& curr_warrior : all_warriors){
                cout << curr_warrior << endl;
            }
        }
        else if (command == "Battle"){
            // finds warriors in vector based off of names
            // subtracts from strengths and prints to console accordingly
            
            string instigator_name, opponent_name;
            size_t instigator_index, opponent_index;
            file >> instigator_name >> opponent_name;
            findIndexesFromNames(all_warriors, instigator_name,
                                 opponent_name, instigator_index, opponent_index);
            cout << instigator_name << " battles " << opponent_name << endl;
            warriorsBattle(all_warriors, instigator_index, opponent_index);
            
        }
    }
}
