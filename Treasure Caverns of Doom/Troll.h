#include "Player.h"
#include "Item.h"
#include "Monster.h"


#ifndef TROLL_H
#define TROLL_H

class Troll : public Monster {
protected:

public:
	Troll();
	Troll(string name, int level, int health, int defense, int attack);
	~Troll();
	void setTrollItem(Item loot);
	void setTrollName(string newName);
	void setTrollHP(int hp);
	void setTrollAttack(int atk);
	void setTrollDamage(int dmg);
	void setTrollDefense(int def);
	void setTrollLevel(int level);
	void setTrollLocation(string location);
	virtual void getDetails();

	string getTrollName();
	int getTrollHP();
	int getTrollMaxHP();
	int getTrollAttack();
	int getTrollDamage();
	int getTrollDefense();
	int getTrollLevel();
	Item getTrollItem();
	string getTrollLocation();

};


#endif