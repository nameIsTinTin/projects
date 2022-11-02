#include "Player.h"
#include "Item.h"
#include "Monster.h"


#ifndef HOBGOBLIN_H
#define HOBGOBLIN_H

class Hobgoblin : public Monster {
protected:

public:
	Hobgoblin();
	Hobgoblin(string name, int level, int health, int defense, int attack);
	~Hobgoblin();
	void setHobgoblinItem(Item loot);
	void setHobgoblinName(string newName);
	void setHobgoblinHP(int hp);
	void setHobgoblinAttack(int atk);
	void setHobgoblinDamage(int dmg);
	void setHobgoblinDefense(int def);
	void setHobgoblinLevel(int level);
	void setHobgoblinLocation(string location);
	virtual void getDetails();

	string getHobgoblinName();
	int getHobgoblinHP();
	int getHobgoblinMaxHP();
	int getHobgoblinAttack();
	int getHobgoblinDamage();
	int getHobgoblinDefense();
	int getHobgolbinLevel();
	Item getHobgoblinItem();
	string getHobgoblinLocation();

};


#endif