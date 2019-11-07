#ifndef Warrior_h
#define Warrior_h
#include <iostream>
#include <string>
namespace WarriorCraft{
    class Lord;

    class Protector{
    public:
        Protector(const std::string& name, int strength);
        virtual ~Protector() {};
        // sets boss to new_boss (returns false if already hired)
        bool hire(Lord* new_boss);
        // getter of dead status
        bool isDead() const;
        // strength getter
        int getStrength() const;
        // loses strength using the winning ratio
        void loseStrength(double ratio);
        // sets boss to nullptr
        void getFired();
        // must print defending yell.
            // but this depends on derived type
            // required but we cannot write it for the protector class
                // --> it is made abstract.
        virtual void printDefendingYell() const = 0;
        // set strength to 0 and dead to true
        void die();
    protected:
        // only derived protectors should see name and boss;
        const std::string& getName() const;
        const Lord* const getBoss() const;
    private:
        std::string name;
        int strength;
        Lord* boss;
        bool dead;
    };

    class Archer : public Protector{
    public:
        Archer(const std::string& name, int strength);
        void printDefendingYell() const;
    };

    class Wizard : public Protector{
    public:
        Wizard(const std::string& name, int strength);
        void printDefendingYell() const;
    };

    class Swordsman : public Protector{
    public:
        Swordsman(const std::string& name, int strength);
        void printDefendingYell() const;
    };
}
#endif /* Warrior_h */
