#include "Main.h"

/*
Author of Code: Tin Nguyen 

Date of Completion (for Part A): 21/09/2022 

Purpose: Designing the foundation of hack and slash game called "The Treasure Caverns of Doom"
where it contains the player fighting through a horde of mobs and collecting loot.

This contains the game logic as well as demonstrates the criteria of Part A.  
Unsure of how the tutors will mark this, but in the case where they want to call methods or access objects
within objects. Here are some notes : 

Objects like Items can only be mutated before being assigned into another object, after so, they cannot be 
mutated any further but can still be accessed. 

Items do not have names due to a problem implementing strings just for Item Class, read Item.cpp for more details.

Date of Completion (for Part B): 31/10/2022

Purpose: Built and completed from the foundations of Part A - made a hack and slash game called 
"The Treasure Caverns of Doom" which involves collecting the 5 artefacts inside the dungeon 
and slaying the dragon to win

The idea and thought process behind upon this code can be found within the PDF.


*/


void displayTextData(string filename) { //Allows the game to appear fun messages such as Fireworks, Dragons, etc....
	ifstream fileToRead(filename);
	cout << "\n";
	if (fileToRead.is_open()) {
		string line = "";
		string word;
		while (!fileToRead.eof()) {
			getline(fileToRead, line);
			cout << line << "\n";
		}
		cout << "\n";
	}
	else {
		cout << "\nFile Not Found.\n";
	}
	fileToRead.close();
} 

void storeLocationData(string filename) { //This grabs information from the textfile and assigns the read data into the Location objects
	ifstream fileToRead(filename);
	cout << "\n";
	if (fileToRead.is_open()) {
		if (filename == "locationName.txt") {
			string line = "";
			while (!fileToRead.eof()) {
				getline(fileToRead, line, ';');
				//cout << line << endl;
				locationName.push_back(line);
			}
		}
		if (filename == "locationDescription.txt") {
			string line = "";
			while (!fileToRead.eof()) {
				getline(fileToRead, line, ';');
				//cout << line << endl << endl;
				locationDescription.push_back(line);
			}
			cout << "\n";
		}
	}
	else { cout << "\nFile Not Found.\n"; }
	fileToRead.close();
	} 

void storeExitData(string filename) { //This allows the cave to shape itself by adding adjacent caves to the current iterated cave
	ifstream fileToRead(filename);
	cout << "\n";
	if (fileToRead.is_open()) {
		string line = "";
		int mapExitProvided = -1;
		while (!fileToRead.eof()) {
			if (line == "") {
				mapExitProvided++;
			}
			getline(fileToRead, line, ';');

			if (line == "x") {
				locationMap[mapExitProvided]->insertLocationExits("-1");
			}
			if (line != "" and line != "x") {
				locationMap[mapExitProvided]->insertLocationExits(line);
			}
		}
		cout << "\n";
	}
	else {
		cout << "\nFile Not Found.\n";
	}
	fileToRead.close();
}

int traverseMap(int currentLocation, int direction) { // Allows the ability to move around caves 
	if (locationMap[currentLocation]->getExitIndex(direction) == -1) {
		cout << "What am I suppose to do, run into a wall ?" << endl;
		system("PAUSE");
		system("CLS");
		return currentLocation;
	}
	currentLocation = locationMap[currentLocation]->getExitIndex(direction);
	system("CLS");
	return currentLocation;
}

void examineLocation(Player* player, int mapindex) { //Allows the player to inspect the cave's details
	int playerLuck = player->getPlayerLuck();
	int determinedLoot = rand() % 100; 
	if (locationMap[mapindex]->isLocationExamined() == true) {
		cout << "Nothing but rocks here." << endl;
	}
	if (30 + playerLuck >= determinedLoot && locationMap[mapindex]->isLocationExamined() == false) {
		int foundCoins = rand() % 12 + 6;
		player->addPlayerMoney(foundCoins);
		cout << "You have found: " << foundCoins << " coins" << endl;
		cout << "Your new total amount: " << player->getInventoryIndex(1)->getItemValue() << endl;
		
	}
	else if(locationMap[mapindex]->isLocationExamined() == false) {
		cout << "Found...dirt." << endl;
	}
	int oilUsed = rand() % 4 + 2; 
	player->getInventoryIndex(0)->setItemOil(player->getInventoryIndex(0)->getItemOil() - oilUsed);
	cout << "Oil Used: " << oilUsed << endl;
	cout << "Remaining Oil Before Complete Darkness: " << player->getInventoryIndex(0)->getItemOil() << endl;
	locationMap[mapindex]->setLocationExamined();
	
}
void displayMap(int mapIndex) { //Shows the adjacent areas of the current cave 
	locationMap[mapIndex]->getDetails(); 
	cout << "Possible exits: " << endl;
	for (int i = 0; i < locationMap[mapIndex]->getAmountOfExits(); i++) {
		if (i == 0) { cout << "[N]: ";}
		if (i == 1) { cout << "[E]: "; }
		if (i == 2) { cout << "[S]: "; }
		if (i == 3) { cout << "[W]: "; }
		if (locationMap[mapIndex]->getExitIndex(i) == -1) { cout << " N/A" << endl; }
		else { cout << locationMap[locationMap[mapIndex]->getExitIndex(i)]->getLocationName() << endl; }
	}
	system("PAUSE");
	system("CLS");
	cout << endl;
}
void displayLocationMessage(int mapIndex) { //This provides the user interface the idea of what's going on inside the cave 
	                                        // depending on the situation they are in
	cout << "/////////////////TREASURE CAVERNS OF DOOM/////////////////" << endl;
	if (mapIndex == 0) {
		cout << "               You stumbled into the entrance             " << endl;
	}
	else if (mapIndex != 0) {
		if (locationMap[mapIndex]->isMonsterPresent()) {
			cout << "               A hidden presence lurks around             " << endl;
		}
		if (locationMap[mapIndex]->isTreasureHunterPresent()) {
			cout << "************    TREASURE HUNTER ALERT    ************" << endl;
		}
	}
	if (locationMap[mapIndex]->getExitIndex(0) != -1) {
		cout << "                            [N]                           " << endl;
	}
	cout << "                                                          " << endl;
	if (locationMap[mapIndex]->getExitIndex(3) != -1) {
		cout << "                    [W]     MOVE";
		if (locationMap[mapIndex]->getExitIndex(1) != -1) {
			cout << "     [E]                  " << endl;
		}
	}
	if (locationMap[mapIndex]->getExitIndex(1) != -1 && locationMap[mapIndex]->getExitIndex(3) == -1) {
		cout << "                            MOVE     [E]                  " << endl;
	}
	cout << "                                                          " << endl;
	cout << "                                                          " << endl;
	if (locationMap[mapIndex]->getExitIndex(2) != -1)
	cout << "                            [S]                           " << endl;
	cout << "                                                          " << endl;
	cout << "[P]ROVISION [I]NVENTORY [T]AKE [D]ROP [M]AP [H]ELP [Q]UIT " << endl;
	if (locationMap[mapIndex]->isMonsterPresent() || locationMap[mapIndex]->isTreasureHunterPresent()) {
		cout << "            [C]HECK STATS         [A]TTACK                " << endl;
	}
	if (locationMap[mapIndex]->isDragonPresent() && amountArtefactTracker.size() >= 4) {
		cout << "                    [C]HECK STATS                        " << endl;
		cout << " [A]LL THAT'S LEFT BETWEEN ME AND THE END IS THIS BEAST  " << endl;
	}
	if (!locationMap[mapIndex]->isMonsterPresent() && !locationMap[mapIndex]->isTreasureHunterPresent()) {
		cout << "            [C]HECK STATS         E[X]AMINE               " << endl;
	}
	if (mapIndex == 0) {
		cout << "               [A]UGMENT BODY PARTS      " << endl;
		if (amountArtefactTracker.size() == 5) {
			cout << "               [V]ICTORY?" << endl;
		}
	}
}

bool moneyChecker(Player* player, int amount){ //Checks if the player has sufficient funds for an interaction
	if (player->getInventoryIndex(1)->getItemValue() < amount) { return false; }
	else { return true; }
}
void shop(Player* player) { //This is the store interface where players can exchange their gold coins for their respective purchase
	
	int playerChoice = 99;
	while (playerChoice != 7) {
		displayTextData("shopMessage.txt");
		cin >> playerChoice;
		switch (playerChoice) {
		case(1):
			if (!moneyChecker(player, 4)) {
				cout << "You don't have enough money." << endl;
				
			}

			if (moneyChecker(player, 4)) {
				player->addPlayerMoney(-4);
				cout << "You paid 4 gold coins." << endl;
				player->setPlayerAttack(player->getPlayerAttack() + 2);
				player->getDetails();
				
			}
			system("PAUSE");
			system("CLS");
			break;

		case(2):
			if (!moneyChecker(player, 4)) {
				cout << "You don't have enough money." << endl;
				
			}

			if (moneyChecker(player, 4)) {
				player->addPlayerMoney(-4);
				cout << "You paid 4 gold coins." << endl;
				player->setPlayerDamage(player->getPlayerDamage() + 1);
				player->getDetails();
				
			}
			system("PAUSE");
			system("CLS");
			break;
		case(3):
			if (!moneyChecker(player, 4)) {
				cout << "You don't have enough money." << endl;
				system("PAUSE");
			}

			if (moneyChecker(player, 4)) {
				player->addPlayerMoney(-4);
				cout << "You paid 4 gold coins." << endl;
				player->setPlayerDefense(player->getPlayerDefense() + 1);
				player->getDetails();
				
			}
			system("PAUSE");
			system("CLS");
			break;
		case(4):
			if (!moneyChecker(player, 4)) {
				cout << "You don't have enough money." << endl;
				
			}

			if (moneyChecker(player, 4)) {
				player->addPlayerMoney(-4);
				cout << "You paid 4 gold coins." << endl;
				player->getInventoryIndex(0)->setItemOil(player->getInventoryIndex(0)->getItemOil() + 16);
				player->getInventoryIndex(0)->getDetails();
				
			}
			system("PAUSE");
			system("CLS");
			break;
		case(5):
			if (!moneyChecker(player, 5)) {
				cout << "You don't have enough money." << endl;
				
			}

			if (moneyChecker(player, 5)) {
				player->addPlayerMoney(-5);
				cout << "You paid 5 gold coins." << endl;
				for (int i = 0; i < player->getInventory().size(); i++) {
					if (player->getInventoryIndex(i)->getItemName() == "Provisions") {
						player->getInventoryIndex(i)->setItemUsage(
							player->getInventoryIndex(i)->getItemUsage() + 1);

					}
					if (i == player->getInventory().size() - 1) {
						Item* test4 = new Item("Provisions");
						test4->setItemType(0);
						int c = rand() % 10;
						if (c < 5) { c += 5; }
						test4->setItemHealing(c);
						test4->setItemUsage(1);
						player->getInventory().push_back(test4);
					}
				}
			}
			system("PAUSE");
			system("CLS");
			break;

		case(6):
			if (!moneyChecker(player, 8)) {
				cout << "You don't have enough money." << endl;
				system("PAUSE");
			}

			if (moneyChecker(player, 8)) {
				player->addPlayerMoney(-8);
				cout << "You paid 8 gold coins." << endl;
				gambleStats(player);
			}
			system("PAUSE");
			system("CLS");
			break;
		case(7):
			system("CLS");
			break;
		}
	}

}
void eatProvision(Player* player){ // Looks through the inventory for food to eat

	if (player->getPlayerMaxHP() == player->getPlayerHP()) { 
		cout << "Perhaps I should save it instead..." << endl; }

	if (player->getPlayerMaxHP() > player->getPlayerHP()) {
		for (int i = 0; i < player->getInventory().size(); i++) {
			if (player->getInventoryIndex(i)->getItemName() == "Provisions" &&
				player->getInventoryIndex(i)->getItemUsage() > 0) {
				if (player->getPlayerMaxHP() - player->getPlayerHP() > player->getInventoryIndex(i)->getItemHealing()) {
					player->setPlayerHP(player->getPlayerHP() + player->getInventoryIndex(i)->getItemHealing());
					player->getInventoryIndex(i)->setItemUsage(
						player->getInventoryIndex(i)->getItemUsage() - 1);
					cout << "HP: " << player->getPlayerHP() << " / " << player->getPlayerMaxHP() << endl;
				}
				else if (player->getPlayerMaxHP() - player->getPlayerHP() <= player->getInventoryIndex(i)->getItemHealing()) {
					player->setPlayerHP(player->getPlayerMaxHP());
					player->getInventoryIndex(i)->setItemUsage(
						player->getInventoryIndex(i)->getItemUsage() - 1);
					cout << "HP: " << player->getPlayerHP() << " / " << player->getPlayerMaxHP() << endl;
				}
				if (player->getInventoryIndex(i)->getItemUsage() == 0) {
					player->getInventory().at(i)->~Item();
				}
			}
		}
	}
	}
void gambleStats(Player* player) { //Allows the player if they're feeling lucky to gamble their stats for money
	int gambleNumber = rand() % 8;
	if (gambleNumber <= 3) { displayTextData("wonGamble.txt"); }
	else if (gambleNumber > 3) { displayTextData("lostGamble.txt"); }
	int statBoost = rand() % 4 + 1;
	switch (gambleNumber) {
	case(0):
		player->setPlayerAttack(player->getPlayerAttack() + statBoost);
		cout << "Attack (+" << statBoost << ")" << endl;
		system("PAUSE");
		break;
	case(1):
		player->setPlayerDefense(player->getPlayerDefense() + statBoost);
		cout << "Defense (+" << statBoost << ")" << endl;
		system("PAUSE");
		break;
	case(2):
		player->setPlayerDamage(player->getPlayerDamage() + statBoost);
		cout << "Damage (+" << statBoost << ")" << endl;
		system("PAUSE");
		break;
	case(3):
		player->setPlayerLuck(player->getPlayerLuck() + statBoost);
		cout << "Luck (+" << statBoost << ")" << endl;
		system("PAUSE");
		break;
	case(4):
		player->setPlayerAttack(player->getPlayerAttack() - statBoost);
		cout << "Attack (-" << statBoost << ")" << endl;
		system("PAUSE");
		break;
	case(5):
		player->setPlayerDefense(player->getPlayerDefense() - statBoost);
		cout << "Defense (-" << statBoost << ")" << endl;
		system("PAUSE");
		break;
	case(6):
		player->setPlayerDamage(player->getPlayerDamage() - statBoost);
		cout << "Damage (-" << statBoost << ")" << endl;
		system("PAUSE");
		break;
	case(7):
		player->setPlayerLuck(player->getPlayerLuck() - statBoost);
		cout << "Luck (-" << statBoost << ")" << endl;
		system("PAUSE");
		break;
	}
}
void initiateArtefacts(string filename) { //Spawns the artefacts into the world


	ifstream fileToRead(filename);
	cout << "\n";
	int track = 0;
	if (fileToRead.is_open()) {
		if (filename == "artefactName.txt") {
			string line = "";
			while (!fileToRead.eof()) {
				getline(fileToRead, line, ';');
				artefactTracker[track]->setItemName(line);
				track++;
			}
		}
		if (filename == "artefactDescription.txt") {
			string line = "";
			while (!fileToRead.eof()) {
				getline(fileToRead, line, ';');
				artefactTracker[track]->setItemDescription(line);
				track++;
			}
			cout << "\n";
		}
	}
	else { cout << "\nFile Not Found.\n"; }
	fileToRead.close();
	}


Player* initializeGame(Player* player) { //Creates the player and mobs inside of the cave 

	
	system("PAUSE");

	for (int i = 0; i < locationName.size(); i++) {
		Location* a = new Location();
		a->setLocationName(locationName[i]);
		a->setLocationDescription(locationDescription[i]);
		if (5 >= i && i > 0) {
			Goblin* b = new Goblin();
			a->setLocationGoblin(b);
		}
		if (10 > i && i >= 6) {
			Hobgoblin* b = new Hobgoblin();
			a->setLocationHobgoblin(b);
		}
		if (14 > i && i >= 10) {
			Ogre* b = new Ogre();
			a->setLocationOgre(b);
		}
		if (20 >= i && i >= 14) {
			Troll* b = new Troll();
			a->setLocationTroll(b);
		}
		if (i == 21) {
			Dragon* b = new Dragon();
			a->setLocationDragon(b);
		}

		locationMap.push_back(a);
	}

	Item* test = new Item("Lantern");
	test->setItemOil(100);
	test->setItemType(0);
	Item* test2 = new Item("Coin", rand() % 12 + 6);
	test2->setItemType(0);
	Item* test3 = new Item("Map");
	test3->setItemType(0);
	Item* test4 = new Item("Provisions"); 
	test4->setItemType(0);
	int c = rand() % 10;
	if (c < 5) { c += 5; }
	test4->setItemHealing(c);
	test4->setItemUsage(4);
	Item* test5 = new Item(listOfSwords[rand() % 11]); 

	////////////////////////////////////////////////////////////
	test5->setItemDamage(4);
	test5->setItemType(1);
	player->addPlayerDamage(4);
	//player->setPlayerAttack(4);
	/////////////////////////////////////////////////////////////


	player->addItemIntoInventory(test);
	player->addItemIntoInventory(test2);
	player->addItemIntoInventory(test3); 
	player->addItemIntoInventory(test4);
	player->addItemIntoInventory(test5);

	for (int i = 0; i < 5; i++) {
		Item* a = new Artefact();
		if (i == 0) { a->setItemType(1); a->setItemDamage(8); }
		if (i == 1) { a->setItemType(2); a->setItemDefense(12); }
		if (i == 2) { a->setItemType(2); a->setItemDefense(12); }
		if (i == 3) { a->setItemType(0); a->setItemHealing(-999); }
		if (i == 4) { a->setItemType(3);}
		artefactTracker.push_back(a);
	}
	initiateArtefacts("artefactName.txt");
	initiateArtefacts("artefactDescription.txt");

	for (int i = 0; i < artefactTracker.size(); i++) {
		artefactTracker[i]->getDetails();
	}
	
	
	cout << "\n\n" << "~~~~~~~ YOUR CURRENT ITEMS ~~~~~~~";

	player->displayInventory();

	system("PAUSE");
	system("CLS");

	return player;
}

void battleGoblin(Player* player, Goblin* goblin, int mapindex) { //The interface when fighting against a Goblin
	int rounds = 0;
	while (player->getPlayerHP() > 0 && goblin->getGoblinHP() > 0 && rounds < 12) {
		cout << "/////////////////TREASURE CAVERNS OF DOOM/////////////////" << endl;
		int a = player->getPlayerAttack() + (rand() % (11 - 2) + 2);
		cout << player->getPlayerName() << "'s Attack: " << a << endl;
		int b = goblin->getGoblinAttack() + (rand() % (11 - 2) + 2);
		cout << goblin->getGoblinName() << "s Attack : " << b << endl;

		if (a > b) {
			cout << player->getPlayerName() << listOfActions[rand() % 20] << goblin->getGoblinName() << endl;
			int actualDamage = player->getPlayerDamage() - goblin->getGoblinDefense();
			if (actualDamage > 0) {
				goblin->setGoblinHP(goblin->getGoblinHP() - actualDamage);
			}
			cout << player->getPlayerName() << " inflicted " << actualDamage << " damage" << endl;
			cout << goblin->getGoblinName() << "'s health: " << goblin->getGoblinHP() << " / " << goblin->getGoblinMaxHP() << endl;
		}
		if (b > a) {
			cout << goblin->getGoblinName() << listOfActions[rand() % 20] << player->getPlayerName() << endl;
			int actualDamage = goblin->getGoblinDamage() - player->getPlayerDefense();
			if (actualDamage > 0){
				player->setPlayerHP(player->getPlayerHP() - actualDamage);
			}
			cout << goblin->getGoblinName() << " inflicted " << actualDamage << " damage" << endl;
			cout << player->getPlayerName() << "'s health: " << player->getPlayerHP() << " / " << player->getPlayerMaxHP() << endl;
		}
		if (a == b) {
			cout << "You both clash weapons" << endl;
		}
		rounds++;
		if (rounds == 12) {
			cout << "This fight has gone on for too long, I better retreat for now.." << endl;
		}
		cout << "\n\n"; 
		system("PAUSE");
	}
	if (player->getPlayerHP() <= 0) {
		displayTextData("deathScreen.txt");
		system("PAUSE");
		exit(0);
	}

	if (goblin->getGoblinHP() <= 0) {
		goblin->~Goblin();
		delete goblin;
		locationMap[mapindex]->setLocationGoblin(NULL);
		goblinDropLoot(player, 40);
		system("PAUSE");

	}
}
void battleHobgoblin(Player* player, Hobgoblin* hobgoblin, int mapindex) { //Interface for fighting a Hobgoblin
	int rounds = 0;
	while (player->getPlayerHP() > 0 && hobgoblin->getHobgoblinHP() > 0 && rounds < 12) {
		cout << "/////////////////TREASURE CAVERNS OF DOOM/////////////////" << endl;
		int a = player->getPlayerAttack() + (rand() % (11 - 2) + 2);
		cout << player->getPlayerName() << "'s Attack: " << a << endl;
		int b = hobgoblin->getHobgoblinAttack() + (rand() % (11 - 2) + 2);
		cout << hobgoblin->getHobgoblinName() << "s Attack : " << b << endl;

		if (a > b) {
			cout << player->getPlayerName() << listOfActions[rand() % 20] << hobgoblin->getHobgoblinName() << endl;
			int actualDamage = player->getPlayerDamage() - hobgoblin->getHobgoblinDefense();
			if (actualDamage > 0) {
				hobgoblin->setHobgoblinHP(hobgoblin->getHobgoblinHP() - actualDamage);
			}
			cout << player->getPlayerName() << " inflicted " << actualDamage << " damage" << endl;
			cout << hobgoblin->getHobgoblinName() << "'s health: " << hobgoblin->getHobgoblinHP() << " / " << hobgoblin->getHobgoblinMaxHP() << endl;
		}
		if (b > a) {
			cout << hobgoblin->getHobgoblinName() << listOfActions[rand() % 20] << player->getPlayerName() << endl;
			int actualDamage = hobgoblin->getHobgoblinDamage() - player->getPlayerDefense();
			if (actualDamage > 0) {
				player->setPlayerHP(player->getPlayerHP() - actualDamage);
			}
			cout << hobgoblin->getHobgoblinName() << " inflicted " << actualDamage << " damage" << endl;
			cout << player->getPlayerName() << "'s health: " << player->getPlayerHP() << " / " << player->getPlayerMaxHP() << endl;
		}
		if (a == b) {
			cout << "You both clash weapons" << endl;
		}
		rounds++;
		if (rounds == 12) {
			cout << "This fight has gone on for too long, I better retreat for now.." << endl;
		}
		cout << "\n\n";
		system("PAUSE");
	}
	if (player->getPlayerHP() <= 0) {
		displayTextData("deathScreen.txt");
		system("PAUSE");
		exit(0);
	}

	if (hobgoblin->getHobgoblinHP() <= 0) {
		hobgoblin->~Hobgoblin();
		delete hobgoblin;
		locationMap[mapindex]->setLocationHobgoblin(NULL);
		goblinDropLoot(player, 50);
		int randomiser = rand() % 100;
		if (randomiser <= 30 && amountHunterTracker.size() < 3) {
			TreasureHunter* uglyman = new TreasureHunter();
			locationMap[mapindex]->setLocationHunter(uglyman);
			cout << "Uh oh, I hear something..." << endl;
			amountHunterTracker.push_back(1);
		}
		system("PAUSE");

	}

}
void battleOgre(Player* player, Ogre* ogre, int mapindex, int artefact){ //Interface when fighting an Ogre
	int rounds = 0;
	while (player->getPlayerHP() > 0 && ogre->getOgreHP() > 0 && rounds < 12) {
		cout << "/////////////////TREASURE CAVERNS OF DOOM/////////////////" << endl;
		int a = player->getPlayerAttack() + (rand() % (11 - 2) + 2);
		cout << player->getPlayerName() << "'s Attack: " << a << endl;
		int b = ogre->getOgreAttack() + (rand() % (11 - 2) + 2);
		cout << ogre->getOgreName() << "s Attack : " << b << endl;

		if (a > b) {
			cout << player->getPlayerName() << listOfActions[rand() % 20] << ogre->getOgreName() << endl;
			int actualDamage = player->getPlayerDamage() - ogre->getOgreDefense();
			if (actualDamage > 0) {
				ogre->setOgreHP(ogre->getOgreHP() - actualDamage);
			}
			cout << player->getPlayerName() << " inflicted " << actualDamage << " damage" << endl;
			cout << ogre->getOgreName() << "'s health: " << ogre->getOgreHP() << " / " << ogre->getOgreMaxHP() << endl;
		}
		if (b > a) {
			cout << ogre->getOgreName() << listOfActions[rand() % 20] << player->getPlayerName() << endl;
			int actualDamage = ogre->getOgreDamage() - player->getPlayerDefense();
			if (actualDamage > 0) {
				player->setPlayerHP(player->getPlayerHP() - actualDamage);
			}
			cout << ogre->getOgreName() << " inflicted " << actualDamage << " damage" << endl;
			cout << player->getPlayerName() << "'s health: " << player->getPlayerHP() << " / " << player->getPlayerMaxHP() << endl;
		}
		if (a == b) {
			cout << "You both clash weapons" << endl;
		}
		rounds++;
		if (rounds == 12) {
			cout << "This fight has gone on for too long, I better retreat for now.." << endl;
		}
		cout << "\n\n";
		system("PAUSE");
	}
	if (player->getPlayerHP() < 0) {
		displayTextData("deathScreen.txt");
		system("PAUSE");
		exit(0);
	}

	if (ogre->getOgreHP() <= 0) {
		ogre->~Ogre();
		delete ogre;
		locationMap[mapindex]->setLocationOgre(NULL);
		ogreTrollDropLoot(player, 60, artefact, false);
		int randomiser = rand() % 100;
		if (randomiser <= 40 && amountHunterTracker.size() < 3) {
			TreasureHunter* uglyman = new TreasureHunter();
			locationMap[mapindex]->setLocationHunter(uglyman);
			cout << "Uh oh, I hear something..." << endl;
			amountHunterTracker.push_back(1);
		}
		system("PAUSE");
	}
}
void battleTroll(Player* player, Troll* troll, int mapindex, int artefact){ //Interface when fighting a Troll
	int rounds = 0;
	while (player->getPlayerHP() > 0 && troll->getTrollHP() > 0 && rounds < 12) {
		cout << "/////////////////TREASURE CAVERNS OF DOOM/////////////////" << endl;
		int a = player->getPlayerAttack() + (rand() % (11 - 2) + 2);
		cout << player->getPlayerName() << "'s Attack: " << a << endl;
		int b = troll->getTrollAttack() + (rand() % (11 - 2) + 2);
		cout << troll->getTrollName() << "s Attack : " << b << endl;

		if (a > b) {
			cout << player->getPlayerName() << listOfActions[rand() % 20] << troll->getTrollName() << endl;
			int actualDamage = player->getPlayerDamage() - troll->getTrollDefense();
			if (actualDamage > 0) {
				troll->setTrollHP(troll->getTrollHP() - actualDamage);
			}
			cout << player->getPlayerName() << " inflicted " << actualDamage << " damage" << endl;
			cout << troll->getTrollName() << "'s health: " << troll->getTrollHP() << " / " << troll->getTrollMaxHP() << endl;
		}
		if (b > a) {
			cout << troll->getTrollName() << listOfActions[rand() % 20] << player->getPlayerName() << endl;
			int actualDamage = troll->getTrollDamage() - player->getPlayerDefense();
			if (actualDamage > 0) {
				player->setPlayerHP(player->getPlayerHP() - actualDamage);
			}
			cout << troll->getTrollName() << " inflicted " << actualDamage << " damage" << endl;
			cout << player->getPlayerName() << "'s health: " << player->getPlayerHP() << " / " << player->getPlayerMaxHP() << endl;
		}
		if (a == b) {
			cout << "You both clash weapons" << endl;
		}
		rounds++;
		if (rounds == 12) {
			cout << "This fight has gone on for too long, I better retreat for now.." << endl;
		}
		cout << "\n\n";
		system("PAUSE");
	}
	if (player->getPlayerHP() < 0) {
		displayTextData("deathScreen.txt");
		system("PAUSE");
		exit(0);
	}

	if (troll->getTrollHP() <= 0) {
		troll->~Troll();
		delete troll;
		locationMap[mapindex]->setLocationTroll(NULL);
		ogreTrollDropLoot(player, 70, artefact, false);
		system("PAUSE");
	}
}
void battleDragon(Player* player, Dragon* dragon, int mapindex) { //Interface when fighting a Dragon
	bool breathedFire = false;
	int rounds = 0;
	while (player->getPlayerHP() > 0 && dragon->getDragonHP() > 0 && rounds < 12) {
		cout << "/////////////////TREASURE CAVERNS OF DOOM/////////////////" << endl;
		int a = player->getPlayerAttack() + (rand() % (11 - 2) + 2);
		cout << player->getPlayerName() << "'s Attack: " << a << endl;
		int b = dragon->getDragonAttack() + (rand() % (11 - 2) + 2);
		cout << dragon->getDragonName() << "s Attack : " << b << endl;

		if (a > b) {
			cout << player->getPlayerName() << listOfActions[rand() % 20] << dragon->getDragonName() << endl;
			int actualDamage = player->getPlayerDamage() - dragon->getDragonDefense();
			if (actualDamage > 0) {
				dragon->setDragonHP(dragon->getDragonHP() - actualDamage);
			}
			cout << player->getPlayerName() << " inflicted " << actualDamage << " damage" << endl;
			cout << dragon->getDragonName() << "'s health: " << dragon->getDragonHP() << " / " << dragon->getDragonMaxHP() << endl;
		}
		if (b > a) {
			cout << dragon->getDragonName() << listOfActions[rand() % 20] << player->getPlayerName() << endl;

			dragon->setDragonClawAttack();
			int randomDamage = rand() % 100;
			if (randomDamage < 30 && !breathedFire) {
				dragon->setDragonFireAttack();
				displayTextData("dragonFire.txt");
				breathedFire = true;
			}
			int actualDamage = dragon->getDragonDamage();
			if (actualDamage > 0) {
				player->setPlayerHP(player->getPlayerHP() - actualDamage);
			}
			cout << dragon->getDragonName() << " inflicted " << actualDamage << " damage" << endl;
			cout << player->getPlayerName() << "'s health: " << player->getPlayerHP() << " / " << player->getPlayerMaxHP() << endl;
		}
		if (a == b) {
			cout << "You both clash weapons" << endl;
		}
		rounds++;
		if (rounds == 12) {
			cout << "This fight has gone on for too long, I better retreat for now.." << endl;
		}
		cout << "\n\n";
		system("PAUSE");
	}
	if (player->getPlayerHP() < 0) {
		displayTextData("deathScreen.txt");
		system("PAUSE");
		exit(0);
	}

	if (dragon->getDragonHP() <= 0) {
		dragon->~Dragon();
		delete dragon;
		locationMap[mapindex]->setLocationDragon(NULL);
		ogreTrollDropLoot(player, 100, 4, true);
		system("PAUSE");
	}
}
void battleTreasureHunter(Player* player, TreasureHunter* hunter, int mapindex) { //Interface when fighting a Treasure Hunter
	int rounds = 0;
	while (player->getInventoryIndex(0)->getItemOil() > 0 && hunter->getMonsterHP() > 0 && rounds < 12) {
		cout << "/////////////////TREASURE CAVERNS OF DOOM/////////////////" << endl;
		int a = player->getPlayerAttack() + (rand() % (11 - 2) + 2);
		cout << player->getPlayerName() << "'s Attack: " << a << endl;
		int b = hunter->getMonsterAttack() + (rand() % (11 - 2) + 2);
		cout << hunter->getMonsterName() << "s Attack : " << b << endl;

		if (a > b) {
			cout << player->getPlayerName() << listOfActions[rand() % 20] << hunter->getMonsterName() << endl;
			int actualDamage = player->getPlayerDamage() - hunter->getMonsterDefense();
			if (actualDamage > 0) {
				hunter->setMonsterHP(hunter->getMonsterHP() - actualDamage);
			}
			cout << player->getPlayerName() << " inflicted " << actualDamage << " damage" << endl;
			cout << hunter->getMonsterName() << "'s health: " << hunter->getMonsterHP() << " / " << hunter->getMonsterMaxHP() << endl;
		}
		if (b > a) {
			cout << hunter->getMonsterName() << " swipes some of your lantern oil" << endl;
			int actualDamage = hunter->getMonsterSteal();
			player->getInventoryIndex(0)->setItemOil(player->getInventoryIndex(0)->getItemOil() - actualDamage);
			cout << hunter->getMonsterName() << " stole " << actualDamage << " amount of your lantern oil" << endl;
			cout << player->getPlayerName() << "'s remaining oil: " << player->getInventoryIndex(0)->getItemOil() << endl;
		}
		if (a == b) {
			cout << "You both clash weapons" << endl;
		}
		rounds++;
		if (rounds == 12) {
			cout << "This fight has gone on for too long, I better retreat for now.." << endl;
		}
		cout << "\n\n";
		system("PAUSE");
	}
	if (player->getPlayerHP() <= 0) {
		displayTextData("deathScreen.txt");
		system("PAUSE");
		exit(0);
	}

	if (hunter->getMonsterHP() <= 0) {
		cout << "You took: " << hunter->getMonsterWealth() << " gold coins!" << endl;
		player->addPlayerMoney(hunter->getMonsterWealth());
		hunter->~TreasureHunter();
		delete hunter;
		locationMap[mapindex]->setLocationHunter(NULL);
			
		system("PAUSE");
		}
	}

void processGame(Player* player) { //This allows the ability to interact with the environment, allowing the 
	                               //player to choose what to do 
	int currentLocation = 0;

	while (player->getInventoryIndex(0)->getItemOil() > 0) {
		int artefactTrack = amountArtefactTracker.size();

		playerTracker.push_back(currentLocation);
		displayLocationMessage(currentLocation);
		char playerChoice;
		cin >> playerChoice;
		int oilUsage = rand() % 5 + 2;
		switch (playerChoice) {
		case('N'):
			currentLocation = traverseMap(currentLocation, 0);
			player->getInventoryIndex(0)->setItemOil(player->getInventoryIndex(0)->getItemOil() - oilUsage);
			cout << "Oil Used: " << oilUsage << endl;
			cout << "Remaining Oil Before Complete Darkness: " << player->getInventoryIndex(0)->getItemOil() << endl;
			break;

		case('E'):
			currentLocation = traverseMap(currentLocation, 1);
			player->getInventoryIndex(0)->setItemOil(player->getInventoryIndex(0)->getItemOil() - oilUsage);
			cout << "Oil Used: " << oilUsage << endl;
			cout << "Remaining Oil Before Complete Darkness: " << player->getInventoryIndex(0)->getItemOil() << endl;
			break;

		case('S'):
			currentLocation = traverseMap(currentLocation, 2);
			player->getInventoryIndex(0)->setItemOil(player->getInventoryIndex(0)->getItemOil() - oilUsage);
			cout << "Oil Used: " << oilUsage << endl;
			cout << "Remaining Oil Before Complete Darkness: " << player->getInventoryIndex(0)->getItemOil() << endl;
			break;

		case('W'):
			currentLocation = traverseMap(currentLocation, 3);
			player->getInventoryIndex(0)->setItemOil(player->getInventoryIndex(0)->getItemOil() - oilUsage);
			cout << "Oil Used: " << oilUsage << endl;
			cout << "Remaining Oil Before Complete Darkness: " << player->getInventoryIndex(0)->getItemOil() << endl;
			break;

		case('Q'):
			char playerInput;
			cin >> playerInput;
			cout << "[R]ESTART" << endl;
			cout << "[Q]UIT" << endl;
			switch (playerInput) {
			case('R'):
				game();
				break;
			case('Q'):
				exit(0);
				break;
			default:
				break;
			}

		case('I'):
			player->displayInventory();
			system("PAUSE");
			system("CLS");
			break;

		case('M'):
			displayMap(currentLocation);
			break;

		case('H'):
			displayTextData("GameInstructions.txt");
			system("PAUSE");
			system("CLS");
			break;

		case('C'):
			player->getDetails();
			system("PAUSE");
			system("CLS");
			break;

		case('X'):
			if (locationMap[currentLocation]->isMonsterPresent()) {
				cout << "It's too risky with that thing lingering around, I better kill it first.." << endl;
			}
			if (!locationMap[currentLocation]->isMonsterPresent()) {
				examineLocation(player, currentLocation);
				system("PAUSE");
				system("CLS");
			}
			break;


		case('P'):
			eatProvision(player);
			system("PAUSE");
			system("CLS");
			break;

		case('V'):
			if (amountArtefactTracker.size() >= 4) {
				system("CLS");
				displayTextData("victorySpeech.txt");
				system("PAUSE");
				system("CLS");
				displayTextData("victoryFirework.txt");
				system("PAUSE");
				system("CLS");
				displayTextData("victoryFireworkBoom.txt");
				system("PAUSE");
				system("CLS");
				cout << "Your final stats and inventory : " << endl;
				player->getDetails();
				player->displayInventory();
				system("PAUSE");
				system("CLS");
				cout << "Until next time :)" << endl;
				exit(0);

			}
			system("CLS");
			break;

		case('A'):
			system("CLS");
			if (currentLocation == 0) {
				shop(player);
				break;
			}

			if (locationMap[currentLocation]->isTreasureHunterPresent()) {
				if (locationMap[currentLocation]->getLocationHunter()->getMonsterDefense() >= player->getPlayerDamage() &&
					locationMap[currentLocation]->getLocationHunter()->getMonsterAttack() - player->getPlayerAttack() >= 7){ 
					cout << "It seems like it's way too strong, I better not fight it for now..." << endl;
					system("PAUSE");
				}
				else {
					battleTreasureHunter(player, locationMap[currentLocation]->getLocationHunter(), currentLocation);
				}
			}
			if (locationMap[currentLocation]->isDragonPresent()) {
				if (locationMap[currentLocation]->getLocationDragon() != NULL) {
					bool hasAxe = false;
					bool hasChain = false;
					bool hasBoots = false;
					for (int i = 0; i < player->getInventory().size(); i++) {
						Item* current = player->getInventoryIndex(i);
						if (current->getItemName() == " Krang's Battle Axe") { hasAxe = true; }
						if (current->getItemName() == " Krang's Chainmail") { hasChain = true; }
						if (current->getItemName() == " Boots of Speed") { hasBoots = true; }

					}
					if (hasAxe && hasChain && hasBoots) {
						battleDragon(player, locationMap[currentLocation]->getLocationDragon(), currentLocation);
					}
					else if (locationMap[currentLocation]->getLocationDragon()->getDragonDefense() >= player->getPlayerDamage() &&
						locationMap[currentLocation]->getLocationDragon()->getDragonAttack() - player->getPlayerAttack() >= 7) {
						cout << "It seems like it's way too strong, I better not fight it for now..." << endl;
					}
					else {
						cout << "I'm missing some artefacts behind...perhaps it's a good idea to get them first" << endl;
					}
				}
			}


			if (locationMap[currentLocation]->isMonsterPresent()) {
				if (locationMap[currentLocation]->getLocationGoblin() != NULL) {
					if (locationMap[currentLocation]->getLocationGoblin()->getGoblinDefense() >= player->getPlayerDamage() && 
						locationMap[currentLocation]->getLocationGoblin()->getGoblinAttack() - player->getPlayerAttack() >= 7) {
						cout << "It seems like it's way too strong, I better not fight it for now..." << endl;
						system("PAUSE");
					}
					else { battleGoblin(player, locationMap[currentLocation]->getLocationGoblin(), currentLocation); }

				}
				if (locationMap[currentLocation]->getLocationHobgoblin() != NULL) {
					if (locationMap[currentLocation]->getLocationHobgoblin()->getHobgoblinDefense() >= player->getPlayerDamage() &&
						locationMap[currentLocation]->getLocationHobgoblin()->getHobgoblinAttack() - player->getPlayerAttack() >= 7) {
						cout << "It seems like it's way too strong, I better not fight it for now..." << endl;
						system("PAUSE");
					}
					else { battleHobgoblin(player, locationMap[currentLocation]->getLocationHobgoblin(), currentLocation); }

				}
				if (locationMap[currentLocation]->getLocationOgre() != NULL) {
					if (locationMap[currentLocation]->getLocationOgre()->getOgreDefense() >= player->getPlayerDamage() &&
						locationMap[currentLocation]->getLocationOgre()->getOgreAttack() - player->getPlayerAttack() >= 7) {
						cout << "It seems like it's way too strong, I better not fight it for now..." << endl;
						system("PAUSE");
					}
					else { battleOgre(player, locationMap[currentLocation]->getLocationOgre(), currentLocation, artefactTrack); }

				}
				if (locationMap[currentLocation]->getLocationTroll() != NULL) {
					if (locationMap[currentLocation]->getLocationTroll()->getTrollDefense() >= player->getPlayerDamage()&&
						locationMap[currentLocation]->getLocationTroll()->getTrollAttack() - player->getPlayerAttack() >= 7) {
						cout << "It seems like it's way too strong, I better not fight it for now..." << endl;
						system("PAUSE");
					}
					battleTroll(player, locationMap[currentLocation]->getLocationTroll(), currentLocation, artefactTrack);
				}

			}
			system("CLS");
			break;
		}
	} cout << "The darkness engulfed you." << endl;
}
				
		
void goblinDropLoot(Player* player, int probability) { //This is the event in which a lesser mob is defeated
	int dropRate = rand() % 100;
	char playerDecision = 'Z';
	if (dropRate <= probability) {
		int itemDrop = rand() % 100;
		if (itemDrop >= 50) {
			Item* randomWeapon = new Item(listOfSwords[rand() % 10]);
			randomWeapon->setItemType(1);
			int damageApplied = rand() % 4 + 1;
			randomWeapon->setItemDamage(damageApplied);
			cout << "~~~~~~~ FOUND ~~~~~~~" << endl;
			randomWeapon->getDetails();
			cout << "~~~~~~~~~~~~~~~~~~~~~" << "\n\n";
			cout << "[P]ICK UP   [L]EAVE  " << endl;
			while (playerDecision != 'P' && playerDecision != 'L') {
				cin >> playerDecision;
				if (playerDecision == 'P') {
					player->addItemIntoInventory(randomWeapon);
					player->addPlayerDamage(damageApplied);
					cout << "NEW ITEM ADDED INTO INVENTORY !" << endl;
				}
				if (playerDecision == 'L') {
					cout << "You chose to ignore it." << endl;
				}
				else if (playerDecision != 'P' && playerDecision != 'L') { cout << "Invalid action."; }
			}
		}

		if (itemDrop < 50) {
			Item* randomArmor = new Item(listOfArmor[rand() % 10]);
			randomArmor->setItemType(2);
			int defenseApplied = rand() % 3 + 1;
			randomArmor->setItemDefense(defenseApplied);
			cout << "~~~~~~~ FOUND ~~~~~~~" << endl;
			randomArmor->getDetails();
			cout << "~~~~~~~~~~~~~~~~~~~~~" << "\n\n";
			cout << "[P]ICK UP   [L]EAVE  " << endl;
			while (playerDecision != 'P' && playerDecision != 'L') {
				cin >> playerDecision;
				if (playerDecision == 'P') {
					player->addItemIntoInventory(randomArmor);
					player->addPlayerDefense(defenseApplied);
					cout << "NEW ITEM ADDED INTO INVENTORY !" << endl;
				}
				if (playerDecision == 'L') { cout << "You chose to ignore it." << endl; }

				else if (playerDecision != 'P' && playerDecision != 'L') { cout << "Invalid action.";  }
			}
		}
	}
	if (dropRate > probability) {
		cout << "Nothing good to take" << endl;
	}
	}
void ogreTrollDropLoot(Player* player, int probability, int artefact, bool isDragon) { //This is the event where a big mob has been defeated
	int dropRate = rand() % 100;
	if ((dropRate <= probability && artefact < 4)) {
		Item* a = artefactTracker[artefact];
		cout << "*************YOU FOUND*************" << endl; 
		artefactTracker[artefact]->getDetails();
		player->addItemIntoInventory(artefactTracker[artefact]);
		player->addPlayerDamage(a->getItemDamage());
		player->addPlayerDamage(a->getItemDefense());
		cout << "NEW ITEM ADDED INTO INVENTORY !" << endl;	
		amountArtefactTracker.push_back(1);
	}

	if (dropRate > probability || artefact > 4) {
		int amount = rand() % 12 + 3;
		player->addPlayerMoney(amount);
		cout << "You found : " << amount << " gold!" << endl;
	}

	if (isDragon) {
		Item* a = artefactTracker[artefact];
		cout << "*************YOU FOUND*************" << endl;
		artefactTracker[artefact]->getDetails();
		player->addItemIntoInventory(artefactTracker[artefact]);
		player->addPlayerDamage(a->getItemDamage());
		player->addPlayerDamage(a->getItemDefense());
		cout << "NEW ITEM ADDED INTO INVENTORY !" << endl;
		amountArtefactTracker.push_back(1);
		cout << "YOU HAVE DEFEATED THE LEGEND AND MYTH ITSELF" << endl; 
	}
}




void game() { //The overall process for the entire game
	displayTextData("GameInstructions.txt");
	srand(time(NULL));

	storeLocationData("locationName.txt");
	storeLocationData("locationDescription.txt");

	system("PAUSE");
	system("CLS");

	Player* player = new Player();
	player->getDetails();
	initializeGame(player);
	storeExitData("locationExit.txt");

	processGame(player);

}





int main() {
	game();
}