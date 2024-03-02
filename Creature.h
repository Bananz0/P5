//
// Created by glenm on 02/03/2024.
//

#ifndef P5_CREATURE_H
#define P5_CREATURE_H

#include <string>
#include <iostream>
#include <random>

using  std::string;
using std::cout;
using std::endl;


class Creature {
private:
    int type;
    int hitpoints;
    int strength;
public:

    virtual string getSpecies();
    Creature();
    Creature(int newType, int newStrength, int newHit);
    void setType(int typeIn);
    void setStrength(int strengthIn);
    void setHitPoints(int hitpointIn);
    virtual int getDamage();
};
class Human : public Creature {
public:
    Human();
    int getDamage() override;
    string getSpecies() override;
};
class Demon : public Creature {
public:
    Demon();
    int getDamage() override;
    string getSpecies() override;
};
class Elf : public Creature {
public:
    Elf();
    int getDamage() override;
    string getSpecies() override;
};
class Cyberdemon : public Demon {
public:
    Cyberdemon();
    int getDamage() override;
    string getSpecies() override;
};
class Balrog : public Demon {
public:
    Balrog();
    int getDamage() override;
    string getSpecies() override;
};
#endif //P5_CREATURE_H
