// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_suit_and_rank) {
    Card ten_spades = Card();
    ASSERT_EQUAL(ten_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(ten_spades.get_suit(), Card::SUIT_SPADES);

    Card three_hearts = Card(Card::RANK_THREE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(three_hearts.get_rank(), Card::RANK_THREE);
    ASSERT_EQUAL(three_hearts.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(three_hearts.get_suit(Card::SUIT_CLUBS), Card::SUIT_HEARTS);
}

TEST(test_card_ctor)
{
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}


TEST(test_is_face)
{
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c1(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c2(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c3(Card::RANK_ACE, Card::SUIT_CLUBS);

    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_TWO, Card::SUIT_CLUBS);
    
    ASSERT_TRUE(c.is_face() && c1.is_face());
    ASSERT_TRUE(c2.is_face()&& c3.is_face());
    ASSERT_FALSE(c4.is_face());
    ASSERT_FALSE(c5.is_face());

}

TEST(test_is_right_bower)
{
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c5(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_TRUE(c1.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(c2.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(c3.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c4.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c5.is_right_bower(Card::SUIT_HEARTS));
}

TEST(test_is_left_bower)
{
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c5(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(c1.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c2.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_TRUE(c3.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c4.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c5.is_left_bower(Card::SUIT_HEARTS));
}

TEST(test_is_trump)
{
    Card c(Card::RANK_TWO, Card::SUIT_HEARTS);
    Card c1(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c6(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card c7(Card::RANK_TEN, Card::SUIT_CLUBS);

    ASSERT_TRUE(c.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(c1.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(c2.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(c3.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(c4.is_trump(Card::SUIT_CLUBS));
    ASSERT_TRUE(c5.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(c6.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(c7.is_trump(Card::SUIT_CLUBS));
}

TEST(test_operators)
{
    Card c = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c2 = Card(Card::RANK_ACE, Card::SUIT_SPADES);

    Card c3(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    
    ASSERT_TRUE(c3 == c4);
    ASSERT_FALSE(c3 != c4);
    ASSERT_FALSE(c3 < c4);
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ASSERT_TRUE(c < c2);
    ASSERT_TRUE(c <= c2);
    ASSERT_TRUE(c2 > c);
    ASSERT_TRUE(c2 >= c);
    ASSERT_TRUE(c2 != c);
    ASSERT_FALSE(c2 == c);
}

TEST(test_suit_next)
{
    ASSERT_TRUE(Suit_next(Card::SUIT_SPADES) == Card::SUIT_CLUBS);
    ASSERT_TRUE(Suit_next(Card::SUIT_CLUBS) == Card::SUIT_SPADES);
    ASSERT_TRUE(Suit_next(Card::SUIT_HEARTS) == Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Suit_next(Card::SUIT_DIAMONDS) == Card::SUIT_HEARTS);
    ASSERT_FALSE(Suit_next(Card::SUIT_HEARTS) == Card::SUIT_CLUBS);
}

TEST(test_insertion)
{
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c1(Card::RANK_FOUR, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c5(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c6(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card c7(Card::RANK_TEN, Card::SUIT_CLUBS);
    ostringstream oss;
    oss << c;

    oss << c1<< endl;
    oss << c2 ;
    oss << c3;
    oss << c4 << endl;
    oss << c5;
    oss << c6;
    oss << c7;
    ASSERT_EQUAL(oss.str(),
                 ("Ace of SpadesFour of Spades\n"
                 "Jack of ClubsQueen of DiamondsJack of Spades\n"
                  "King of HeartsThree of DiamondsTen of Clubs"));
}

TEST(test_card_less)
{

    Card a1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card a2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card a3(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card a4(Card::RANK_KING, Card::SUIT_HEARTS);
    Card a5(Card::RANK_ACE, Card::SUIT_HEARTS);

    Card b1(Card::RANK_TEN, Card::SUIT_SPADES);
    Card b2(Card::RANK_JACK, Card::SUIT_SPADES);
    Card b3(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card b4(Card::RANK_KING, Card::SUIT_SPADES);
    Card b5(Card::RANK_ACE, Card::SUIT_SPADES);

    Card d1(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card d2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card d3(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card d4(Card::RANK_KING, Card::SUIT_CLUBS);
    Card d5(Card::RANK_ACE, Card::SUIT_CLUBS);

    Card e1(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card e2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card e3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e4(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card e5(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(Card_less(a1,a2,Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(a2,a3,Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(a3,a4,Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(a4,a5,Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(b1,b2,Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(b2,b3,Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(b3,b4,Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(b4,b5,Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(d1,d2,Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(d2,d3,Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(d3,d4,Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(d4,d5,Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(e1,e2,Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(e2,e3,Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(e3,e4,Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(e4,e5,Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(e1,d2,Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(e2,d3,Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(e3,d4,Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(e4,d5,Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(d1,e2,Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(d2,e3,Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(d3,e4,Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(d4,e5,Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(a1,b2,Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(a2,b3,Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(a3,b4,Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(a4,b5,Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(b1,a2,Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(b2,a3,Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(b3,a4,Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(b4,a5,Card::SUIT_HEARTS));
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c1(Card::RANK_FOUR, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(Card_less(c1, c, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(c, c1, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(c1, c2, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(c2, c3, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(c3, c2, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(c3, c2, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(c, c2, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(c2, c, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(c2, c3, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(c4, c3, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(c1, c3, Card::SUIT_HEARTS));
    
}
TEST(test_card_less_with_led){

    std::string trump = Card::SUIT_HEARTS;
    
    Card kk(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card dd(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card a(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card b(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card d(Card::RANK_KING, Card::SUIT_CLUBS);
    Card e(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card f(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card g(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card h(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card i(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(a, c, a, trump));
    ASSERT_TRUE(Card_less(kk, dd, kk, trump));
    ASSERT_FALSE(Card_less(a, b, a, trump));
    ASSERT_TRUE(Card_less(e, f, e, trump));
    ASSERT_FALSE(Card_less(h, i, e, trump));
    ASSERT_FALSE(Card_less(a, d, a, trump));
    ASSERT_TRUE(Card_less(g, h, e, trump));
}

TEST_MAIN()