#include "Monster.h"
#include "MonsterENUM.h"

/*
The monster class that has mutator and accessor methods. The attack and defending methods are yet to be implemented 
until Part B where battle is formally introduced - then these methods will be implemented accordingly and properly.

Part B's comment : Additional monster stats has been added, and how the Monster fights is 
designed inside of the Main class.
*/
Monster::Monster() {
	int a = rand() % 50; 
	monsterName = monsterListOfNames[a];
	monsterLevel = rand() % 3 + 1;
	monsterHealth = rand() % 5 + 1 * monsterLevel;
	monsterDefense = rand() % 5 + 1 * monsterLevel;
	monsterAttack = rand() % 5 + 1 * monsterLevel;
	monsterMaxHealth = monsterHealth;
}

Monster::Monster(string name, int level, int health, int defense, int attack, string location) {
	setMonsterName(name);
	setMonsterHP(health);
	setMonsterAttack(attack);
	setMonsterDefense(defense);
	setMonsterLevel(level);
	setMonsterLocation(location);
}


Monster::~Monster(){}

void Monster::setMonsterName(string newName) { monsterName = newName; }
void Monster::setMonsterHP(int hp) { monsterHealth = hp; }
void Monster::setMonsterAttack(int atk) { monsterAttack = atk; }
void Monster::setMonsterDefense(int def) { monsterDefense = def; }
void Monster::setMonsterLevel(int level) { monsterLevel = level; }
void Monster::setMonsterItem(Item loot) { monsterItem = loot; }
void Monster::setMonsterLocation(string location) { monsterLocation = location; }

void Monster::getDetails() {
	cout << "\n";
	cout << "Monster Name: " << monsterName << "\n";
	cout << "Monster Level: " << monsterLevel << "\n";
	cout << "Monster Health: " << monsterHealth << "\n";
	cout << "Monster Defense: " << monsterDefense << "\n";
	cout << "Monster Attack: " << monsterAttack << "\n";

}

string Monster::getMonsterName() { return monsterName; }
int Monster::getMonsterHP() { return monsterHealth; }
int Monster::getMonsterMaxHP() { return monsterMaxHealth; }
int Monster::getMonsterAttack() { return monsterAttack; }
int Monster::getMonsterDefense() { return monsterDefense; }
int Monster::getMonsterLevel() { return monsterLevel; }
Item Monster::getMonsterItem() { return monsterItem; }
string Monster::getMonsterLocation() { return monsterLocation; }


//void Monster::testClassName() {
//
//	Monster defaultMonster = Monster::Monster();
//	cout << "Default Monster Details: " << "\n";
//	defaultMonster.getDetails();
//
//	cout << "\n";
//
//	Item overloadedItem = Item::Item(1, 1, 1);
//	//overloadedItem.setItemName("Overloaded");
//	Monster overloadedMonster = Monster::Monster("Overloaded", 1, 1, 1, 1, "Overloaded"); 
//	overloadedMonster.setMonsterItem(overloadedItem);
//	cout << "Overloaded Monster w/ Item Details: " << "\n";
//	overloadedMonster.getDetails();
//
//}