#ifndef Noble_h
#define Noble_h
#include <iostream>
#include <string>
namespace WarriorCraft{
    class Warrior;

    class Noble{
        friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
    public:
        //regular constructor
        Noble(const std::string& name);
        //copy constructor
        Noble(const Noble& rhs);
        //assignment operator
        Noble& operator=(const Noble& rhs);
        //destructor
        ~Noble();
        
        const int getArmyStrength() const;
        
        bool warriorInArmy(Warrior*& warrior) const;
        
        void reduceArmyStrength(double ratio);
        
        bool hire(Warrior& new_warrior);
        
        bool fire(Warrior& fired_warrior);
        
        void killed();
            
        bool isDead() const;
        
        const std::string& getName() const;
        void battle(Noble& opponent);
        void warriorRanAway(Warrior& runaway);

    private:
        std::string name;
        Warrior** army;
        size_t army_size;
        size_t army_capacity;
        int army_strength; //running count of the total strength of army
        bool dead;
    };
}

#endif
