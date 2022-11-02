#include "Player.h"
#include "Item.h"
#include "Artefact.h"
#include "Dragon.h"
#include "Monster.h"
#include "Location.h"
#include "Goblin.h"
#include "Hobgoblin.h"
#include "Ogre.h"
#include "Troll.h"
#include <fstream>
#include <cstdlib>

#ifndef MAIN_H
#define MAIN_H

vector<string> locationName;
vector<string> locationDescription; 
vector<Location*> locationMap;
vector<int> playerTracker;
vector<int> amountArtefactTracker;
vector<int> amountHunterTracker;
vector<Item*> artefactTracker; 

string listOfActions[20] = { " ripped off the shoulder of ", " hammered the leg of ", " smothered ",
" reformed the skull of ", " threw a rock at ", " clobbered ", " whipped ", " punished ", " disposed fingers from ",
" vaporized both eyes from ", " delivered a concussion to ", " crashed a hunk of steel into ",
" flattened the beautiful face of ", " reduced the life expectancy of ", " butchered the toenails of ",
" deciminated the limbs of ", " stole clavicles from ", " threw salt at ", " walloped and flattened ",
" absolutely disrespected " };

string listOfSwords[11] = { "Arming Sword", "Ceremonial Sword",
"Longsword", "Backsword", "Falchion", "Estoc",
"Claymore", "Paramerion", "Cutlass", "Rapier", "Sabre" };

string listOfArmor[10] = { "Brigandine", "Codpiece",
"Cuirass", "Fauld", "Gambeson", "Hauberk",
"Jack of plates", "Jupon", "Pourpoint","Chainmail"};

void displayTextData(string filename);
void storeLocationData(string filename);
void displayMap(int mapIndex);
void displayLocationMessage(int mapindex);
void examineLocation(Player* player, int mapindex);
void initiateArtefacts(string filename);
int traverseMap(int currentLocation, int direction);
void eatProvision(Player* player);
bool moneyChecker(Player* player, int amount);
void shop(Player* player);
Player* initializeGame(Player* player);
void processGame(Player* player);
void gambleStats(Player* player);

void battleGoblin(Player* player, Goblin* goblin, int mapindex);
void battleHobgoblin(Player* player, Hobgoblin* hobgoblin, int mapindex);
void battleOgre(Player* player, Ogre* ogre, int mapindex, int artefact);
void battleTroll(Player* player, Troll* troll, int mapindex, int artefact);
void battleDragon(Player* player, Dragon* dragon, int mapindex);
void battleTreasureHunter(Player* player, TreasureHunter* hunter, int mapindex);

void goblinDropLoot(Player* player, int probability);
void ogreTrollDropLoot(Player* player, int probability, int artefact, bool isDragon);



void game();


#endif