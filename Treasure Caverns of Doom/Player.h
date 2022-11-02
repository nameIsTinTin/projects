#ifndef PLAYER_H
#define PLAYER_H

#include <string> 
#include <iostream>
#include <vector> 
#include "Item.h"


using namespace std;

class Player {

private:
	//player attributes 
	string playerName;
	int playerHealth;
	int playerMaxHealth;
	int playerAttack;
	int playerDamage;
	int playerDefense;
	int playerLuck;
	vector<Item*> playerInventory;
	int playerCarryCapacity;
	//Item playerInventory[12];

public:
	Player();
	Player(int hp, int attack, int defense, int luck);
	~Player();
	void setPlayerName();
	void setPlayerHP(int hp);
	void setPlayerMaxHP(int hp);
	void setPlayerAttack(int atk);
	void setPlayerDamage(int dmg);
	void setPlayerDefense(int def);
	void setPlayerLuck(int luck);
	void addItemIntoInventory(Item* item);
	void addPlayerMoney(int value);
	void addPlayerDamage(int value); 
	void addPlayerDefense(int value);
	void getDetails();
	void displayInventory();
	void testClassName();
	vector<Item*> getInventory();

	string getPlayerName();
	int getPlayerHP();
	int getPlayerMaxHP();
	int getPlayerAttack();
	int getPlayerDamage();
	int getPlayerDefense();
	int getPlayerLuck();
	int getPlayerMoney();
	Item* getInventoryIndex(int index);
	//void addPlayerInventory(Item itemType);
};

#endif
