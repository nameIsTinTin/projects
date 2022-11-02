#include "Player.h"
#include "Item.h"
#include "Monster.h"


#ifndef GOBLIN_H
#define GOBLIN_H

class Goblin : public Monster {
protected: 

public:
	Goblin();
	Goblin(string name, int level, int health, int defense, int attack);
	~Goblin();
	void setGoblinItem(Item loot);
	void setGoblinName(string newName);
	void setGoblinHP(int hp);
	void setGoblinAttack(int atk);
	void setGoblinDamage(int dmg);
	void setGoblinDefense(int def);
	void setGoblinLevel(int level);
	void setGoblinLocation(string location);
	virtual void getDetails();

	string getGoblinName();
	int getGoblinHP();
	int getGoblinMaxHP();
	int getGoblinAttack();
	int getGoblinDamage();
	int getGoblinDefense();
	int getGoblinLevel();
	Item getGoblinItem();
	string getGoblinLocation();

};


#endif