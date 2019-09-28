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
private:
    class Weapon{
        friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);
    public:
        Weapon(string name, int strength): name(name), strength(strength) {};
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
    os << "Warrior: " << warrior.name << " " << warrior.weapon;
    return os;
}

void openFileAndLoop(vector<Warrior>& all_warriors);

int main(){
    vector<Warrior> all_warriors;
    openFileAndLoop(all_warriors);
}

void openFileAndLoop(vector<Warrior>& all_warriors){
    ifstream file("warriors.txt");
    string command;
    while (file >> command){
        cout << "ITS DOING THINGS " << command << endl;
        if (command == "Warrior"){
            string name;
            string weapon_name;
            int strength;
            file >> name >> weapon_name >> strength;
            cout << "NAME" << "WEAPON NAMEEEE " << weapon_name << endl;
            all_warriors.push_back(Warrior(name, weapon_name, strength));
            for (Warrior curr_warrior : all_warriors){
                cout << curr_warrior << endl;
            }
        }
        else if (command == "Status"){
            cout << "STATUS";
            for (Warrior curr_warrior : all_warriors){
                cout << curr_warrior << endl;
            }
        }
        else if (command == "Battle"){
            string instigator_name, opponent_name;
            file >> instigator_name >> opponent_name;
            cout << "dunnit " << endl;
        }
    }
}
