
/*
This project is meant to provide the user the choice of loading a mad lib template file with replaceable words according to their liking. 

Author : Tin Nguyen 

Note: For a mad lib template to be deemed valid, every sentence must end with a ";". 
                                                 every replaceable word such as nouns, must end with a ",".
*/

#include "MadLibGencpp.h"


/*
 This function displays the contents inside the file of paramter "filename".
*/

void displayTextData(string filename) {
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

/*
This function reads from the given "myFileName" file and stores the story of the mad libs into "madLibs.txt" 
and stores the respective word type such as nouns, verbs, etc into "madBits.txt".
*/

void createLists(string myFileName) {
    ifstream fileToRead(myFileName);
    ofstream madBitsFile("madBits.txt");
    ofstream madLibsFile("madLibs.txt");

    if (fileToRead.is_open()) {
        string line = "";
        bool first_half = true;
        char newLine = '\n';
        while (!fileToRead.eof()) {

            getline(fileToRead, line, ';');

            if (line.rfind('a', 0) == 0) {
                madBits.push_back(line);
                madBitsFile << line + ",";
            }

            if (!line.rfind('a', 0) == 0) {
                madLibs.push_back(line + "\n");
                madLibsFile << line + ";";
            }
        }
        cout << "  Data loading from mabLibs.txt\n";
        cout << "  Data loading from madBits.txt\n  ";
    }
    else {
        cout << "\n File not found!\n";
    }

    fileToRead.close();
}

/*
The following function reads the given sentence from madLibs.txt based on the index and asks for the user's input to replace the 
first occurence of the word with their own. 
*/



void wordCounter(string replacedWord, int currentSentence) {

    ifstream fileToRead("madLibs.txt");

    if (fileToRead.is_open()) {
        string line = "";
        string final_sentence = "";
        string word;

        istringstream sentence(madLibs[currentSentence]);
        bool replaced = false;
        bool end = false;
        while (!replaced || !end) {
            string subs;
            sentence >> subs;

            if (!replaced) {
                if (subs == "WORD") {
                    subs = replacedWord;
                    replaced = true;
                }
                if (subs == "WORD." || subs == "WORD!" || subs == "WORD?") {
                    subs = replacedWord + subs.back();
                    replaced = true;
                }
                if (subs == "WORD!\".") {
                    subs = replacedWord + "!\"" + subs.back();
                    replaced = true;
                }
                if (subs == "WORD\".") {
                    subs = replacedWord + "\"" + subs.back();
                    replaced = true;
                }

            }
            final_sentence = final_sentence + " " + subs;


            if (subs.back() == '!' || subs.back() == '.') {
                end = true;
            }

        }
        madLibs[currentSentence] = final_sentence + "\n";

    }
    else {
        cout << "\nFile Not Found.\n";
    }

    fileToRead.close();


}

/*
This function asks for the user's inputs - to give a word according to what the word-type is such as noun, verb, etc. 
This data is gathered from the file which the function calls from the input. 
*/

void generateMadLib(string filename) {

    ifstream fileToRead2(filename);



    if (fileToRead2.is_open()) {
        string line = "";
        string sentence_line = "";

        string word;
        int divider = 0;
        int divider_limit = 0;
        int actual_sentence = 0;
        bool dividing_count = false;


        int length = madLibs.size();
        if (length == 0) {
            cout << "\nSeems like you have not read and stored data from files yet. \n";
        }


        while (!fileToRead2.eof() && length != 0) {

            istringstream sentence(madLibs[actual_sentence]);
            while (!dividing_count) {
                string subs;
                sentence >> subs;
                if (subs == "WORD" || subs == "WORD." || subs == "WORD!" || subs == "WORD?" || subs == "WORD!\"." || subs == "WORD\".") {
                    divider_limit++;

                }
                if (subs.back() == '!' || subs.back() == '.') {
                    dividing_count = true;
                }
            }

            getline(fileToRead2, line, ',');
            cout << "Enter " << line << ": ";
            cin >> word;

            wordCounter(word, actual_sentence);
            divider++;
            if (divider % divider_limit == 0) {
                divider = 0;
                divider_limit = 0;
                dividing_count = false;
                actual_sentence++;
                cout << "\n";

            }
        }
    }

    else {
        cout << "\nFile Not Found.\n";
    }

    cout << "\n";
    for (int i = 0; i < madLibs.size(); i++) {
        cout << madLibs[i];
    }
    cout << "\n";



    fileToRead2.close();

}

/*
This function asks for the user if they want to save the generated mad lib. If so, the function will iterate through 
madLibs which stored every generated sentence of the story and write it into the file "savedMadLibs.txt".
*/

void saveData() {
    cout << "\n";
    ofstream savedMadLibs("savedMadLibs.txt");

    if (madLibs.size() == 0) {
        cout << "You have nothing to save!\n";
    }
    else {
        for (int i = 0; i < madLibs.size(); i++) {
            cout << madLibs[i];
        }
        cout << "\n" << "Do you want to save this Mad Lib? (y/n) ";
        char answer;
        cin >> answer;
        if (answer == 'y' && savedMadLibs.is_open()) {
            for (int i = 0; i < madLibs.size(); i++) {
                savedMadLibs << madLibs[i];
            }
            cout << "Saved!\n";
        }
        else if (answer == 'n') {}
        else {
            cout << "\nInvalid answer.\n";
        }
    }
}

/*
This function is to print out the contents of the given filename. Despite it having the same function as 
displayTextData - this exists to fit the requirements of the assignment brief.
*/
void loadData(string filename) {
    displayTextData(filename);
}

/*
This function provides the user a menu and a choice to generate their own madlib. If they were to choose the 
options provided, a function will be called. Otherwise a 0 or any other input will terminate the program. 
*/

void runMenu()
{

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "       The Amazing Mad Lib Story Generator\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << " [0] End Testing the Program\n";
    cout << " [1] Display 'About' Information\n";
    cout << " [2] Read and store data from files\n";
    cout << " [3] Generate a random Mad Lib\n";
    cout << " [4] Save a Mad Lib to file\n";
    cout << " [5] Load saved Mad Libs from file\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << " Which option would you like (0-5): ";

    int x;
    cin >> x;
    switch (x) {
    case(0):
        cout << "\n Thank you for testing this application.\n";
        //cout << " If you did not select 0, re-run this program with a valid input.\n";
        return exit(EXIT_SUCCESS);
        break;

    case(1):
        system("CLS");
        displayTextData("MadAbout.txt");
        system("pause");
        system("CLS");
        runMenu();
        break;

    case(2):
        createLists("MadTemplate.txt");
        system("pause");
        system("CLS");
        runMenu();
        break;


    case(3):
        generateMadLib("madBits.txt");
        system("pause");
        system("CLS");
        runMenu();
        break;

    case(4):
        saveData();
        system("pause");
        system("CLS");
        runMenu();
        break;

    case(5):
        loadData("savedMadLibs.txt");
        system("pause");
        system("CLS");
        runMenu();
        break;




    }
}








//---------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------//


int main()
{
    runMenu();
    return 0;
}
