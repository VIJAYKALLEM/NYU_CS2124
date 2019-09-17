/*
 Simran Soin
 CS2124 HW02 
 Battling warriors and keeping track of their respective strengths
 Functions, structs, vectors and file I/O
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Warrior {
    // each warrior has a name and starting strength level
    string name;
    int strength;
};

void openFileAndLoop(vector<Warrior>& all_warriors);
void createAndAddWarrior(const string name, int strength, vector<Warrior>& all_warriors);
void displayStatus(const vector<Warrior>& all_warriors); // outputs name, strength of all warriors in vector
size_t getWarriorIndexFromName(const vector<Warrior>& all_warriors, const string& name);
void warriorsBattle(vector<Warrior>& all_warriors, size_t instigator_index, size_t opponent_index);



int main() {
    // creates empty warrior vector and calls fxn to open file
    vector<Warrior> all_warriors;
    openFileAndLoop(all_warriors);
}




void createAndAddWarrior(const string name, int strength,
                         vector<Warrior>& all_warriors){
    // creates a new warrior with given name and strength
    // adds warrior to existing vector of warriors
    Warrior new_warrior{name, strength};
    all_warriors.push_back(new_warrior);
}

void displayStatus(const vector<Warrior>& all_warriors){
    cout << "There are: " << all_warriors.size() << " warriors" << endl;
    // loops through warriors in vectors and outputs the name, strength to console
    for (Warrior curr_warrior : all_warriors){
        cout << "Warrior: " << curr_warrior.name <<
        ", strength: " << curr_warrior.strength << endl;
    }
}

size_t getWarriorIndexFromName(const vector<Warrior>& all_warriors,
                               const string& name){
    // given the name of the warrior, loops through the vector of all warriors
    // returns the index of the warrior within the vector
    for (size_t i=0; i<all_warriors.size(); ++i){
        if (all_warriors[i].name == name){
            return i;
        }
    }
    // in case the name is not found, prints "warrior name not found" and returns 0.
    cout << "Warrior name not found " << name << endl;
    return 0;
}

void warriorsBattle(vector<Warrior>& all_warriors, size_t instigator_index,
                    size_t opponent_index){
    // instigator is just an easier way to refer to all_warriors[instigator_index]
        // subtrating from instigator strength doesnt subtract all_warriors[instigator_index].strength
        // therefore the vector, indexes are still needed
    // (same thing for opponent and all_warriors[opponent_index])
    
    Warrior instigator = all_warriors[instigator_index];
    Warrior opponent = all_warriors[opponent_index];
    cout << instigator.name << " battles " << opponent.name << endl;

    if (opponent.strength == 0){
        if(instigator.strength == 0){
            // opponent strength is 0 AND instigator strength is 0
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        // only opponent is dead
        else {cout << "He's dead, " << instigator.name << endl;}
    }
    
    else if (opponent.strength == instigator.strength){
        // if equal strength, both die (strengths = 0)
        // mutual annihilation
        all_warriors[opponent_index].strength = 0;
        all_warriors[instigator_index].strength = 0;
        cout << "Mutual Annihilation: " << instigator.name << " and  " << opponent.name
        << " die at each other's hands" << endl;
    }
    else {
        // if we are here, it means that both strengths are different and non-zeroes
        // larger strength = larger strength - smaller strength
        // smaller strength = 0
        // print that smaller strengthed warrior is now defeated
        
        if (opponent.strength < instigator.strength){
            all_warriors[instigator_index].strength -= all_warriors[opponent_index].strength;
            all_warriors[opponent_index].strength = 0;
            cout << instigator.name << " defeats " << opponent.name << endl;
        }
        else{
            all_warriors[opponent_index].strength -=  all_warriors[instigator_index].strength;
            all_warriors[instigator_index].strength = 0;
            cout << opponent.name << " defeats " << instigator.name << endl;
        }
        
    }
}

void openFileAndLoop(vector<Warrior>& all_warriors){
    // opens file stream
    // loops through file
    // based on the first word(commmand):
        // reads the next necessary pieces of information
        // calls the corresponding function
    ifstream file("warriors.txt");
    string command;
    while (file >> command){
        if (command == "Warrior"){
            string name;
            int strength;
            file >> name >> strength;
            createAndAddWarrior(name, strength, all_warriors);
        }
        else if (command == "Status"){
            displayStatus(all_warriors);
        }
        else if (command == "Battle"){
            string instigator_name, opponent_name;
            file >> instigator_name >> opponent_name;
            
            size_t instigator_index =
            getWarriorIndexFromName(all_warriors, instigator_name);
            
            size_t opponent_index =
            getWarriorIndexFromName(all_warriors, opponent_name);
            warriorsBattle(all_warriors, instigator_index, opponent_index);
        }
    }
}
