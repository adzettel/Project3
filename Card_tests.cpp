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

TEST(operator_minimums){
    Card nineSpades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nineDiamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(nineSpades < nineDiamonds);
    ASSERT_TRUE(nineSpades <= nineDiamonds);
    ASSERT_FALSE(nineSpades > nineDiamonds);
    ASSERT_FALSE(nineSpades >= nineDiamonds);
    ASSERT_TRUE(nineSpades != nineDiamonds);
    ASSERT_FALSE(nineSpades == nineDiamonds);
}
TEST(operator_maximums){
    Card aceDiamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(aceDiamonds > aceDiamonds);
    ASSERT_TRUE(aceDiamonds >= aceDiamonds);
    ASSERT_FALSE(aceDiamonds < aceDiamonds);
    ASSERT_TRUE(aceDiamonds <= aceDiamonds);
    ASSERT_FALSE(aceDiamonds != aceDiamonds);
    ASSERT_TRUE(aceDiamonds == aceDiamonds);
}
TEST(suit_next){
    Card nineSpades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nineDiamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card nineClubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card nineHearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(nineSpades.get_suit()), "Clubs");
    ASSERT_EQUAL(Suit_next(nineClubs.get_suit()), "Spades");
    ASSERT_EQUAL(Suit_next(nineDiamonds.get_suit()), "Hearts");
    ASSERT_EQUAL(Suit_next(nineHearts.get_suit()), "Diamonds");
}




//get.suit(trump), get.face, is_left_bower, is_right_bower, is_trump 
TEST(getSuitFace){
    Card jackHearts(Card::RANK_JACK,Card::SUIT_HEARTS);
    Card nineSpades(Card::RANK_NINE,Card::SUIT_SPADES);

    ASSERT_EQUAL(nineSpades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(nineSpades.get_suit(Card::SUIT_CLUBS), Card::SUIT_SPADES);

    ASSERT_EQUAL(jackHearts.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(jackHearts.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(jackHearts.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);


    ASSERT_TRUE(jackHearts.is_trump(Card::SUIT_HEARTS) && jackHearts.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(jackHearts.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(jackHearts.is_trump(Card::SUIT_SPADES));

    ASSERT_TRUE(jackHearts.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(jackHearts.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(jackHearts.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(nineSpades.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(nineSpades.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(jackHearts.is_left_bower(Card::SUIT_DIAMONDS) && jackHearts.is_right_bower(Card::SUIT_DIAMONDS));

    ASSERT_TRUE(jackHearts.is_face());
    ASSERT_FALSE(nineSpades.is_face());
}

//Card_less(led, trump), Card_less(trump), find_rank_weight, find_suit_weight
TEST(Card_less){
    Card nineDiamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card nineSpades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card jackHearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card aceClubs(Card::RANK_ACE, Card::SUIT_CLUBS);

    ASSERT_TRUE(Card_less(aceClubs, jackHearts, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(aceClubs, jackHearts, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(nineSpades, nineDiamonds, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(nineSpades, nineSpades, Card::SUIT_SPADES));

    ASSERT_TRUE(Card_less(aceClubs, jackHearts, nineSpades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(aceClubs, jackHearts, nineSpades, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(nineSpades, nineDiamonds, aceClubs, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(nineSpades, nineSpades, nineSpades, Card::SUIT_SPADES));
}

//print operator
TEST(test_print){
    ostringstream oss;
    Card aceSpades(Card::RANK_ACE, Card::SUIT_SPADES);
    oss << aceSpades;
    ASSERT_EQUAL(oss.str(),"Ace of Spades");
}

TEST_MAIN()