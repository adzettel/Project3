// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <sstream>
#include <iostream>
#include <string>
#include "Pack.h"

using namespace std;


// add any necessary #include or using directives here

Pack::Pack(std::istream& pack_input){
    string rank, of, suit;
    for (int i = 0; i < 24; i++)
    {
        pack_input >> rank;
        pack_input >> of; // idk
        pack_input >> suit;
        cards[i] = Card(rank, suit);
    }
    next = 0;
}

Pack::Pack(){
    string s = "Nine of Spades\nTen of Spades\nJack of Spades\nQueen of Spades\nKing of Spades\nAce of Spades\nNine of Hearts\nTen of Hearts\nJack of Hearts\nQueen of Hearts\nKing of Hearts\nAce of Hearts\nNine of Clubs\nTen of Clubs\nJack of Clubs\nQueen of Clubs\nKing of Clubs\nAce of Clubs\nNine of Diamonds\nTen of Diamonds\nJack of Diamonds\nQueen of Diamonds\nKing of Diamonds\nAce of Diamonds";
    istringstream pack_input(s);
    string rank, of, suit;
    for (int i = 0; i < 24; i++)
    {
        pack_input >> rank;
        pack_input >> of; // idk
        pack_input >> suit;
        cards[i] = Card(rank, suit);
    }
    next = 0;
}

Card Pack::deal_one() {
    assert(next != 23);
    next++;
    return cards[next - 1];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    reset();
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

bool Pack::empty() const {
    return next == 23;
}