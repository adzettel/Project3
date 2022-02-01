// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to Two of Spades
Card::Card(){
  rank = "Two";
  suit = "Spades";
}

Card::Card(const std::string &rank_in, const std::string &suit_in){
    rank = rank_in;
    suit = suit_in;
}

//EFFECTS Returns the rank
std::string Card::get_rank() const{
  return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const{
  return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const{
    if(rank == "Jack" && suit != trump){
        if(trump == "Diamonds" && suit == "Hearts") return trump;
        if(trump == "Hearts" && suit == "Diamonds") return trump;
        if(trump == "Clubs" && suit == "Spades") return trump;
        if(trump == "Spades" && suit == "Clubs") return trump; 
    }else return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const{
  if (rank == "Jack" || rank == "Queen" || rank == "King" || rank == "Ace")
      return true;
  else return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const{
  assert(trump == "Spades" || trump == "Clubs" || trump == "Diamonds" || trump == "Hearts");
  if (rank != "Jack") return false;
  if (suit == trump) return true;
  else return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const{
  assert(trump == "Spades" || trump == "Clubs" || trump == "Diamonds" || trump == "Hearts");
  if (rank != "Jack") return false;
  if (rank == trump) return false;
  if (this->get_suit(trump) == trump) return true;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const{
  assert(trump == "Spades" || trump == "Clubs" || trump == "Diamonds" || trump == "Hearts");
  if (suit == trump) return true;
  if (this->is_left_bower(trump) == true) return true;
}


//OPERATOR OVERLOADING//

int find_weight(const Card &lhs) {
  for (int i = 0; i < 13; i++)
  {
    if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
      return i;
    }
  }
  throw "not found rank";
  return -1; // throw error
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
  return find_weight(lhs) < find_weight(rhs);
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
  return find_weight(lhs) <= find_weight(rhs);
};

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
  return find_weight(lhs) > find_weight(rhs);
};

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
  return find_weight(lhs) >= find_weight(rhs);
};

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
  return find_weight(lhs) == find_weight(rhs) && lhs.get_suit() == rhs.get_suit();
};

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
  return !(find_weight(lhs) == find_weight(rhs) && lhs.get_suit() == rhs.get_suit());
};

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit);

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card);

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump);

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump);

