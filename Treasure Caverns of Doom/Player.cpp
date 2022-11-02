
#include "Player.h"

/*
This will be the Player where the user can choose their own name and as they fight, 
the following mutator and accessor methods will be used to grow their character. However, this 
will be strongly implemented later on in Part B.

Part B's comment: The Player's stats is interacted with all over in the game, 
for every equipment they pick up, movement, and fight. The Player class heavily 
interacts with the monsters in the game.
*/

Player::Player(){
	setPlayerName();
	setPlayerHP((rand() % 12 + 4) + 12);
	setPlayerMaxHP(getPlayerHP());
	setPlayerAttack(getPlayerHP() / 5);
	setPlayerDamage(getPlayerAttack() / 3);
	setPlayerDefense(getPlayerAttack() / 2);
	setPlayerLuck((rand() % 6 + 2) + 6);
	}

Player::Player(int hp, int attack, int defense, int luck){
	setPlayerName();
	setPlayerHP(hp);
	setPlayerAttack(attack);
	setPlayerDefense(defense);
	setPlayerLuck(luck);
}


Player::~Player(){}

void Player::setPlayerName() { 
	string newName;
	cout << "Enter player's name: ";
	cin >> newName;
	playerName = newName; 
}

void Player::setPlayerHP(int hp) { playerHealth = hp; }
void Player::setPlayerAttack(int atk) { playerAttack = atk; }
void Player::setPlayerDamage(int dmg) { playerDamage = dmg; }
void Player::setPlayerDefense(int def) { playerDefense = def; }
void Player::setPlayerLuck(int luck) { playerLuck = luck; }
void Player::setPlayerMaxHP(int hp) { playerMaxHealth = hp; }
void Player::addPlayerMoney(int value) {
	for (int i = 0; i < playerInventory.size(); i++) {
		if (playerInventory[i]->getItemName() == "Coin") {
			playerInventory[i]->setItemValue(playerInventory[i]->getItemValue() + value); 
		}
	}
}
void Player::addPlayerDamage(int value) {playerDamage += value;}

void Player::addPlayerDefense(int value) { playerDefense += value; }



void Player::addItemIntoInventory(Item* item) {
	playerInventory.push_back(item);
	playerCarryCapacity++;
}

void Player::getDetails() {
	cout << endl;
	cout << "~~~~~~~ YOUR CURRENT STATS ~~~~~~~" << endl;
	cout << "Player's Name: " << playerName << "\n";
	cout << "Player's Health: " << playerHealth << " / " << getPlayerMaxHP() << "\n";
	cout << "Player's Attack: " << playerAttack << "\n";
	cout << "Player's Damage: " << playerDamage << "\n";
	cout << "Player's Defense: " << playerDefense << "\n";
	cout << "Player's Luck: " << playerLuck << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void Player::displayInventory() {
	cout << "\n"; 
	cout << "///////////////////////////////////" << "\n\n";
	for (int i = 0; i < playerCarryCapacity; i++) {
		cout << "Item " << i + 1 << ": "; 
		playerInventory[i]->getDetails();
		cout << "///////////////////////////////////" << "\n\n";
	}
}

vector<Item*> Player::getInventory() { return playerInventory; }
Item* Player::getInventoryIndex(int index) { return playerInventory[index]; }
string Player::getPlayerName() { return playerName; }
int Player::getPlayerHP() { return playerHealth; }
int Player::getPlayerAttack() { return playerAttack; }
int Player::getPlayerDamage() { return playerDamage; }
int Player::getPlayerDefense() { return playerDefense; }
int Player::getPlayerLuck() { return playerLuck; }
int Player::getPlayerMaxHP() { return playerMaxHealth; }

void Player::testClassName() {

	Player defaultPlayer = Player::Player();
	cout << "Default Player Details: " << "\n";
	defaultPlayer.getDetails();

	cout << "\n";

	Player overloadedPlayer = Player::Player(1, 1, 1, 1);
	cout << "Overloaded Player Details: " << "\n";
	overloadedPlayer.getDetails();

}
