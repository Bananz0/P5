//
// Created by glenm on 02/03/2024.
//

#include "Creature.h"

Creature::Creature() : strength(3) , hitpoints(30), type(0) {}
Creature::Creature(int newType, int newStrength, int newHit) {
    type = newType;
    strength = newStrength;
    hitpoints = newHit;
}

string Creature::getSpecies() {
    return "Unknown";
}
int Creature::getDamage() {
    int damage;
    damage = (rand() % strength) + 1;
    cout << getSpecies( ) << " attacks for " <<
         damage << " points!" << endl;
    return damage;
}

void Creature::setType(int typeIn) {
    type = typeIn;
}
void Creature::setStrength(int strengthIn) {
    strength = strengthIn;
}
void Creature::setHitPoints(int hitpointIn) {
    hitpoints= hitpointIn;
}

Human::Human()  {
    setType(0);
}
int Human::getDamage() {
    int damage;
    damage = Creature::getDamage();
    return damage;
}
string Human::getSpecies() {
    return "Human";
}

Demon::Demon() {
    setType(1);
}
int Demon::getDamage() {
    int damage;
    damage = Creature::getDamage();
    if ((rand( ) % 100) < 5)
    {
        damage = damage + 50;
        cout << "Demonic attack inflicts 50 "
             << " additional damage points!" << endl;
    }
    return damage;
}
string Demon::getSpecies() {
    return "Demon";
}

Elf::Elf(){
    setType(2);
}
int Elf::getDamage() {
    int damage;
    damage = Creature::getDamage();
    if ((rand() % 10)==0)
    {
        cout << "Magical attack inflicts " << damage <<
             " additional damage points!" << endl;
        damage = damage * 2;
    }

    return damage;
}
string Elf::getSpecies() {
    return "Elf";}

Cyberdemon::Cyberdemon() {
    setType(3);
}
int Cyberdemon::getDamage() {
    int damage;
    damage = Demon::getDamage();
    return damage;
}
string Cyberdemon::getSpecies() {
    return "Cyberdemon";
}

Balrog::Balrog()  {
    setType(4);
}
int Balrog::getDamage() {
    int damage;
    damage = Demon::getDamage();
    int damage2 = Creature::getDamage();
    cout << "Balrog speed attack inflicts " << damage2 <<
         " additional damage points!" << endl;
    damage = damage + damage2;
    return damage;
}
string Balrog::getSpecies() {
    return "Balrog";
}