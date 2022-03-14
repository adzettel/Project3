// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}



TEST(test_player_get_name) {
  // Create a player and verify that get_name() returns the player's name
  Player * alice = Player_factory("Alice", "Simple");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

TEST(test_player_get_name2) {
  // Create a player and verify that get_name() returns the player's name
  Player * alice = Player_factory("Alice", "Human");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

TEST(test_player_factory) {
  // Create a player and verify that get_name() returns the player's name
  Player * alice = Player_factory("Alice", "Human");
  delete alice;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob makes tump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);
  ASSERT_FALSE(bob->make_trump(Card(Card::RANK_ACE, Card::SUIT_HEARTS), false, 1, trump));
  delete bob;
}

TEST(test_simple_player_make_trump3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_SEVEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob makes tump
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump;
  bool orderup = bob->make_trump(
    nine_hearts,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

  delete bob;
}

TEST(test_simple_player_make_trump2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

  // Bob makes tump
  Card test(Card::RANK_TWO, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    test,    // Upcard
    false,           // Bob is also the dealer
    2,              // second round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  ASSERT_NOT_EQUAL(trump, Card::SUIT_HEARTS);
  ASSERT_NOT_EQUAL(trump, Card::SUIT_CLUBS);
  ASSERT_NOT_EQUAL(trump, Card::SUIT_SPADES);
  ASSERT_NOT_EQUAL(trump, Card::SUIT_DIAMONDS);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  bob->add_and_discard(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  Card led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob played
  Card highest_nontrump(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  ASSERT_EQUAL(led, highest_nontrump);
  delete bob;
}

TEST(test_simple_player_play_card2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  delete bob;
}

// Add more tests here

TEST_MAIN()