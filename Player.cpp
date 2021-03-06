// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Player.h"

using namespace std;

class SimplePlayer : public Player{
    public:
        // DONE
        SimplePlayer(const string &in) {
            name = in;
        }

        // DONE
        const std::string & get_name() const {
            return name;
        }
        
        // DONE
        void add_card(const Card &c) {
            assert(cards.size() < MAX_HAND_SIZE);
            cards.push_back(c);
        }

        // DONE
        bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
            assert(round == 1 || round == 2);

            if (round == 1) {
                if (countBowers(upcard.get_suit()) >= 2)  { // player wants to change suit
                    order_up_suit = upcard.get_suit(); // changed suit
                    return true;
                }
            } else {
                if (is_dealer || countBowers(Suit_next(upcard.get_suit())) >= 1) {
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;
                }
            }

            return false;
        }

        void add_and_discard(const Card &upcard) {
            assert(cards.size() > 1); // makes no sense
            cards.push_back(upcard);
            cards.erase(cards.begin() + lowest_card(upcard.get_suit()));
        }

        Card lead_card(const std::string &trump) {
            int p = highest_anti_trump(trump);
            Card output = cards.at(p);
            cards.erase(cards.begin() + p); 
            return output;
        }

        Card play_card(const Card &led_card, const std::string &trump) {
            int p;
            if (has_suit(led_card.get_suit(trump),trump)) {
                p = highest_card_suit(led_card.get_suit(trump), trump); 
            } else {
                p = lowest_card(trump);
            }
            Card output = cards.at(p);
            cards.erase(cards.begin() + p);
            return output;
        }

    private:
        string name;
        vector<Card> cards;

        int countBowers(string suit) const {
            int count = 0;
            for (size_t i = 0; i < cards.size(); i++)
            {
                if (cards[i].is_left_bower(suit) || 
                (cards[i].is_trump(suit) && cards[i].is_face()))
                    count++;
            }
            return count;
        }

        int highest_anti_trump(const string trump) const {
            vector<string> s;
            s.push_back(trump);
            vector<Card> f = filter(s, true, trump);
            if (f.size() == 0) return highest_card(trump); // only trumps
            return findIndex(f.at(range_card(f, true, trump)));
        }

        int highest_card_suit(const string suit, const string trump) const {
            vector<string> s;
            s.push_back(suit);
            vector<Card> f = filter(s, false, trump);
            return findIndex(f.at(range_card(f, true, trump)));
        }

        int findIndex(const Card &look) const {
            for (size_t i = 0; i < cards.size(); i++)
            {
                if (look == cards.at(i)) {
                    return i;
                }
            }
            throw "card not found";
        }

        bool has_suit(string suit, string trump) {
            for (size_t i = 0; i < cards.size(); i++)
            {
                if (cards[i].get_suit(trump) == suit)
                    return true;
            }
            return false;
        }

        int range_card(const vector<Card> input, const bool sortHigh, 
        string trump) const {
            if (input.size() == 1) 
                return 0;
            Card c = input.at(0);
            int l = 0;
            for (size_t i = 0; i < input.size(); i++)
            {
                if (sortHigh ? (Card_less(c,input.at(i),trump)) :
                 Card_less(input.at(i),c,trump)) {
                    l = i;
                    c = input.at(i);
                }
            }
            return l;
        }

        int highest_card(string trump) const {
            return range_card(cards, true, trump);
        }

        int lowest_card(string trump) const {
            return range_card(cards, false, trump);
        }

        vector<Card> filter(const vector<string> suits, const bool flip, 
        const string trump) const {
            assert(suits.size() >= 1);
            vector<Card> o;
            for (size_t i = 0; i < cards.size(); i++)
            {
                bool pass = false;
                for (size_t x = 0; x < suits.size(); x++)
                {
                    if (flip ? cards[i].get_suit(trump) != suits[x] : 
                    cards[i].get_suit(trump) == suits[x])  // checked to see if was bower
                        pass = true;
                }
                if (pass)
                    o.push_back(cards[i]);
            }
            return o;
        }
};

class HumanPlayer : public Player{
    public:
        // DONE
        HumanPlayer(const string &in) {
            name = in;
        }

        // DONE
        const std::string & get_name() const {
            return name;
        }
        
        // DONE
        void add_card(const Card &c) {
            assert(cards.size() < MAX_HAND_SIZE);
            cards.push_back(c);
        }

        // DONE
        bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
            assert(round == 1 || round == 2);
            printHand();
            string input;
            string suit = upcard.get_suit();
            cout << "Human player " << name << ", please enter a suit,"
            " or \"pass\":" << endl;
            cin >> input;
            if (round == 1) {
                if (input != "pass" && input == suit) {
                    order_up_suit = suit;
                    return true;
                } 
            } else {
                if (input != "pass" && input != suit) {
                    order_up_suit = input;
                    return true;
                } 
            }
            return false;
        }

        void add_and_discard(const Card &upcard) {
            assert(cards.size() > 0); // makes no sense
            printHand();
            sort(cards.begin(),cards.end()); //sorted hand to match what was printed
            cout << "Discard upcard: [-1]" << endl;
            cout<< "Human player " << name << ", please select a card to discard:"
             << endl;
            int p = -1;
            cin >> p;
            if (p >= 0) {
                cards.erase(cards.begin() + p);
                cards.push_back(upcard);
            }
        }

        Card lead_card(const std::string &trump) {
            assert(cards.size() > 0);
            printHand();
            sort(cards.begin(),cards.end()); //sorted hand to match what was printed
            cout << "Human player " << name << ", please select a card:" << endl; 
            int p;
            cin >> p;
            Card output = cards.at(p);
            cards.erase(cards.begin() + p); 
            return output;
        }

        Card play_card(const Card &led_card, const std::string &trump) {
            assert(cards.size() > 0);
            printHand();
            sort(cards.begin(),cards.end()); //sorted hand to match what was printed
            cout << "Human player " << name << ", please select a card:" << endl; 
            int p;
            cin >> p;
            Card output = cards.at(p);
            cards.erase(cards.begin() + p);
            return output;
        }

    private:
        string name;
        vector<Card> cards;

        void printHand() const {
            vector<Card> copy = cards;
            sort(copy.begin(), copy.end());
            for (size_t i = 0; i < copy.size(); i++)
            {
                cout << "Human player " << name << "'s hand: [" << i << "] " << copy[i]
                 << endl;
            }
        }
};


Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  } else if (strategy == "Human") {
    // The "new" keyword dynamically allocates an object.
    return new HumanPlayer(name);
  }

  // Invalid strategy if we get here
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name(); //send output to "os"
  return os; //don't forget to return "os"
}
