#include "../Class_Collection/Errors.h"
#include "TestClass.h"

DeckOfCards* TestClass::deck{ nullptr };

::testing::AssertionResult TestClass::fullDeckInit() {
	int expectSuit;
	int excpectRang;

	for (int counter = 0; counter < sizeStandartDeck; ++counter) {
		expectSuit = counter / numberCardsInSuit;
		excpectRang = counter - expectSuit * numberCardsInSuit + 2;

		if (expectSuit != static_cast<int>(deck->getSuit(counter + 1))) {
			return ::testing::AssertionFailure() << "expected suit: " << expectSuit <<
				"but real value: " << static_cast<int>(deck->getSuit(counter + 1));
		}
		
		if (excpectRang != static_cast<int>(deck->getRang(counter + 1))) {
			return ::testing::AssertionFailure() << "expected rang: " << excpectRang <<
				"but real value: " << static_cast<int>(deck->getRang(counter + 1));
		}
	}

	return ::testing::AssertionSuccess();
}

::testing::AssertionResult TestClass::initRandomCards(const int expectNumber) {
	try {
		for (int current = 0; current < expectNumber; ++current) {
			deck->getSuit(current + 1);
		}
	}
	catch (const Exception& exc) {
		return ::testing::AssertionFailure() << exc.what();
	}

	return ::testing::AssertionSuccess();	
}

::testing::AssertionResult TestClass::initOneCard(const int expectSuit, const int expectRang) {
	if (expectRang != static_cast<int>(deck->getRang(1))) {
		return ::testing::AssertionFailure() << "expected rang: " << expectRang <<
			"real value: " << static_cast<int>(deck->getRang(1));
	}

	if (expectSuit != static_cast<int>(deck->getSuit(1))) {
		return ::testing::AssertionFailure() << "expected suit: " << expectSuit <<
			"real value: " << static_cast<int>(deck->getSuit(1));
	}

	return ::testing::AssertionSuccess();
}

::testing::AssertionResult TestClass::addedRandCard() {
	try {
			deck->getSuit(1);
			deck->getRang(1);
	}
	catch (const Exception& exc) {
		return ::testing::AssertionFailure() << exc.what();
	}

	return ::testing::AssertionSuccess();
}

::testing::AssertionResult TestClass::chekInvert(const int numberInit) {
	int expectedSuit;
	int expectedRang;

	for (int current = 1; current <= sizeStandartDeck; ++current) {
		expectedSuit = (current - 1) / numberCardsInSuit;
		expectedRang = static_cast<int>(Card::Rang::ACE) -
			((current - 1) - numberCardsInSuit * expectedSuit);

		if (expectedSuit != static_cast<int>(deck->getSuit(current))) {
			return ::testing::AssertionFailure() << "expected suit: " <<
				expectedSuit << "but real value: " << static_cast<int>(deck->getSuit(current));
		}

		if (expectedRang != static_cast<int>(deck->getRang(current))) {
			return ::testing::AssertionFailure() << "expected rang: " <<
				expectedRang << "but real value: " << static_cast<int>(deck->getRang(current));
		}
	}

	return ::testing::AssertionSuccess();
}

DeckOfCards TestClass::checkSameSuit(const Card::Suit& suit, const int numberInit) {
	DeckOfCards deckSameSuit(0);
	Card bufferCard;

	for (int current = 1; current <= numberInit; ++current) {
		if (static_cast<int>(suit) == static_cast<int>(deck->getSuit(current))) {
			bufferCard.rang = deck->getRang(current);
			bufferCard.suit = deck->getSuit(current);

			deckSameSuit.setCard(bufferCard);
		}
	}

	return deckSameSuit;
}

::testing::AssertionResult TestClass::measureDecks(const DeckOfCards& deck_1, 
	const DeckOfCards& deck_2, const int numberInit) {

	for (int current = 1; current <= numberInit; ++current) {
		if (static_cast<int>(deck_1.getRang(current)) != static_cast<int>(deck_2.getRang(current))) {
			return ::testing::AssertionFailure() << "expected rang: " << static_cast<int>(deck_1.getRang(current)) <<
				"but real value: " << static_cast<int>(deck_2.getRang(current));
		}

		if (static_cast<int>(deck_1.getSuit(current)) != static_cast<int>(deck_2.getSuit(current))) {
			return ::testing::AssertionFailure() << "expected suit: " << static_cast<int>(deck_1.getSuit(current)) <<
				"but real value: " << static_cast<int>(deck_2.getSuit(current));
		}
	}

	return ::testing::AssertionSuccess();
}

::testing::AssertionResult TestClass::checkGetRang() {
	int suit;

	for (int current = 1; current <= sizeStandartDeck; ++current) {
		suit = (current - 1) / numberCardsInSuit;

		if (static_cast<int>(deck->getRang(current)) != current - suit * numberCardsInSuit + 1) {
			return ::testing::AssertionFailure() << "expected rang: " << current - suit * numberCardsInSuit + 1 <<
				"but real value: " << static_cast<int>(deck->getRang(current));
		}
	}

	return ::testing::AssertionSuccess();
}

::testing::AssertionResult TestClass::checkGetRangInverse() {
	int suit;
 
	for (int current = 1; current <= sizeStandartDeck; ++current) {
		suit = (current - 1) / numberCardsInSuit;

		if (static_cast<int>(deck->getRang(current)) != 
			static_cast<int>(Card::Rang::ACE) - (current - suit * numberCardsInSuit) + 1) {
			return ::testing::AssertionFailure() << "expected rang: " << current - suit * numberCardsInSuit + 1 <<
				"but real value: " << static_cast<int>(deck->getRang(current));
		}
	}

	return ::testing::AssertionSuccess();
}

::testing::AssertionResult TestClass::checkGetSuit() {
	int suit;

	for (int current = 1; current <= sizeStandartDeck; ++current) {
		suit = (current - 1) / numberCardsInSuit;

		if (static_cast<int>(deck->getSuit(current)) != suit) {
			return ::testing::AssertionFailure() << "expected rang: " << suit <<
				"but real value: " << static_cast<int>(deck->getSuit(current));
		}
	}

	return ::testing::AssertionSuccess();
}
