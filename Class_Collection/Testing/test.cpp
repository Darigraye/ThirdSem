#include <random>

#include "../Class_Collection/DeckOfCards.h"
#include "../Class_Collection/Errors.h"
#include "gtest/gtest.h"
#include "TestClass.h"

TEST_F(TestClass, TestConstructor_1) {
	TestClass::createObj();
	EXPECT_TRUE(TestClass::fullDeckInit());
	TestClass::deleteObj();
}

TEST_F(TestClass, TestConstructor_2) {
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> range(0, sizeStandartDeck);

	int numberInitCards{ range(mersenne) };
	TestClass::createObj(numberInitCards);
	EXPECT_TRUE(TestClass::initRandomCards(numberInitCards));
	EXPECT_FALSE(TestClass::initRandomCards(numberInitCards + 1));
 
	TestClass::deleteObj();
}

TEST_F(TestClass, TestConstructor_3) {
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> range(0, sizeStandartDeck);

	int suit{ range(mersenne) % 4 };
	int rang{ range(mersenne) % numberCardsInSuit + 2 };

	TestClass::createObj(static_cast<Card::Suit>(suit), static_cast<Card::Rang>(rang));
	EXPECT_TRUE(TestClass::initOneCard(suit, rang));
	TestClass::deleteObj();
}

TEST_F(TestClass, TestAddRandomCard) {
	TestClass::createObj();
	EXPECT_THROW(deck->addRandomCard(), Exception);
	TestClass::deleteObj();

	TestClass::createObj(0);
	TestClass::deck->addRandomCard();
	EXPECT_TRUE(TestClass::addedRandCard());
	TestClass::deleteObj();
}

TEST_F(TestClass, TestInveresdeck) {
	int numberInitCards{ sizeStandartDeck };

	TestClass::createObj(numberInitCards);
	TestClass::deck->inverseDeck();

	EXPECT_TRUE(TestClass::chekInvert(numberInitCards));

	TestClass::deleteObj();
	TestClass::createObj(0);

	TestClass::deck->inverseDeck();
	EXPECT_THROW(TestClass::deck->getSuit(1), Exception);

	TestClass::deleteObj();
}

TEST_F(TestClass, TestSameSuit) {
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> range(1, sizeStandartDeck);

	int numberCardInit{ range(mersenne) };
	int suit{ range(mersenne) % 4 };

	TestClass::createObj(numberCardInit);
	DeckOfCards deckSameSuit(0);

	int numberCardsSameSuit{ TestClass::deck->getCardsSameSuit(static_cast<Card::Suit>(suit), deckSameSuit) };
	DeckOfCards expectedDeck = TestClass::checkSameSuit(static_cast<Card::Suit>(suit), numberCardInit);
	
	EXPECT_TRUE(TestClass::measureDecks(expectedDeck, deckSameSuit, numberCardsSameSuit));
		
	TestClass::deleteObj();
	TestClass::createObj(0);

	DeckOfCards deckSameSuit_1(0);

	numberCardsSameSuit = TestClass::deck->getCardsSameSuit(static_cast<Card::Suit>(suit), deckSameSuit_1);
	expectedDeck = TestClass::checkSameSuit(static_cast<Card::Suit>(suit), 0);

	EXPECT_TRUE(TestClass::measureDecks(expectedDeck, deckSameSuit_1, numberCardsSameSuit));

	TestClass::deleteObj();
}

TEST_F(TestClass, TestGetRang) {
	TestClass::createObj();
	EXPECT_TRUE(TestClass::checkGetRang());
	TestClass::deleteObj();

	TestClass::createObj();
	TestClass::deck->inverseDeck();
	EXPECT_TRUE(TestClass::checkGetRangInverse());

	TestClass::deleteObj();
	TestClass::createObj(0);

	EXPECT_THROW(TestClass::deck->getRang(1), Exception);

	TestClass::deleteObj();
}

TEST_F(TestClass, TestGetSuit) {
	TestClass::createObj();
	EXPECT_TRUE(TestClass::checkGetSuit());
	TestClass::deleteObj();

	TestClass::createObj();
	TestClass::deck->inverseDeck();
	EXPECT_TRUE(TestClass::checkGetSuit());

	TestClass::deleteObj();
	TestClass::createObj(0);

	EXPECT_THROW(TestClass::deck->getSuit(1), Exception);

	TestClass::deleteObj();
}

//test overloading of operators

TEST_F(TestClass, TestIndexes) {
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> range(0, sizeStandartDeck);

	int numberInit{ range(mersenne) };
	TestClass::createObj(numberInit);

	for (int current = 0; current < numberInit; ++current) {
		EXPECT_EQ(static_cast<int>(TestClass::deck->getRang(current + 1)), 
			static_cast<int>(TestClass::deck->operator[](current).rang));

		EXPECT_EQ(static_cast<int>(TestClass::deck->getSuit(current + 1)),
			static_cast<int>(TestClass::deck->operator[](current).suit));
	}

	TestClass::deleteObj();
	TestClass::createObj(0);

	EXPECT_THROW(TestClass::deck->operator[](1), std::out_of_range);

	TestClass::deleteObj();
}

TEST_F(TestClass, TestCompare) {
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> range(1, sizeStandartDeck);

	int numberInit{ range(mersenne) };
	TestClass::createObj(numberInit);
	DeckOfCards copyDeck = *(TestClass::deck);

	EXPECT_TRUE(*(TestClass::deck) == copyDeck);

	TestClass::deleteObj();
	TestClass::createObj(0);

	copyDeck = (*TestClass::deck);

	EXPECT_TRUE((*TestClass::deck) == copyDeck);

	TestClass::deleteObj();
}

TEST_F(TestClass, TestGreater) {
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> range(0, sizeStandartDeck);

	int numberInit{ range(mersenne) };
	TestClass::createObj(numberInit);
	DeckOfCards secondDeck(sizeStandartDeck - numberInit);

	if (numberInit > sizeStandartDeck / 2) {
		EXPECT_TRUE(secondDeck < *(TestClass::deck));
		EXPECT_TRUE(secondDeck <= *(TestClass::deck));
		EXPECT_FALSE(secondDeck > *(TestClass::deck));
		EXPECT_FALSE(secondDeck >= *(TestClass::deck));
	}

	if (numberInit < sizeStandartDeck / 2) {
		EXPECT_TRUE(*(TestClass::deck) < secondDeck);
		EXPECT_TRUE(*(TestClass::deck) <= secondDeck);
		EXPECT_FALSE(*(TestClass::deck) > secondDeck);
		EXPECT_FALSE(*(TestClass::deck) >= secondDeck);
	}

	TestClass::deleteObj();
	TestClass::createObj(0);

	DeckOfCards secondDeck_1(sizeStandartDeck);
	
	EXPECT_TRUE(*(TestClass::deck) < secondDeck_1);
	EXPECT_TRUE(*(TestClass::deck) <= secondDeck_1);
	EXPECT_FALSE(*(TestClass::deck) > secondDeck_1);
	EXPECT_FALSE(*(TestClass::deck) >= secondDeck_1);

	TestClass::deleteObj();
}

TEST_F(TestClass, TestSum) {
	TestClass::createObj(0);
	(*(TestClass::deck))++;

	EXPECT_EQ(static_cast<int>(*(TestClass::deck)), 1);
	TestClass::deleteObj();

	TestClass::createObj(Card::Suit::CLUBS, Card::Rang::FIVE);
	DeckOfCards secondDeck(Card::Rang::FIVE, Card::Suit::CLUBS);

	DeckOfCards sum = *(TestClass::deck) + secondDeck;
	EXPECT_TRUE(sum == *(TestClass::deck));

	TestClass::deleteObj();
}

TEST_F(TestClass, TestInOut) {
	std::string str = "3 D\n";
	std::istringstream istr(str);
	std::ostringstream ostr;

	TestClass::createObj(0);
	istr >> (*(TestClass::deck));

	EXPECT_EQ(static_cast<int>(TestClass::deck->getRang(1)), 3);
	EXPECT_EQ(static_cast<int>(TestClass::deck->getSuit(1)), 0);

	ostr << (*(TestClass::deck));
	std::string outString = ostr.str(); 
	std::string expectString = "|Rang: 3 Suit: DIAMONDS|\n\n";
	EXPECT_EQ(expectString, outString);

	TestClass::deleteObj();

	TestClass::createObj(0);
	str = "3";
	std::istringstream istr_2(str);
	istr_2 >> (*(TestClass::deck));
	EXPECT_TRUE(istr_2.eof());

	TestClass::deleteObj();
}

int main(int arcg, char* argv[]) {
	::testing::InitGoogleTest(&arcg, argv);
	const int numberTests = 100;

	for (int counter = 0; counter < numberTests; ++counter) {
		RUN_ALL_TESTS();
	}

	return 0;
}