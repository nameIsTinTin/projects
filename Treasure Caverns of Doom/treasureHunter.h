#include "Player.h"
#include "Item.h"
#include "Monster.h"


#ifndef TREASUREHUNTER_H
#define TREASUREHUNTER_H

class TreasureHunter : public Monster {
protected:
	int monsterWealth;
	int monsterSteal;

public:
	TreasureHunter();
	TreasureHunter(string name, int level, int health, int defense, int attack, int gold);
	~TreasureHunter();
	
	void setMonsterWealth(int value); 
	int getMonsterWealth();

	void setMonsterSteal(int value);
	int getMonsterSteal();

};


#endif