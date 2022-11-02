#include "treasureHunter.h"

// A child from the Monster class which allows the player 
// an opportunity to get filthy rich !

TreasureHunter::TreasureHunter() {
	monsterName = hunterListOfNames[rand() % 15];
	monsterLevel = 3; 
	monsterAttack = monsterLevel + (rand() % 5 + 1);
	monsterDefense = 0; 
	monsterHealth = monsterLevel * (rand() % 9 + 4);
	monsterWealth = monsterLevel * (rand() % 15 + 5); 
	monsterSteal = rand() % 5 + 3;
}

TreasureHunter::TreasureHunter(string name, int level, int health, int defense, int attack, int gold) {
	monsterName = name; 
	monsterLevel = level; 
	monsterHealth = health;
	monsterDefense = defense;
	monsterAttack = attack; 
	monsterWealth = gold;
}

TreasureHunter::~TreasureHunter() {}

void TreasureHunter::setMonsterWealth(int value) {
	monsterWealth = value;
}
int TreasureHunter::getMonsterWealth() {
	return monsterWealth;
}

void TreasureHunter::setMonsterSteal(int value) {
	monsterSteal = value;
}

int TreasureHunter::getMonsterSteal() {
	return monsterSteal;
}
