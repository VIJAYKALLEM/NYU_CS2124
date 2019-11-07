#ifndef Noble_h
#define Noble_h
#include <iostream>
#include <string>
#include <vector>
namespace WarriorCraft{
    class Protector;

    class Noble{
    public:
        //regular constructor
        Noble(const std::string& name);
        virtual ~Noble() {};
        void battle(Noble& opponent);
        virtual int getStrength() const = 0;
            // Lord will get entire army's strength
            // Person with Strength to fight will get own strength
            // both need to get strength to battle, so this is an abstract fxn
        bool isDead() const;
        const std::string& getName() const;
        // die method sets bool dead to 0.
        virtual void die();
        virtual void updateStrength(double ratio) = 0;
        
        // only Lords have to print a battle cry. Therefore this function is empty and
        // overriden only for Lords. That way it can be called on a generic noble object and
        // only print battle cry if noble is a lord.
        virtual void printBattleCrysIfNecessary() const;
    private:
        std::string name;
        bool dead;
    };

    class Lord : public Noble{
    public:
        //regular constructor (calls Noble constructor)
        Lord(const std::string& name);
        bool hires(Protector& new_protector);
        void fires(Protector& fired_protector);
        //required override of abstract getStrength and updateStrength methods
        int getStrength() const;
        // die method kills all protectors and sets army strength to 0.
        // die method ALSO calls Noble::die() to set bool dead to true.
        void die();
        //updates strengths of all protectors and recalculates army strength.
        void updateStrength(double ratio);
        void printBattleCrysIfNecessary() const;
    private:
        std::vector<Protector*> army;
        int army_strength;
    };

    class PersonWithStrengthToFight : public Noble{
    public:
        //regular constructor (calls Noble constructor)
        PersonWithStrengthToFight(const std::string& name, int strength);
        //required override of abstract getStrength and updateStrength methods
        int getStrength() const;
        // die method sets strength to 0.
        // die method ALSO calls Noble::die() to set bool dead to true.
        void die();
        void updateStrength(double ratio);
    private:
        int strength;
    };
}
#endif /* Noble_h */
