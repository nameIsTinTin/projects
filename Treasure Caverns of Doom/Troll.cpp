#include "Troll.h"


//The strongest minion of the Dragon ! 

Troll::Troll() {
	monsterLevel = 4;
	monsterHealth = monsterLevel * (rand() % 7 + 5);
	monsterMaxHealth = monsterHealth;
	monsterAttack = monsterLevel + (rand() % 7 + 4);
	monsterDefense = monsterLevel + (rand() % 5 + 2);
	monsterDamage = monsterLevel + (rand() % 4 + 2);
}
Troll::Troll(string name, int level, int health, int defense, int attack) {}
Troll::~Troll() {}
void Troll::setTrollItem(Item loot) { monsterItem = loot; }
void Troll::setTrollName(string newName) { monsterName = newName; }
void Troll::setTrollHP(int hp) { monsterHealth = hp; }
void Troll::setTrollAttack(int atk) { monsterAttack = atk; }
void Troll::setTrollDamage(int dmg) { monsterDamage = dmg; }
void Troll::setTrollDefense(int def) { monsterDefense = def; }
void Troll::setTrollLevel(int level) { monsterLevel = level; }
void Troll::setTrollLocation(string location) { monsterLocation = location; }
void Troll::getDetails() {
	cout << endl;
	cout << "Troll's Name: " << monsterName << endl;
	cout << "Troll's Level: " << monsterLevel << endl;
	cout << "Troll's Health: " << monsterHealth << endl;
	cout << "Troll's Attack: " << monsterAttack << endl;
	cout << "Troll's Defense: " << monsterDefense << endl;
	cout << "Troll's Damage: " << monsterDamage << endl;
}

string Troll::getTrollName() { return monsterName; }
int Troll::getTrollHP() { return monsterHealth; }
int Troll::getTrollMaxHP() { return monsterMaxHealth; }
int Troll::getTrollAttack() { return monsterAttack; }
int Troll::getTrollDamage() { return monsterDamage; }
int Troll::getTrollDefense() { return monsterDefense; }
int Troll::getTrollLevel() { return monsterLevel; }
Item Troll::getTrollItem() { return monsterItem; }
string Troll::getTrollLocation() { return monsterLocation; }
