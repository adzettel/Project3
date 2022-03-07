// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <sstream>
#include <iostream>
#include <string>
#include "Pack.h"

using namespace std;


// add any necessary #include or using directives here

// add any necessary #include or using directives here

Pack::Pack(std::istream& pack_input){
    string rank, of, suit;
    for (int i = 0; i < 24; i++)
    {
        pack_input >> rank;
        pack_input >> of; // idk - removes "of" in the string
        pack_input >> suit;
        cards[i] = Card(rank, suit);
    }
    next = 0;
}

Pack::Pack(){
    string s = "Nine Spades\nTen Spades\nJack Spades\nQueen Spades\nKing Spades\n"
    "Ace Spades\n"
    "Nine Hearts\nTen Hearts\nJack Hearts\nQueen Hearts\nKing Hearts\nAce Hearts\n"
    "Nine Clubs\nTen Clubs\nJack Clubs\nQueen Clubs\nKing Clubs\nAce Clubs\n"
    "Nine Diamonds\nTen Diamonds\nJack Diamonds\nQueen Diamonds\nKing Diamonds\n"
    "Ace Diamonds";
    
    istringstream pack_input(s);
    string rank, of, suit;
    for (int i = 0; i < 24; i++)
    {
        pack_input >> rank;
        // pack_input >> of; // idk - removes "of" in the string
        pack_input >> suit;
        cards[i] = Card(rank, suit);
    }
    next = 0;
}

Card Pack::deal_one() {
assert(next != 24);
    next++;
    return cards[next - 1];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    reset();
    for (int i = 0; i < 7; i++)
    {
        std::array<Card, PACK_SIZE> temp;
        for (int i = 0; i < 24; i++)
        {
            if (i < 12)
                temp[2*i + 1] = cards[i];
            else
                temp[2*(i - 12)] = cards[i];
        }
        cards = temp;
    }
}

bool Pack::empty() const {
    // cout << "check if empty, next is " << next << endl;
    return next == 24;
}