#include "Hobgoblin.h"
#include "Goblin.h"


/// <summary>
/// 
/// The Hobgoblin class which has its own stats
/// </summary>
Hobgoblin::Hobgoblin(){
	monsterLevel = 2; 
	monsterHealth = monsterLevel * (rand() % 5 + 3); 
	monsterMaxHealth = monsterHealth;
	monsterAttack = monsterLevel + (rand() % 4 + 2); 
	monsterDefense = monsterLevel + (rand() % 3 + 1); 
	monsterDamage = monsterLevel + (rand() % 2 + 1);
}
Hobgoblin::Hobgoblin(string name, int level, int health, int defense, int attack){}
Hobgoblin::~Hobgoblin(){}

void Hobgoblin::setHobgoblinItem(Item loot) { monsterItem = loot; }
void Hobgoblin::setHobgoblinName(string newName) { monsterName = newName; }
void Hobgoblin::setHobgoblinHP(int hp) { monsterHealth = hp; }
void Hobgoblin::setHobgoblinAttack(int atk) { monsterAttack = atk; }
void Hobgoblin::setHobgoblinDamage(int dmg) { monsterDamage = dmg; }
void Hobgoblin::setHobgoblinDefense(int def) { monsterDefense = def; }
void Hobgoblin::setHobgoblinLevel(int level) { monsterLevel = level; }
void Hobgoblin::setHobgoblinLocation(string location){}
void Hobgoblin::getDetails(){
	cout << endl; 
	cout << "Hobgoblin's Name: " << monsterName << endl; 
	cout << "Hobgoblin's Level: " << monsterLevel << endl;
	cout << "Hobgoblin's Health: " << monsterHealth << endl; 
	cout << "Hobgoblin's Attack: " << monsterAttack << endl; 
	cout << "Hobgoblin's Defense: " << monsterDefense << endl; 
	cout << "Hobgoblin's Damage: " << monsterDamage << endl;
}

string Hobgoblin::getHobgoblinName() { return monsterName; }
int Hobgoblin::getHobgoblinHP() { return monsterHealth; }
int Hobgoblin::getHobgoblinMaxHP() { return monsterMaxHealth; }
int Hobgoblin::getHobgoblinAttack() { return monsterAttack; }
int Hobgoblin::getHobgoblinDamage() { return monsterDamage; }
int Hobgoblin::getHobgoblinDefense() { return monsterDefense; }
int Hobgoblin::getHobgolbinLevel() { return monsterLevel; }
Item Hobgoblin::getHobgoblinItem() { return monsterItem; }
string Hobgoblin::getHobgoblinLocation() { return monsterLocation; }

