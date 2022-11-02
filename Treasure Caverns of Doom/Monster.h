#include "Player.h"
#include "Item.h"



#ifndef MONSTER_H
#define MONSTER_H

class Monster {
	
protected:
string monsterListOfNames[50] = { "Rottingspawn", "Shadowwing", "Netherspawn","Thundergolem",
"The Wretched Mumbler", "The Cloudy Face", "The Greedy Miscreation",
"The Stormcloud Terror Bee", "The Black - Eyed Bane Rhino", "The Ivory Cavern Sheep",
"Vexman", "Grievehood", "Frightserpent", "Grievesnake", "The Tall Ooze",
"The White Abortion", "The Reckless Presence", "The Primeval Mist Vermin",
"The Lone Thunder Monkey", "The Wild Harlequin Viper", "Bonescreamer",
"Corpsedeviation", "Soilcrackle", "Barbtalon", "The Grim Hunter",
"The Defiant Man", "The Brown Phenomenon", "The Long - Horned Corpse Dog",
"The Tattooed Frost Dog", "The Blood - Eyed Berserker Dog",
"Thornling", "Banetalon", "Vilelich", "Banemutant", "The Horrible Freak", "The Meager Howler",
"The Wild Revenant", "The Barb - Tailed Terror Behemoth", "The Golden Ash Hog",
"The Taloned Harlequin Buffalo", "Webwing", "Rottingflayer", "Mornserpent",
"Bouldermask", "The Nasty Face", "The Aged Fiend", "The Angry Blob", "The Giant Sun Cobra",
"The Brutal Horror Frog", "The Patriarch Vampire Panther" };

string hunterListOfNames[15] = { "Zoowee Blubberworth",
"Flufffy Gloomkins","Buritt Noseface","Peaberry Wigglewhistle","Trashwee Sockborn",
"Flapberry Fudgewhistle", "Gummoo Hooperbottom", "Humster Pottyworthy",
"Bugby Doodoohill", "Gootu Snotborn", "Peafy Doodoofish", "Peawee Pimplehair",
"Chewlu Boogerbrain", "Eggster HoboSmittens", "Andre Pinto" };

string monsterName;
int monsterLevel;
int monsterHealth;
int monsterMaxHealth;
int monsterDefense;
int monsterAttack;
int monsterDamage;
Item monsterItem;
string monsterLocation;

public:
	Monster();
	Monster(string name, int level, int health, int defense, int attack, string location);
	~Monster();
	void setMonsterItem(Item loot);
	void setMonsterName(string newName);
	void setMonsterHP(int hp);
	void setMonsterAttack(int atk);
	void setMonsterDefense(int def);
	void setMonsterLevel(int level);
	void setMonsterLocation(string location);
	void getDetails();

	string getMonsterName();
	int getMonsterHP();
	int getMonsterMaxHP();
	int getMonsterAttack();
	int getMonsterDefense();
	int getMonsterLevel();
	Item getMonsterItem();
	string getMonsterLocation();
	void testClassName();
};

#endif