#include "Player.h"
#include "Item.h"
#include "Monster.h"


#ifndef OGRE_H
#define OGRE_H

class Ogre : public Monster {
protected:

public:
	Ogre();
	Ogre(string name, int level, int health, int defense, int attack);
	~Ogre();
	void setOgreItem(Item loot);
	void setOgreName(string newName);
	void setOgreHP(int hp);
	void setOgreAttack(int atk);
	void setOgreDamage(int dmg);
	void setOgreDefense(int def);
	void setOgreLevel(int level);
	void setOgreLocation(string location);
	virtual void getDetails();

	string getOgreName();
	int getOgreHP();
	int getOgreMaxHP();
	int getOgreAttack();
	int getOgreDamage();
	int getOgreDefense();
	int getOgreLevel();
	Item getOgreItem();
	string getOgreLocation();

};


#endif