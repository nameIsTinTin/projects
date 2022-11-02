#include "Ogre.h"

// A child from the Monster Class which has bigger stats than most of the mobs
Ogre::Ogre() {
	monsterLevel = 3;
	monsterHealth = monsterLevel * (rand() % 6 + 4);
	monsterMaxHealth = monsterHealth;
	monsterAttack = monsterLevel + (rand() % 5 + 3);
	monsterDefense = monsterLevel + (rand() % 4 + 2);
	monsterDamage = monsterLevel + (rand() % 3 + 1);
}
Ogre::Ogre(string name, int level, int health, int defense, int attack) {}
Ogre::~Ogre() {}
void Ogre::setOgreItem(Item loot) { monsterItem = loot; }
void Ogre::setOgreName(string newName) { monsterName = newName; }
void Ogre::setOgreHP(int hp) { monsterHealth = hp; }
void Ogre::setOgreAttack(int atk) { monsterAttack = atk; }
void Ogre::setOgreDamage(int dmg) { monsterDamage = dmg; }
void Ogre::setOgreDefense(int def) { monsterDefense = def; }
void Ogre::setOgreLevel(int level) { monsterLevel = level; }
void Ogre::setOgreLocation(string location) {}
void Ogre::getDetails() {
	cout << endl;
	cout << "Ogre's Name: " << monsterName << endl;
	cout << "Ogre's Level: " << monsterLevel << endl;
	cout << "Ogre's Health: " << monsterHealth << endl;
	cout << "Ogre's Attack: " << monsterAttack << endl;
	cout << "Ogre's Defense: " << monsterDefense << endl;
	cout << "Ogre's Damage: " << monsterDamage << endl;
}

string Ogre::getOgreName() { return monsterName; }
int Ogre::getOgreHP() { return monsterHealth; }
int Ogre::getOgreMaxHP() { return monsterMaxHealth; }
int Ogre::getOgreAttack() { return monsterAttack; }
int Ogre::getOgreDamage() { return monsterDamage; }
int Ogre::getOgreDefense() { return monsterDefense; }
int Ogre::getOgreLevel() { return monsterLevel; }
Item Ogre::getOgreItem() { return monsterItem; }
string Ogre::getOgreLocation() { return monsterLocation; }
