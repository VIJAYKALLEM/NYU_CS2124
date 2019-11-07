#ifndef Warrior_h
#define Warrior_h
#include <iostream>
#include <string>
namespace WarriorCraft{
    class Lord;

    class Protector{
    public:
        Protector(const std::string& name, int strength);
        bool hire(Lord* new_boss);
        bool isDead() const;
        int getStrength() const;
        void loseStrength(double ratio);
        virtual void printDefendingYell() const = 0;
        void die();
    protected:
        const std::string& getName() const;
        Lord* getBoss() const;
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
