/*
 Simran K Soin (sks684)
 CS2124 HW05
 13 Oct 2019
 Focusing on Dynamic Memory
    Creating Nobles & Warriors and battling
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
       
    int getStrength() const{return strength;} // strength getter
       
    void killed(){
        // kills warrior
        dead = true;
        strength = 0;
    }
    void updateStrength(double ratio){
        // updates strength using winning ratio from battle
        strength *= (1-ratio);
    }
       
    const string& getName() const{return name;} // name getter
    const bool unemployed() const {
        //returns true if warrior is unemployed
        return (hired==false);
        
    }
    
private:
    string name;
    int strength;
    bool hired, dead;
};



class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs){
        os << rhs.name << " has an army of " << rhs.army_size << endl;
        for (size_t index=0; index<rhs.army_size; ++index){
            os << "     " << *((rhs.army)[index]) << endl;
        }
        return os;
    }
public:
    //regular constructor
    Noble(const string& name): name(name), army(new Warrior*[1]), army_size(0), army_capacity(1), army_strength(0), dead(false) {};
    //copy constructor
    Noble(const Noble& rhs): name(rhs.name), army(new Warrior*[rhs.army_capacity]), army_size(rhs.army_size), army_capacity(rhs.army_capacity), army_strength(rhs.army_strength), dead(rhs.dead) {
        for (size_t index = 0; index<rhs.army_size; ++index){
            army[index] = new Warrior(*rhs.army[index]);
        }
    };
    //assignment operator
    Noble& operator=(const Noble& rhs){
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
    ~Noble(){
        for (size_t index=0; index<army_size; ++index){
            delete army[index];
        }
        delete [] army;
    };
    
    const int getArmyStrength() const{
        //army strength getter
        return army_strength;
    }
    
    bool warriorInArmy(Warrior*& warrior) const{
        //returns true if the given warrior is in this noble's army
        for (size_t index=0; index<army_size; ++index){
            if (army[index]->getName() == warrior->getName()){
                return true;
            }
        }
        return false;
    }
    void reduceArmyStrength(double ratio){
        // multiply each warrior's strength by (1-losing ratio)
        // recalculate total army strength
        army_strength = 0;
        for (size_t index=0; index<army_size; ++index){
            army[index]->updateStrength(ratio);
            army_strength += army[index]->getStrength();
        }
    }
    
     bool hire(Warrior*& new_warrior_ptr){
         // if the noble dead or warrior is already hired
         // return false
         // else, hire warrior
        if (dead || !new_warrior_ptr->getHired()){
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
         army[army_size] = new_warrior_ptr;
         army_size += 1;
         army_strength += new_warrior_ptr->getStrength();
         return true;
     }
    
    bool fire(Warrior*& fired_warrior){
        // fires given warrior
            //tells warrior it is not hired anymore
            //reduces army size and strength accordingly
        
        //if this noble is dead, it cannot fire the warrior, return false
        if (dead){ return false; }
        fired_warrior->getFired();
        army_size -= 1;
        army_strength -= fired_warrior->getStrength();
        
        //moves over warriors in array
            //(to make sure fired warrior is no longer within size)
        bool move_over_one = false;
        for (size_t index = 0; index< army_size; ++index){
            // if we found the warrior to remove, set bool to true
                // move the rest of the vector over one
                // delete last item in list
            if (army[index] == fired_warrior){
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
        cout << fired_warrior->getName() << "! -- " << name << endl;
        //returns true if successfully fired the warrior
        return true;
    }
    
    void killed(){
           // called if noble has been killed
            // --> loops through and kills all the warriors
           dead = true;
           army_strength = 0;
           for (size_t index = 0; index< army_size; ++index){
               army[index]->killed();
           }
       }
        
    bool isDead() const {return dead;}; //returns true if noble is dead
    
    const string& getName() const { return name;} //name getter
    void battle(Noble*& opponent){
        //called when this noble instigates battle on another
        
        cout << name << " battles " << opponent->getName() << endl;
        
        // if one or both opponents is dead, battle cannot occur
        if (opponent->isDead()){
            if (dead){
                cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            }
            else{ cout << "He's dead, " << name << endl;}
        }
        
        // if both opponents are equally strong, mutual annihilation
        else if(opponent->getArmyStrength() == army_strength){
            killed();
            opponent->killed();
            cout << "Mutual Annihalation: " << name << " and ";
            cout << opponent->getName() << "die at each other's hands" << endl;
        }
        
        
        // opponent defeats self
        else if (opponent->getArmyStrength() > army_strength){
            double losing_ratio = (double(army_strength) /
                                   double(opponent->getArmyStrength()));
            opponent->reduceArmyStrength(losing_ratio);
            killed();
            cout << opponent->getName() << " defeats " << name << endl;
        }
        
        
        // self defeats opponent
        else if (opponent->getArmyStrength() < army_strength){
            double losing_ratio = (double(opponent->getArmyStrength()) /
                                   double(army_strength));
            reduceArmyStrength(losing_ratio);
            opponent->killed();
            cout << name << " defeats " << opponent->getName() << endl;
        }
    }

private:
    string name;
    Warrior** army;
    size_t army_size;
    size_t army_capacity;
    int army_strength; //running count of the total strength of army
    bool dead;
};

void createNoble(const string& noble_name, vector<Noble*>& nobles); //creates noble object
void createWarrior(const string& warrior_name, int warrior_strength, vector<Warrior*>& warriors); //creates warrior object
void hireWarrior(const string& noble_name, const string& warrior_name, vector<Warrior*>& warriors, vector<Noble*>& nobles); //noble adds warrior to army
void fireWarrior(const string& noble_name, const string& warrior_name, vector<Warrior*>& warriors, vector<Noble*>& nobles); //noble fires warrior from army
void battleNobles(vector<Noble*>& nobles, const string& instigator_name, const string& opponent_name); //battles two nobles
void printStatus(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);

int main() {
    //loops through file, parses the commands, and calls appropriate functions
    ifstream file("noblewarriors.txt");
    string command;
    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    while (file >> command){
        if (command == "Noble"){
            string noble_name;
            file >> noble_name;
            createNoble(noble_name, nobles);
        }
        else if (command == "Warrior"){
            string warrior_name;
            int warrior_strength;
            file >> warrior_name >> warrior_strength;
            createWarrior(warrior_name, warrior_strength, warriors);
        }
        
        else if (command == "Hire"){
            string noble_name;
            string warrior_name;
            file >> noble_name >> warrior_name;
            hireWarrior(noble_name, warrior_name, warriors, nobles);
        }
        
        else if (command == "Status"){
            printStatus(nobles, warriors);
        }
        
        else if (command == "Fire"){
            string noble_name;
            string warrior_name;
            file >> noble_name >> warrior_name;
            fireWarrior(noble_name, warrior_name, warriors, nobles);
        }
        
        else if (command == "Clear"){
            nobles.clear();
            warriors.clear();
        }
        
        else if (command == "Battle"){
            string instigator_name;
            string opponent_name;
            file >> instigator_name >> opponent_name;
            battleNobles(nobles, instigator_name, opponent_name);
        }
    }
    file.close();
}

void createNoble(const string& noble_name, vector<Noble*>& nobles){
    /*checks if noble with this name already exists. If it doesnt,
     it creates a new noble object on the heap and adds the pointer
     to the nobles vector*/
    
    // checks if noble with this name already exists
    bool already_exists = false;
    for (Noble* curr_noble : nobles){
        if (curr_noble->getName() == noble_name){
            already_exists = true;
            break;
        }
    }
    //if noble with this name already exists, print to console
    if(already_exists){cout << "Noble with name " << noble_name << " already exists." << endl;}
    else{
        //otherwise, creates new noble object on heap and adds the pointer to vector
        Noble* new_noble = new Noble(noble_name);
        nobles.push_back(new_noble);
    }
}



void createWarrior(const string& warrior_name, int warrior_strength, vector<Warrior*>& warriors){
    /*checks if warrior with this name already exists. If it doesnt,
    it creates a new warrior object on the heap and adds the pointer
    to the warriors vector*/
    
    bool already_exists = false;
    for (Warrior* curr_warr : warriors){
        if (curr_warr->getName() == warrior_name){
            already_exists = true;
            break;
        }
    }
    if(already_exists){cout << "Warrior with name " << warrior_name << " already exists." << endl;}
    else{
        Warrior* new_warrior = new Warrior(warrior_name, warrior_strength);
        warriors.push_back(new_warrior);
    }
}

void hireWarrior(const string& noble_name, const string& warrior_name, vector<Warrior*>& warriors, vector<Noble*>& nobles){
    /*checks if warrior with this name exists and is not already hired.
     checks if noble with this name exists.
     If all passes, Noble hires the warrior
     */
    Warrior* warr_to_hire = nullptr;
    for (Warrior* curr_warr : warriors){
        if (curr_warr->getName() == warrior_name){
            warr_to_hire = curr_warr;
            break;
        }
    }
    if(warr_to_hire == nullptr){
        cout << "Warrior with name " << warrior_name << " doesn't exist." << endl;
    }
    else{
        bool hired = false;
        for (Noble* curr_noble : nobles){
            if (curr_noble->getName() == noble_name){
                hired = true;
                curr_noble->hire(warr_to_hire);
                
                break;
            }
        }
        if(!hired){cout << "Noble with name " << noble_name << " doesn't exist." << endl;}
    }
}
void fireWarrior(const string& noble_name, const string& warrior_name, vector<Warrior*>& warriors, vector<Noble*>& nobles){
    /*checks if warrior with this name exists.
    checks if noble with this name exists.
    checks that this noble has this warrior in the army.
    If all passes, Noble fires the warrior
    */
    Warrior* warr_to_fire = nullptr;
    for (Warrior* curr_warr : warriors){
        if (curr_warr->getName() == warrior_name){
            warr_to_fire = curr_warr;
            break;
        }
    }
    if(warr_to_fire == nullptr){
        cout << "Warrior with name " << warrior_name << " doesn't exist." << endl;
    }
    bool fired = false;
    for (Noble* curr_noble : nobles){
        if (curr_noble->getName() == noble_name){
            fired = true;
            if(curr_noble->warriorInArmy(warr_to_fire)){
                curr_noble->fire(warr_to_fire);
            }
            else{
                cout << "Noble " << noble_name << " doesn't have "<< warrior_name << " in army."<< endl;
                
            }
            break;
        }
    }
    if(!fired){cout << "Noble with name " << noble_name << "doesn't exist" << endl;}
}

void battleNobles(vector<Noble*>& nobles, const string& instigator_name, const string& opponent_name){
    /*checks that both nobles with those names exist. If so, the instigator
     battles the opponent*/
    Noble* instigator = nullptr;
    Noble* opponent = nullptr;
    for (Noble* curr_noble : nobles){
        if (curr_noble->getName() == instigator_name){
            instigator = curr_noble;
            if (opponent != nullptr){
                break;
                
            }
            
        }
        if (curr_noble->getName() == opponent_name){
            opponent = curr_noble;
            if (instigator != nullptr){
                break;
            }
        }
    }
    if(instigator == nullptr) {cout << instigator_name << " doesn't exist." << endl;}
    if(opponent == nullptr) {cout << opponent_name << " doesn't exist." << endl;}
    instigator->battle(opponent);
    
}

void printStatus(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){
    /* loops through the nobles vector, dereferences each noble pointer, and prints status. loops through the warriors vector, checks if unemployed, and if so, prints status.
    */
    
    cout << "Status" << endl;
    cout << "======" << endl;
    cout << "Nobles: " << endl;
    bool none = true;
    for (const Noble* curr_noble : nobles){
        if (!curr_noble->isDead()){
            none= false;
        cout << *curr_noble << endl;
        }
    }
    if(none){cout << "NONE" << endl;}
    cout << "Unemployed Warriors: " << endl;
    none = true;
    for (const Warrior* curr_warr : warriors){
        if (curr_warr->unemployed()){
            none= false;
            cout << *curr_warr << endl;
        }
    }
    if(none){cout << "NONE" << endl;}
}
