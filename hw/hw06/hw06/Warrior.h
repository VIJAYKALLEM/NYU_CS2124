#ifndef Warrior_h
#define Warrior_h
#include <string>
#include <iostream>
#include "Noble.h"
namespace WarriorCraft{
    class Warrior{
        friend std::ostream& operator<<(std::ostream& os, const Warrior& rhs);
    public:
            Warrior(const std::string& name, int strength);
            bool getHired(Noble* new_boss);
           
            void getFired();
           
            int getStrength() const;
           
            void killed();
            void updateStrength(double ratio);
               
            const std::string& getName() const;
            const bool unemployed() const;
            void runaway();
        
    private:
        std::string name;
        int strength;
        bool dead;
        Noble* boss;
    };

}
#endif
