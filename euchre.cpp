// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include "Card.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Game{
    public:
    //sets up players, points to win, and shuffle mode
    void setupGame(char *argv[]); 
     //sets up deck
    bool setPack(char* argv[]);
     //deals cards in deal order: 3-2-3-2 2-3-2-3.
    void deal();
    //establishes deal order based on current dealer
    void setDealOrder(); 
     //calls deck.shuffle() 7 times
    void shuffle7();
//returns what currentTrump is
    string makeTrump(); 
    //has players play their cards; gets best player
    void doTrick(); 
    //used in doTrick to add points
    void trickWinner(int n); 
    //changes deal order based on winner of trick
    void setTrickOrder(Player *winner); 
    //does a round: resets control variables
    void doRound(); 
     //returns 1 if t1 wins, 2 if t2 wins, 0 if no win
    int checkForWin();
    
    void deleteGame();
    
    private: 
    //main variables - are not reset after each round
    Pack deck;
    Player* p0;
    Player* p1;
    Player* p2;
    Player* p3;
    vector<Player*> team1 {p0,p2};
    vector<Player*> team2 {p1,p3};
    int pointsToWin;
    int t1Points = 0;
    int t2Points = 0;
    bool shuffleMode = false;
    int numHands = 0;
    //control variables - get reset after each call of doRound()
    int currentDealer = 0;
    string currentTrump;
    Card upcard;
    bool t1trump;
    bool t2trump;
    int t1Tricks = 0;
    int t2Tricks = 0;
     //determines deal AND play order
    vector<Player*> dealOrder = {p1,p2,p3,p0};
};
//returns true if cmdline argument format is incorrect
bool failedPrelimChecks(int argc, char *argv[]); 

int main(int argc, char *argv[]){

    if (failedPrelimChecks(argc, argv)){ //checks argument input 
    std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return -1;
    }

    for (int i = 0; i < argc; i++){
        cout << argv[i] << " ";
    }
    cout << endl;
    Game game;
    if (!game.setPack(argv)) { //reads in pack
        std::cout << "Error opening " << argv[1] << endl;
        return -1;
    }
    game.setupGame(argv); //reads in players 
    //does game until thfere is a winner
    while(game.checkForWin()==0) {game.doRound();} 
    if (game.checkForWin() == 1) {
        cout << argv[4] << " and " << argv[8];
        cout << " win!" << endl << endl;
        }
    if (game.checkForWin() == 2) {
        cout << argv[6] << " and " << argv[10];
        cout << " win!" << endl << endl;
    }
    delete &game;
    return 0;
}

void Game::setupGame(char* argv[]){
    //turns on shuffling
    string shuffle = argv[2];
    if (shuffle == "shuffle") this->shuffleMode = true; 
    pointsToWin = stoi(argv[3]);
    //reads in player name and type
    p0 = Player_factory(argv[4],argv[5]);
    p1 = Player_factory(argv[6],argv[7]);
    p2 = Player_factory(argv[8],argv[9]);
    p3 = Player_factory(argv[10],argv[11]);
}

bool Game::setPack(char* argv[]){
    //reads in deck, returns true if file opened correctly
    ifstream packIn (argv[1]);
    bool fileOpened = packIn.is_open();
    deck = Pack(packIn);
    packIn.close();
    return fileOpened;
}

void Game::deal() {
    this->setDealOrder();
    if (shuffleMode) this->shuffle7(); 
    else deck.reset();
    cout << *dealOrder[3] << " deals" << endl;

    dealOrder[0]->add_card(deck.deal_one());
    dealOrder[0]->add_card(deck.deal_one());
    dealOrder[0]->add_card(deck.deal_one());

    dealOrder[1]->add_card(deck.deal_one());
    dealOrder[1]->add_card(deck.deal_one());

    dealOrder[2]->add_card(deck.deal_one());
    dealOrder[2]->add_card(deck.deal_one());
    dealOrder[2]->add_card(deck.deal_one());

    dealOrder[3]->add_card(deck.deal_one());
    dealOrder[3]->add_card(deck.deal_one());

    dealOrder[0]->add_card(deck.deal_one());
    dealOrder[0]->add_card(deck.deal_one());

    dealOrder[1]->add_card(deck.deal_one());
    dealOrder[1]->add_card(deck.deal_one());
    dealOrder[1]->add_card(deck.deal_one());

    dealOrder[2]->add_card(deck.deal_one());
    dealOrder[2]->add_card(deck.deal_one());
    
    dealOrder[3]->add_card(deck.deal_one());
    dealOrder[3]->add_card(deck.deal_one());
    dealOrder[3]->add_card(deck.deal_one());

    upcard = deck.deal_one();
    cout << upcard << " turned up" << endl;
    currentDealer++;
    if (currentDealer > 3) currentDealer = 0;
}

void Game::setDealOrder(){
    if (currentDealer == 0) dealOrder = {p1,p2,p3,p0};
    if (currentDealer == 1) dealOrder = {p2,p3,p0,p1};
    if (currentDealer == 2) dealOrder = {p3,p0,p1,p2};
    if (currentDealer == 3) dealOrder = {p0,p1,p2,p3};
}

void Game::shuffle7(){
    deck.shuffle();
}

string Game::makeTrump(){
    string trump = upcard.get_suit();
    int round = 1;
    for(int i = 0; i < (int)dealOrder.size(); ++i){
        if (dealOrder[i]->make_trump(upcard, dealOrder[3]==dealOrder[i], round, trump)){
            cout << *dealOrder[i] << " orders up " << trump << endl;
            if (round == 1) dealOrder[3]->add_and_discard(upcard);
            if (dealOrder[i] == p0 || dealOrder[i] == p2) t1trump = true;
            if (dealOrder[i] == p1 || dealOrder[i] == p3) t2trump = true;
            return trump;
        }
        else cout << *dealOrder[i] << " passes" << endl;
        if(i == (int)dealOrder.size()-1) {round++; i = -1;}
    }
    if (round == 2) trump = Suit_next(upcard.get_suit());
    cout << trump << endl;
    return trump;
}

void Game::doTrick(){
    Card c1,c2,c3,c4,bestCard;
    c1 = dealOrder[0]->lead_card(currentTrump);
    cout << c1 << " led by " << *dealOrder[0] << endl;
    c2 = dealOrder[1]->play_card(c1, currentTrump);
    cout << c2 << " played by " << *dealOrder[1] << endl;
    c3 = dealOrder[2]->play_card(c1,currentTrump);
    cout << c3 << " played by " << *dealOrder[2] << endl;
    c4 = dealOrder[3]->play_card(c1,currentTrump);
    cout << c4 << " played by " << *dealOrder[3] << endl;
    vector<Card> pile = {c1,c2,c3,c4};

    while(pile.size() > 1){
        for (int i = 1; i < (int)pile.size() ; ++i){
            if(Card_less(pile[0],pile[i],c1,currentTrump)) pile.erase(pile.begin());
            else pile.erase(pile.begin()+i);
        }
    }

    bestCard = pile[0];
    if (bestCard == c1) trickWinner(0);
    else if (bestCard == c2) trickWinner(1);
    else if (bestCard == c3) trickWinner(2);
    else if (bestCard == c4) trickWinner(3);
}

void Game::trickWinner(int n){
    cout << *dealOrder[n] << " takes the trick" << endl << endl;
        if (dealOrder[n] == p0 || dealOrder[n] == p2) t1Tricks++;
        else t2Tricks++;
        this->setTrickOrder(dealOrder[n]);
}

void Game::setTrickOrder(Player *winner){
    if (winner == p1) dealOrder = {p1,p2,p3,p0};
    if (winner == p2) dealOrder = {p2,p3,p0,p1};
    if (winner == p3) dealOrder = {p3,p0,p1,p2};
    if (winner == p0) dealOrder = {p0,p1,p2,p3};
}

void Game::doRound(){
    cout << "Hand " << numHands << endl;
    numHands++;
    this->deal(); // sets deal order 
    currentTrump = this->makeTrump(); 
    cout << endl;

    for (int i = 0; i < Player::MAX_HAND_SIZE; ++i){ //does 5 tricks
        this->doTrick();
    }
    //points logic
    if (t1Tricks > t2Tricks){ 
        cout << *p0 << " and " << *p2 << " win the hand" << endl;
        if (t1Tricks == 5 && t1trump){
            t1Points += 2; 
            cout << "march!" << endl;
        } 
        else if (t2trump) {
            cout << "euchred!" << endl;
            t1Points += 2;
        }
        else t1Points++;
    }
    if (t2Tricks > t1Tricks){
        cout << *p1 << " and " << *p3 << " win the hand" << endl;
        if (t2Tricks == 5 && t2trump) {
            t2Points += 2; 
            cout << "march!" << endl;
        }
        else if (t1trump) {
            cout << "euchred!" << endl;
            t2Points += 2;
        }
        else t2Points++;
    }
    //resets tricks and trump
    t1Tricks = 0;
    t2Tricks = 0;
    t1trump = false;
    t2trump = false;
    //prints current point totals
    cout << *p0 << " and " << *p2 << " have " << t1Points << " points" << endl;
    cout << *p1 << " and " << *p3 << " have " << t2Points << " points" << endl << endl;
}

int Game::checkForWin(){
    if(t1Points>=pointsToWin) return 1;
    if(t2Points>=pointsToWin) return 2;
    else return 0;
}

bool failedPrelimChecks(int argc, char *argv[]){
    //has enough arguments
    if (argc != 12) return true; 
    //proper amount of points to win
    if (stoi(argv[3]) < 1 || stoi(argv[3]) > 100) return true; 
    string shuffleMode = argv[2];
    //either shuffle or noshuffle
    if(shuffleMode != "noshuffle" && shuffleMode != "shuffle") return true;
    //player type either simple or human 
    for (int i = 5; i < 11; i+=2){ 
        string ptype = argv[i];
        if (ptype != "Simple" && ptype != "Human") return true;
    }
    return false;
}


