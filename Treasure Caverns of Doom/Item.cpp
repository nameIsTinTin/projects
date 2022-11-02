//#include "MonsterENUM.h"
#include "Item.h"

/*
The Item class has ran into difficulties recognising anything involving strings in its methods. 
This has prevented a few implementation that involves providing the item a name and description of what 
it is. This will be fixed later on, and every item that a mob holds will just contains attributes and no special
effects as gold and artefacts will be an extension of Item in part B.

Part B's comment: This is the parent class for Artefact and the gold is inside the Item class as there 
doesn't seem to be need to have a whole new class for it when we only need one of its attributes to iteract with 
*/



Item::Item() {
	itemName = "Misc.";
	healHealth = 0;
	dealDamage = 0;
	defenseAmount = 0;
	oilAmount = 0;
	valueAmount = 0; 
	itemProperty = ITEM;
};

Item::Item(string name) {
	itemName = name;
}

Item::Item(string name, int value) {
	itemName = name; 
	valueAmount = value;
}

Item::~Item(){}

void Item::setItemHealing(int heal) { healHealth = heal; }
void Item::setItemName(string name) { itemName = name; }
void Item::setItemDamage(int dmg) { dealDamage = dmg; }
void Item::setItemDescription(string description) { itemDescription = description; }
void Item::setItemDefense(int def) { defenseAmount = def; }
void Item::setItemOil(int oil) { oilAmount = oil; }
void Item::setItemValue(int value) { valueAmount = value; }
void Item::setItemUsage(int usage) { itemUsage = usage; }
void Item::setItemType(int itemType) {
	switch (itemType) {
	case(0):
		itemProperty = ITEM;
		break;
	case(1):
		itemProperty = WEAPON;
		break;
	case(2):
		itemProperty = ARMOUR;
		break;
	case(3):
		itemProperty = ARTEFACT;
		break;
	}
}

void Item::getDetails() {
	cout << "\n";
	cout << "Item Name: " << itemName << "\n";

	if (itemName == "Provisions") {
		cout << "Item Healing Capability: " << healHealth << "\n";	
		cout << "Amount Remaining: " << itemUsage << endl;
	}
	if (itemName == "Lantern") {
		cout << "Item Oil Amount: " << oilAmount << endl;
	}
	if (itemName == "Coin") {
		cout << "Item Value Amount: " << valueAmount << endl;
	}

	if (itemProperty == WEAPON) {
		cout << "Item Property: WEAPON" << endl; 
		cout << "Item Damage: " << getItemDamage() << endl;
	}

	if (itemProperty == ARMOUR) {
		cout << "Item Property: ARMOUR" << endl; 
		cout << "Item Defense: " << getItemDefense() << endl;
	}

	cout << "\n";
}


string Item::getItemDescription() {return itemDescription;}
string Item::getItemName() { return itemName; }
int Item::getItemHealing() { return healHealth; }
int Item::getItemDamage() { return dealDamage; }
int Item::getItemDefense() { return defenseAmount; }
int Item::getItemOil() { return oilAmount; }
int Item::getItemValue() { return valueAmount; }
int Item::getItemUsage() { return itemUsage; }
string Item::getItemType() {
	if (itemProperty == ITEM) { return "Item"; }
	if (itemProperty == WEAPON) { return "Weapon"; }
	if (itemProperty == ARMOUR) { return "Armour"; }
	if (itemProperty == ARTEFACT) { return "Artefact"; }
	else {
		return "Item does not have a type.";
	}
}


//void Item::testClassName() {
//	
//	Item defaultItem = Item::Item();
//	cout << "Default Item Details: " << "\n";
//	defaultItem.getDetails();
//
//	cout << "\n";
//
//	Item overloadedItem = Item::Item(1, 1, 1);
//	cout << "Overloaded Item Details: " << "\n";
//	overloadedItem.getDetails();
//
//	cout << "\n";
//}