#ifndef Main_h 
#define Main_h

#include <fstream> 
#include <string> 
#include <time.h>
#include <iostream>
#include "Player.h"
#include <vector> 

using namespace std;

vector<int> playerOnePanel; 
vector<int> playerTwoPanel; 
vector<int> playerThreePanel; 
vector<int> playerFourPanel; 



string displayInstructions(); 
void gameProgress(string name, int rounds);
void gameDecide(string name);
void defeatScreen();
void victoryScreen();


#endif 