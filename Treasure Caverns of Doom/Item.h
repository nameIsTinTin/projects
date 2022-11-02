#ifndef ITEM_H
#define ITEM_H

#include <string> 
#include <iostream>
#include <vector> 

using namespace std;

class Item {

protected:
	enum itemType { ITEM, WEAPON, ARMOUR, ARTEFACT };
	string itemName;
	string itemDescription;
	int healHealth = NULL;
	int dealDamage = NULL;
	int defenseAmount = NULL;
	int valueAmount = NULL;
	int oilAmount = NULL;
	int itemUsage = NULL;
	bool anActualItem = true;
	itemType itemProperty;
	

public: 
	
	Item();
	Item(string name);
	Item(string name, int value);
	~Item();
	void setItemName(string name);
	void setItemHealing(int heal);
	void setItemDamage(int dmg);
	void setItemDefense(int def);
	void setItemExistence(bool exist);
	void setItemOil(int oil);
	void setItemValue(int value);
	void setItemUsage(int usage);
	void setItemType(int itemType);
	void setItemDescription(string description);

	string getItemDescription();
	string getItemName();
	int getItemHealing();
	int getItemDamage();
	int getItemDefense();
	bool getItemExistence();
	int getItemOil(); 
	int getItemValue();
	int getItemUsage();
	string getItemType();

	virtual void getDetails();
	void testClassName();
};

#endif