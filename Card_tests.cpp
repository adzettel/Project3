// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>


using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Tests a bower's rank and suit and the bool functions
TEST(test_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::RANK_JACK, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES,c.get_suit(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_CLUBS, c.get_suit());

    ASSERT_TRUE(c.is_face());

    ASSERT_TRUE(c.is_left_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(!c.is_left_bower(Card::SUIT_CLUBS));

    ASSERT_TRUE(c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(!c.is_right_bower(Card::SUIT_SPADES));
}

TEST(test_comparisons){

    Card aceClubs(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card queenDiamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card twoSpades(Card::RANK_TWO, Card::SUIT_SPADES);
    Card jackClubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jackSpades(Card::RANK_JACK, Card::SUIT_SPADES);

    //operator comparisons
    ASSERT_TRUE(aceClubs > queenDiamonds);
    ASSERT_TRUE(queenDiamonds < aceClubs);
    ASSERT_TRUE(jackClubs == jackClubs);
    ASSERT_TRUE(jackClubs <= jackSpades);
    ASSERT_TRUE(jackClubs >= jackSpades);
    ASSERT_TRUE(jackSpades != aceClubs);


    //non trump against non trump
    ASSERT_TRUE(Card_less(queenDiamonds,aceClubs,Card::SUIT_HEARTS));

    //trump against non trump
    ASSERT_TRUE(Card_less(aceClubs,queenDiamonds,Card::SUIT_DIAMONDS));

    //trump against trump (left vs right)
    ASSERT_TRUE(Card_less(jackSpades,jackClubs,queenDiamonds,Card::SUIT_CLUBS));
    
    //trump against non-lead card
    ASSERT_TRUE(Card_less(aceClubs,queenDiamonds,twoSpades,Card::SUIT_DIAMONDS));

    //non trump against lead card
    ASSERT_TRUE(Card_less(aceClubs, twoSpades, twoSpades, Card::SUIT_DIAMONDS));
}

TEST(test_print){
    ostringstream oss;
    Card aceSpades(Card::RANK_ACE, Card::SUIT_SPADES);
    oss << aceSpades;
    ASSERT_EQUAL(oss.str(),"Ace of Spades");

}

TEST_MAIN()
