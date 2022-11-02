#include "Player.h"
#include "Item.h"
#include "Monster.h"


#ifndef DRAGON_H
#define DRAGON_H

class Dragon : public Monster {

private:
	string dragonName;
	int dragonLevel;
	int dragonHealth;
	int dragonDefense;
	int dragonAttack;
	//int dragonLevel;
	int dragonDamage;
	Item dragonItem;
	string dragonLocation;

public:
	Dragon();
	Dragon(string name, int level, int hp, int attack, int defense, string location, Item item);
	~Dragon();
	void setDragonItem(Item loot);
	void setDragonName(string newName);
	void setDragonHP(int hp);
	void setDragonAttack(int atk);
	void setDragonDefense(int def);
	void setDragonLevel(int level);
	void setDragonLocation(string location);
	void setDragonClawAttack();
	void setDragonFireAttack();
	virtual void getDetails();
	string getDragonName();
	int getDragonHP();
	int getDragonMaxHP();
	int getDragonAttack();
	int getDragonDamage();
	int getDragonDefense();
	int getDragonLevel();
	string getDragonLocation();
	Item getDragonItem();
	void testClassName();

};

#endif