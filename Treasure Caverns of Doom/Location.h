#include "Player.h"
#include "Monster.h"
#include "Goblin.h"
#include "Hobgoblin.h"
#include "Ogre.h"
#include "Troll.h"
#include "Dragon.h"
#include "treasureHunter.h"


#ifndef LOCATION_H
#define LOCATION_H

class Location {

private:
	string locationName; 
	string locationDescription; 
	vector<string> locationExits;
	bool locationExamined = false;
	Goblin* containGoblin = NULL;
	Hobgoblin* containHobgoblin = NULL;
	Ogre* containOgre = NULL;
	Troll* containTroll = NULL;
	TreasureHunter* containHunter = NULL;
	Dragon* containDragon = NULL;
	Item containItem; 


public:
	Location();
	Location(string name);
	Location(string name, string description,Item item);
	~Location();
	void setLocationName(string name); 
	void setLocationDescription(string description); 
	void insertLocationExits(string exit); 
	void setLocationGoblin(Goblin* golbin); 
	void setLocationHobgoblin(Hobgoblin* hobgoblin);
	void setLocationOgre(Ogre* ogre);
	void setLocationTroll(Troll* troll);
	void setLocationHunter(TreasureHunter* th);
	void setLocationDragon(Dragon* dragon);
	void setLocationItem(Item item); 
	void setLocationExamined();

	void getDetails();


	string getLocationName();
	string getLocationDescription();
	void getLocationExits();
	Goblin* getLocationGoblin();
	Hobgoblin* getLocationHobgoblin();
	Ogre* getLocationOgre();
	Troll* getLocationTroll();
	TreasureHunter* getLocationHunter();
	Dragon* getLocationDragon();
	Item getLocationItem();
	int getAmountOfExits();
	bool isMonsterPresent();
	bool isDragonPresent();
	bool isTreasureHunterPresent();
	int getExitIndex(int mapIndex);
	void testClassName();
	bool isLocationExamined();
	
	
};

#endif