#include "Dragon.h"

/*
* The dragon class for now is a class of its own that guarantees itself an artefact upon being slain. 

*/

Dragon::Dragon() { 
	setDragonName("Cuddles"); 
	setDragonLevel(5); 
	setDragonHP(getDragonLevel() * (rand() % 8 + 6));
	monsterMaxHealth = getDragonHP();
	setDragonAttack(getDragonLevel() + (rand() % 10 + 6));
	setDragonDefense(getDragonLevel() + (rand() % 12 + 6));
	setDragonLocation("Nowhere");
}

Dragon::Dragon(string name, int level, int hp, int attack, int defense, string location, Item item) { 
	setDragonName(name);
	setDragonLevel(level);
	setDragonHP(hp);
	setDragonAttack(attack);
	setDragonDefense(defense);
	setDragonLocation(location);
	setDragonItem(item);
}

Dragon::~Dragon(){}
void Dragon::setDragonItem(Item loot) { dragonItem = loot; }
void Dragon::setDragonName(string newName) { dragonName = newName; }
void Dragon::setDragonHP(int hp) { dragonHealth = hp; }
void Dragon::setDragonAttack(int atk) { dragonAttack = atk; }
void Dragon::setDragonDefense(int def) { dragonDefense = def; }
void Dragon::setDragonLevel(int level) { dragonLevel = level; }
void Dragon::setDragonLocation(string location) { dragonLocation = location; }
//The following two will be randomised in Part B during a fight with the player
void Dragon::setDragonClawAttack() { dragonDamage = dragonLevel + (rand() % 6 + 4); }
void Dragon::setDragonFireAttack() { dragonDamage = dragonLevel * (rand() % 3 + 2); }

void Dragon::getDetails(){
	cout << "\n"; 
	cout << "Dragon's Name: " << dragonName << "\n";
	cout << "Dragon's Level: " << dragonLevel << "\n";
	cout << "Dragon's Health: " << dragonHealth << "\n";
	cout << "Dragon's Attack: " << dragonAttack << "\n";
	cout << "Dragon's Damage: " << dragonDamage << "\n";
	cout << "Dragon's Defense: " << dragonDefense << "\n";
}


string Dragon::getDragonName() { return dragonName; }
string Dragon::getDragonLocation() { return dragonLocation; }
int Dragon::getDragonHP() { return dragonHealth; }
int Dragon::getDragonMaxHP() { return monsterMaxHealth; }
int Dragon::getDragonAttack() { return dragonAttack; }
int Dragon::getDragonDamage() { return dragonDamage; }
int Dragon::getDragonDefense() { return dragonDefense; }
int Dragon::getDragonLevel() { return dragonLevel; }
Item Dragon::getDragonItem() { return dragonItem; }


//void Dragon::testClassName() {
//	cout << "Dragon's Damage is not meant to be initialized until a fight has broken out :)" << "\n";
//	Dragon defaultDragon = Dragon::Dragon();
//	cout << "Default Dragon Details: " << "\n"; 
//	defaultDragon.getDetails(); 
//	
//	cout << "\n";
//
//	Item overloadedItem = Item::Item(1, 1, 1);
//	//overloadedItem.setItemName("Overloaded");
//	Dragon overloadedDragon = Dragon::Dragon("Overloaded", 1, 1, 1, 1, "Overloaded", overloadedItem); 
//	cout << "Overloaded Dragon Details: " << "\n"; 
//	overloadedDragon.getDetails();
//
//	cout << "\n";
//
//}