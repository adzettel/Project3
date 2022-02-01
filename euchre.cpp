#include "Pack.h"
#include "Card.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Game{
    private: 
    vector<Player> Team1;
    vector<Player> Team2;

    int pointToWin;
    int t1Points = 0;
    int t2Points = 0;

    string currentTrump;
    Card topCard;
    Pack deck;

    public:

    //REQUIRES: Round is over
    //MODIFIES: t1points or t2points
    //EFFECTS: t1points or t2points
    void checkForWin();

    void deal();

};

bool prelimChecks(int argc, char *argv[]);


int main(int argc, char *argv[]){

    if (prelimChecks(argc, argv)){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return -1;
    }

    
   
    

}

//Returns true if the input fails the prelim checks
bool prelimChecks(int argc, char *argv[]){

    if (argc != 12) return true;

    int pointsToWin = stoi(argv[3]);
    if (pointsToWin < 1 || pointsToWin > 100) return true;

    string shuffleMode = argv[2];
    if(shuffleMode != "noshuffle" || shuffleMode != "shuffle") return true;

    for (int i = 5; i < 11; i+=2){
        string ptype = argv[i];
        if (ptype != "Simple" || ptype != "Human") return true;
    }
    return false;
    
}