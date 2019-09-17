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
void displayStatus(const vector<Warrior>& all_warriors);
size_t getWarriorIndexFromName(const vector<Warrior>& all_warriors, const string& name);
void warriorsBattle(vector<Warrior>& all_warriors, size_t instigator_index, size_t opponent_index);

int main() {
    vector<Warrior> all_warriors;
    openFileAndLoop(all_warriors);
}

void createAndAddWarrior(const string name, int strength, vector<Warrior>& all_warriors){
    Warrior new_warrior{name, strength};
    all_warriors.push_back(new_warrior);
}

void displayStatus(const vector<Warrior>& all_warriors){
    cout << "There are: " << all_warriors.size() << " warriors" << endl;
    for (Warrior curr_warrior : all_warriors){
        cout << "Warrior: " << curr_warrior.name << ", strength: " << curr_warrior.strength << endl;
    }
}

size_t getWarriorIndexFromName(const vector<Warrior>& all_warriors, const string& name){
    for (size_t i=0; i<all_warriors.size(); ++i){
        if (all_warriors[i].name == name){
            return i;
        }
    }
    // in case the name is not found, return 0.
    return 0;
}

void warriorsBattle(vector<Warrior>& all_warriors, size_t instigator_index, size_t opponent_index){
    Warrior instigator = all_warriors[instigator_index];
    Warrior opponent = all_warriors[opponent_index];
    cout << instigator.name << " battles " << opponent.name << endl;
    //cout << instigator.strength << " battles " << opponent.strength << endl;

    if (opponent.strength == 0){
        if(instigator.strength == 0){cout << "Oh, NO! They're both dead! Yuck!" << endl;}
        else {cout << "He's dead, " << instigator.name << endl;}
    }
    
    else if (opponent.strength == instigator.strength){
        all_warriors[opponent_index].strength = 0;
        all_warriors[instigator_index].strength = 0;
        cout << "Mutual Annihilation: " << instigator.name << " and  " << opponent.name << " die at each other's hands" << endl;
    }
    else {
        if (opponent.strength < instigator.strength){
            all_warriors[instigator_index].strength = all_warriors[instigator_index].strength - all_warriors[opponent_index].strength;
            all_warriors[opponent_index].strength = 0;
            cout << instigator.name << " defeats " << opponent.name << endl;
        }
        else{
            all_warriors[opponent_index].strength = all_warriors[opponent_index].strength - all_warriors[instigator_index].strength;
            all_warriors[instigator_index].strength = 0;
            cout << opponent.name << " defeats " << instigator.name << endl;
        }
        
    }
}

void openFileAndLoop(vector<Warrior>& all_warriors){
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
            size_t instigator_index = getWarriorIndexFromName(all_warriors, instigator_name);
            size_t opponent_index = getWarriorIndexFromName(all_warriors, opponent_name);
            warriorsBattle(all_warriors, instigator_index, opponent_index);
        }
    }
}
