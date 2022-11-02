#ifndef MADLIBGEN_H 
#define MADLIBGEN_H

//libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <sstream>

using namespace std;

//global variables
vector<string> madLibs;
vector<string> madBits;

//function declarations; 
void displayTextData(string filename);
void createLists(string myFileName);
void wordcounter(string replacedWord, int currentSentence);
void generateMadLib(string filename);
void saveData();
void loadData(string filename);
void runMenu();
int main();



#endif MADLIBGEN_H