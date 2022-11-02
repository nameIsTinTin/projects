#include "Location.h"
#include "Monster.h"

/*
As of Part A, the format of location inside the text file is still unknown which is why 
the details of the location is mostly string. Upon part B with certainty of how location is formatted, 
this may or may not be updated accordingly.

As of Part B, the major detail that comes into play when creating Location is being able to 
set a Monster inside specific locations. This allows appropriate messages to appear and 
allow appropriate interactions.
*/
Location::Location(){
	locationName = "Dummy Location Name";
	locationDescription = "Dummy Location Description";
	containItem = Item::Item();
	
}


Location::Location(string name, string description, Item item) {
	locationName = name;
	locationDescription = description;
	containItem = item;
}

Location::~Location(){}
void Location::setLocationName(string name) { locationName = name; }
void Location::setLocationDescription(string description) { locationDescription = description; }
void Location::insertLocationExits(string exit) { locationExits.push_back(exit); }
void Location::setLocationGoblin(Goblin* goblin) { containGoblin = goblin; }
void Location::setLocationHobgoblin(Hobgoblin* hobgoblin) { containHobgoblin = hobgoblin; }
void Location::setLocationOgre(Ogre* ogre) { containOgre = ogre; }
void Location::setLocationTroll(Troll* troll) { containTroll = troll; }
void Location::setLocationHunter(TreasureHunter* th) { containHunter = th; }
void Location::setLocationDragon(Dragon* dragon) { containDragon = dragon; }
void Location::setLocationItem(Item item) { containItem = item; }
void Location::setLocationExamined() { locationExamined = true; }



void Location::getDetails() {
	cout << "\n";
	cout << "Location Name: " << locationName << "\n"; 
	cout << "Location Description:" << locationDescription << "\n";
	if (isMonsterPresent()) {
		if (containGoblin != NULL) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			containGoblin->getDetails();
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		if (containHobgoblin != NULL) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			containHobgoblin->getDetails();
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		if (containOgre != NULL) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			containOgre->getDetails();
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		if (containTroll != NULL) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			containTroll->getDetails();
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		if (containDragon != NULL) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			containDragon->getDetails();
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
	}
	
}

string Location::getLocationName() { return locationName; }
string Location::getLocationDescription() { return locationDescription; }
Goblin*  Location::getLocationGoblin() { return containGoblin; }
Hobgoblin* Location::getLocationHobgoblin() { return containHobgoblin; }
Ogre* Location::getLocationOgre() { return containOgre; }
Troll* Location::getLocationTroll() { return containTroll; }
TreasureHunter* Location::getLocationHunter() { return containHunter; }
Dragon* Location::getLocationDragon() { return containDragon; }
Item Location::getLocationItem() { return containItem; }
void Location::getLocationExits() {
	for (int i = 0; i < locationExits.size(); i++) {
		cout << locationExits[i] << endl;
	}
}
int Location::getAmountOfExits() { return locationExits.size(); }
int Location::getExitIndex(int mapIndex) { return stoi(locationExits[mapIndex]); }

bool Location::isMonsterPresent() {
	if (getLocationGoblin() != NULL || getLocationHobgoblin() != NULL || getLocationOgre() != NULL || getLocationTroll() != NULL) {
		return true;
	}
	return false;
}

bool Location::isTreasureHunterPresent() {
	if (getLocationHunter() != NULL) {
		return true;
	}
	return false;
}
bool Location::isDragonPresent() {
	if (getLocationDragon() != NULL) {
		return true;
	}
	return false;

}

bool Location::isLocationExamined() { return locationExamined; }
