/********************************
 A3 :  Easy Come - Easy Go Dice Game 
 Tin Nguyen 32480768

********************************/

#include "Main.h"


string displayInstructions() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "          Easy Come - Easy Go Dice Game" << endl;
	cout << "                   BUT REVERSED !" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; 
	cout << "Roll the die and the corresponding panel [x] will" << endl; 
	cout << "open its window. But if it's opened, it will close to" << endl;
	cout << "hide its number. Be the first player to open every" << endl; 
	cout << "box on your panel OR have the lowest score after 10" << endl; 
	cout << "            rounds to win the game." << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	system("pause");
	system("CLS");
	string name;

	cout << "What is your name ? " << endl; 
	cout << ">> My name is ";
	cin >> name; 

	system("pause");
	system("CLS");

	return name;
	

}

void gameProgress(string name, int rounds) {
	
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "          Round Number: " << rounds << endl;
	cout << name << ": "; 

	int accumulator = 0;
	for (int i = 1; i < playerOnePanel.size(); i++) {
		if (playerOnePanel[i] != 0) cout << "[" << playerOnePanel[i] << "] ";
		if (playerOnePanel[i] == 0) cout << "[x] ";
		accumulator += playerOnePanel[i];
	}

	cout << " Score: " << accumulator << "\n";
	if (accumulator == 21) {
		victoryScreen();
	}
	accumulator = 0;
	cout << "Fujitora" << ": ";


	for (int i = 1; i < playerTwoPanel.size(); i++) {
		if (playerTwoPanel[i] != 0) cout << "[" << playerTwoPanel[i] << "] ";
		if (playerTwoPanel[i] == 0) cout << "[x] ";
		accumulator += playerTwoPanel[i];
	}
	cout << " Score: " << accumulator << "\n";
	if (accumulator == 21) {
		defeatScreen();
	}
	accumulator = 0;
	cout << "Akainu" << ": ";

	for (int i = 1; i < playerOnePanel.size(); i++) {
		if (playerThreePanel[i] != 0) cout << "[" << playerThreePanel[i] << "] ";
		if (playerThreePanel[i] == 0) cout << "[x] ";
		accumulator += playerThreePanel[i];
	}

	cout << " Score: " << accumulator << "\n";
	if (accumulator == 21) {
		defeatScreen();
	}
	accumulator = 0;
	cout << "Fraudbull" << ": ";

	for (int i = 1; i < playerOnePanel.size(); i++) {
		if (playerFourPanel[i] != 0) cout << "[" << playerFourPanel[i] << "] ";
		if (playerFourPanel[i] == 0) cout << "[x] ";
		accumulator += playerFourPanel[i];
	}

	cout << " Score: " << accumulator << "\n";
	if (accumulator == 21) {
		defeatScreen();
	}

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");

}

void gameDecide(string name) {
	cout << "What will you do ? " << endl;;
	int input;
	cin >> input;
	int oneRoll = rand() % 6 + 1;
	int twoRoll = rand() % 6 + 1;
	int threeRoll = rand() % 6 + 1;
	int fourRoll = rand() % 6 + 1;

	switch (input) {
	case(1):


		cout << "\n" << name << ", you rolled a [" << oneRoll << "]" << endl;

		if (playerOnePanel[oneRoll] == oneRoll) {
			playerOnePanel[oneRoll] = 0;
		}
		else if (playerOnePanel[oneRoll] == 0) {
			playerOnePanel[oneRoll] = oneRoll;
		}

		
		if (playerTwoPanel[twoRoll] == twoRoll) {
			playerTwoPanel[twoRoll] = 0;
		}
		else if (playerTwoPanel[twoRoll] == 0) {
			playerTwoPanel[twoRoll] = twoRoll;
		}

		
		if (playerThreePanel[threeRoll] == threeRoll) {
			playerThreePanel[threeRoll] = 0;
		}
		else if (playerThreePanel[threeRoll] == 0) {
			playerThreePanel[threeRoll] = threeRoll;
		}

		
		if (playerFourPanel[fourRoll] == fourRoll) {
			playerFourPanel[fourRoll] = 0;
		}
		else if (playerFourPanel[fourRoll] == 0) {
			playerFourPanel[fourRoll] = fourRoll;
		}
		break;

	case(2):
		system("CLS");
		defeatScreen();
		break;

	default: 
		cout << "WRONG INPUT" << endl;
		break;
	}

}


void victoryScreen() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "                   YOU WON !" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
	system(EXIT_SUCCESS);
}

void defeatScreen() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "                   YOU LOST !" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
	system(EXIT_SUCCESS);
}


int main() {



	string player1 = displayInstructions();
	srand(time(NULL));
	
	int rounds = 1; 

	/*Player* fujitora = new Player("Fujitora"); 
	Player* akainu = new Player("Akainu"); 
	Player* fraudbull = new Player("Fraudbull");*/


	for (int i = 0; i <= 6; i++) {
		playerOnePanel.push_back(0);
		playerTwoPanel.push_back(0);
		playerThreePanel.push_back(0);
		playerFourPanel.push_back(0);
	}

	
	
	while (rounds < 10) {
		gameProgress(player1, rounds);
		cout << "    Options: [1] Roll \n";
		cout << "             [2] Quit \n";
		gameDecide(player1);

		rounds++;
	}

	int oneAcc = 0; 
	int twoAcc = 0; 
	int threeAcc = 0; 
	int fourAcc = 0; 
	for (int i = 0; i < playerOnePanel.size(); i++) {
		oneAcc += playerOnePanel[i]; 
		twoAcc += playerTwoPanel[i]; 
		threeAcc += playerThreePanel[i]; 
		fourAcc += playerFourPanel[i];
	}

	if (oneAcc <= twoAcc && oneAcc <= threeAcc && oneAcc <= fourAcc) {
		victoryScreen();
	}
	else {
		defeatScreen();
	}

}
