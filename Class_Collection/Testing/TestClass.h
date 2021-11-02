#pragma once
#include "gtest/gtest.h"
#include "../Class_Collection/DeckOfCards.h"

class TestClass : public ::testing::Test {
protected:
	static DeckOfCards* deck;

public:

	static inline void createObj() { deck = new DeckOfCards; }
	static inline void createObj(const int number) { deck = new DeckOfCards{ number }; }
	static inline void createObj(const Card::Suit& suit, const Card::Rang& rang) {
		deck = new DeckOfCards(rang, suit);
	}
	static inline void deleteObj() { delete deck; }

	static ::testing::AssertionResult fullDeckInit();
	static ::testing::AssertionResult initRandomCards(const int expectNumber);
	static ::testing::AssertionResult initOneCard(const int expectSuit, const int expectRang);

	static ::testing::AssertionResult checkGetRang();
	static ::testing::AssertionResult checkGetRangInverse();
	static ::testing::AssertionResult checkGetSuit();

	static ::testing::AssertionResult addedRandCard();
	static ::testing::AssertionResult chekInvert(const int numberInit);			// for full deck
	static DeckOfCards checkSameSuit(const Card::Suit& suit, const int numberInit);
	static ::testing::AssertionResult measureDecks(const DeckOfCards& deck_1, 
		const DeckOfCards& deck_2, const int numberInit);

	// testing of overloading operators

	//static ::testing::AssertionResult checkCompare();
};

