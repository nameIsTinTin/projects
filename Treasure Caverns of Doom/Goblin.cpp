#include "Goblin.h"

/// <summary>
/// The Goblin Class which has its own variables and stats
/// </summary>

Goblin::Goblin(){
	monsterLevel = 1; 
	monsterHealth = monsterLevel * (rand() % 3 + 2); 
	monsterMaxHealth = monsterHealth;
	monsterAttack = monsterLevel + (rand() % 3 + 1); 
	monsterDefense = monsterLevel + (rand() % 2 + 1); 
	monsterDamage = monsterLevel;
}
Goblin::Goblin(string name, int level, int health, int defense, int attack){}
Goblin::~Goblin(){}
void Goblin::setGoblinItem(Item loot) { monsterItem = loot; }
void Goblin::setGoblinName(string newName) { monsterName = newName; }
void Goblin::setGoblinHP(int hp) { monsterHealth = hp; }
void Goblin::setGoblinAttack(int atk) { monsterAttack = atk; }
void Goblin::setGoblinDamage(int atk) { monsterDamage = atk; }
void Goblin::setGoblinDefense(int def) { monsterDefense = def; }
void Goblin::setGoblinLevel(int level) { monsterLevel = level; }
void Goblin::setGoblinLocation(string location){}
void Goblin::getDetails(){
	cout << endl; 
	cout << "Goblin's Name: " << monsterName << endl; 
	cout << "Goblin's Level: " << monsterLevel << endl;
	cout << "Goblin's Health: " << monsterHealth << endl; 
	cout << "Goblin's Attack: " << monsterAttack << endl; 
	cout << "Goblin's Defense: " << monsterDefense << endl; 
	cout << "Goblin's Damage: " << monsterDamage << endl;
}

string Goblin::getGoblinName() { return monsterName; }
int Goblin::getGoblinHP() { return monsterHealth; }
int Goblin::getGoblinMaxHP() { return monsterMaxHealth; }
int Goblin::getGoblinAttack() { return monsterAttack; }
int Goblin::getGoblinDamage() { return monsterDamage; }
int Goblin::getGoblinDefense() { return monsterDefense; }
int Goblin::getGoblinLevel() { return monsterLevel; }
Item Goblin::getGoblinItem() { return monsterItem; }
string Goblin::getGoblinLocation() { return monsterLocation; }
