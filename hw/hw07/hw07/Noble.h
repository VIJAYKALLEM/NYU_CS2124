#ifndef Noble_h
#define Noble_h
#include <iostream>
#include <string>
#include <vector>
namespace WarriorCraft{
    class Protector;

    class Noble{
    public:
        Noble(const std::string& name);
        void battle(Noble& opponent);
        virtual int getStrength() const = 0;
        bool isDead() const;
        const std::string& getName() const;
        virtual void die();
        virtual void updateStrength(double ratio) = 0;
        virtual void printBattleCrysIfNecessary();
    private:
        std::string name;
        bool dead;
    };

    class Lord : public Noble{
    public:
        Lord(const std::string& name);
        bool hires(Protector& new_protector);
        int getStrength() const;
        void die();
        void updateStrength(double ratio);
        void printBattleCrysIfNecessary();
    private:
        std::vector<Protector*> army;
        int army_strength;
    };

    class PersonWithStrengthToFight : public Noble{
    public:
        PersonWithStrengthToFight(const std::string& name, int strength);
        int getStrength() const;
        void die();
        void updateStrength(double ratio);
    private:
        int strength;
    };
}
#endif /* Noble_h */
