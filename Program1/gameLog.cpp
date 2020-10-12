#include "gameLog.h"

void gameLog(string s)
{
    cout << s << endl;
    ofstream fileOUT;
    ifstream fileIN;
    fileIN.open("game.txt");
    fileOUT.open ("game.txt",ios::app); // Append mode
    if (fileIN.is_open()) {
        fileOUT << s << endl; // Writing data to file
    }
    fileIN.close();
    fileOUT.close();
}