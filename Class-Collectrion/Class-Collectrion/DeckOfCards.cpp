#include <iostream>
#include <random>

#include "DeckOfCards.h"
#include "Errors.h"
#include "Input.h"
#include "Comparator.h"

void DeckOfCards::initDeck() noexcept {
	if (m_type == TypeLocationCards::USUAL) {
		int rang{ static_cast<int>(Card::Rang::TWO) },			// counters with which we 
			suit{ static_cast<int>(Card::Suit::DIAMONDS) };		// will go through the enumerators

		for (auto& current : m_deck) {
			current.rang = static_cast<Card::Rang>(rang++);
			current.suit = static_cast<Card::Suit>(suit);

			// one suit fully initialized
			if (rang > static_cast<int>(Card::Rang::ACE)) {
				rang = static_cast<int>(Card::Rang::TWO);
				++suit;											// consider the next suit
			}
		}
	}
	else {
		int rang{ static_cast<int>(Card::Rang::ACE) },
			suit{ static_cast<int>(Card::Suit::DIAMONDS) };

		for (auto& current : m_deck) {
			current.rang = static_cast<Card::Rang>(rang--);
			current.suit = static_cast<Card::Suit>(suit);

			if (rang < static_cast<int>(Card::Rang::TWO)) {
				rang = static_cast<int>(Card::Rang::ACE);
				++suit;										
			}
		}
	}
	
}

void DeckOfCards::arrangeDeck() noexcept {
	Comparator comp;

	if (m_type == TypeLocationCards::INVERSION) {
		comp.setMode(ModeComp::SECOND_GREATER);
	}

	Card bufferCard;
	bool flag;

	for (int currentJ = 1; currentJ < sizeStandartDeck; ++currentJ) {
		flag = false;

		for (int currentI = 0; currentI < sizeStandartDeck - currentJ; ++currentI) {
			if (comp(m_deck[currentI], m_deck[currentI + 1]) == true) {
				 
				bufferCard = m_deck[currentI];
				m_deck[currentI] = m_deck[currentI + 1];
				m_deck[currentI + 1] = bufferCard;

				flag = true;
			}
		}

		if (flag == false) {
			break;
		}
	}
}

DeckOfCards::DeckOfCards() noexcept {
	initDeck();

	for (auto& current : m_deck) {
		current.mode = Card::Mode::INIT;
	}

	m_init = ModeInitDeck::FULL_INIT;
}

DeckOfCards::DeckOfCards(int number) {
	if (number > 52 || number < 0) {
		throw Exception("Number out of range (number must be > -1 and < 53\n");
	}

	initDeck();

	std::random_device randomNumber;								
	std::mt19937 mersenne{ randomNumber() };
	std::uniform_int_distribution<> rd{ 0, sizeStandartDeck - 1 };
	
	int maxIndex{ sizeStandartDeck };		// to generate only those numbers that are in the range
	int* indeces{ new int[number] };		// array of indeces cards

	Card bufferCard;

	// We send the generated playing cards to the end of the array and narrow the range 
	// of generated indices (the random index will be guaranteed to belong to the uninitialized card)
	for (int current = 0; current < number; ++current) {
		indeces[current] = rd(mersenne) % maxIndex;
		--maxIndex;
		
		m_deck[indeces[current]].mode = Card::Mode::INIT;

		// put the initialized map at the end of the array
		bufferCard = m_deck[indeces[current]];
		m_deck[indeces[current]] = m_deck[maxIndex];
		m_deck[maxIndex] = bufferCard;
	}

	arrangeDeck();								// we arrange the cards in the desired order

	if (number == sizeStandartDeck) {
		m_init = ModeInitDeck::FULL_INIT;
	}

	delete[] indeces;
}

DeckOfCards::DeckOfCards(const Card::Rang& rang, const Card::Suit& suit) {
	if (m_init == ModeInitDeck::FULL_INIT) {
		throw Exception("Full deck\n");
	}

	initDeck();

	// calculalate index of card with rang and suit this cart
	int index{ static_cast<int>(suit) * numberCardsInSuit + static_cast<int>(rang) - 2 };

	m_deck[index].mode = Card::Mode::INIT;
}

void DeckOfCards::inDeck(std::istream& in, std::ostream& out) {
	std::string suit;
	int rang;

	Card card;

	do {
		getValue(suit, in, out);
		getValue(rang, in, out);

		if (suit != "DMDS" && suit != "HTS" && suit != "PEAKS" && suit != "CLUBS" &&
			suit != "DIAMONDS" && suit != "HEARTS") { 
			out << "Incorrect suit, please repeate\n";

			continue;
		}
		else {
			break;
		}

	} while (true);

	if (rang > static_cast<int>(Card::Rang::ACE) || rang < static_cast<int>(Card::Rang::TWO)) {
		throw Exception("Rang out of range ( < 2 or > 14)\n");
	}

	card.rang = static_cast<Card::Rang>(rang);

	if (suit == "DMDS" || suit == "DIAMONDS") {
		card.suit = Card::Suit::DIAMONDS;
	}

	if (suit == "HTS" || suit == "HEARTS") {
		card.suit = Card::Suit::HEARTS;
	}

	if (suit == "PEAKS") {
		card.suit = Card::Suit::PEAKS;
	}

	if (suit == "CLUBS") {
		card.suit = Card::Suit::CLUBS;
	}

	int index;

	if (m_type == TypeLocationCards::USUAL) {
		index = static_cast<int>(card.suit) * numberCardsInSuit + static_cast<int>(card.rang) - 2;
	}
	else {
		index = static_cast<int>(card.suit) * numberCardsInSuit + numberCardsInSuit - static_cast<int>(card.rang) + 1;
	}

	m_deck[index].mode = Card::Mode::INIT;
}

void DeckOfCards::outDeck(std::ostream& out) const noexcept {
	std::string suit;
	bool flagInit{ false }; // checking for the presence of at least one card in the deck

	for (auto& current : m_deck) {
		if (current.mode == Card::Mode::INIT) {
			flagInit = true;

			out << "|Rang: " << static_cast<int>(current.rang);

			switch (current.suit) {
			case Card::Suit::DIAMONDS:
				suit = "DIAMONDS|\n";
				break;
			case Card::Suit::HEARTS:
				suit = "HEARTS|\n";
				break;
			case Card::Suit::PEAKS:
				suit = "PEAKS|\n";
				break;
			case Card::Suit::CLUBS:
				suit = "CLUBS|\n";
				break;
			}

			out << " Suit: " << suit << '\n';
		}
	}

	if (flagInit == false) {
		out << "No cards in the deck\n" << '\n';
	}
}

void DeckOfCards::addRandomCard() {
	if (m_init == ModeInitDeck::FULL_INIT) {
		throw Exception("Full deck\n");
	}

	int maxIndex{ sizeStandartDeck };
	Card bufferCard;

	// similarly DeckOfCards.cpp (67)
	for (int current = 0; current < sizeStandartDeck; ++current) {
		if (m_deck[current].mode == Card::Mode::INIT) {
			--maxIndex;

			bufferCard = m_deck[current];
			m_deck[current] = m_deck[maxIndex];
			m_deck[maxIndex] = bufferCard;
		}
	}

	std::random_device randomNumber;
	std::mt19937 mersenne{ randomNumber() };
	std::uniform_int_distribution<> rd{ 0, maxIndex - 1 };
	
	int index = rd(mersenne);

	m_deck[index].mode = Card::Mode::INIT;

	arrangeDeck();												// similary DeckOfCards.cpp (81)
}

void DeckOfCards::setCard(const Card& card) {
	int index{ static_cast<int>(card.suit) * numberCardsInSuit + static_cast<int>(card.rang) - 2 };

	if (m_deck[index].mode == Card::Mode::INIT) {
		throw Exception("This card was initialized before\n");
	}

	m_deck[index].mode = Card::Mode::INIT;
}

Card::Suit DeckOfCards::getSuit(const int number) const {
	if (number <= 0 || number > 52) {
		throw Exception("Number out of range (number must be > 0 and < 53");
	}

	int numberInit{ 0 }; // number of initialized cards
	Card::Suit returnSuit;

	for (auto& current : m_deck) {
		if (current.mode == Card::Mode::INIT) {
			++numberInit;
		}

		if (numberInit == number) {
			returnSuit = current.suit;
			break;
		}
	}

	if (numberInit == number) {
		return returnSuit;
	}
	// if the number of initialized elements is less than the specified number
	throw Exception("Number number out of range init. cards\n"); 
}

Card::Rang DeckOfCards::getRang(const int number) const {
	if (number <= 0 || number > 52) {
		throw Exception("Number out of range (number must be > 0 and < 53");
	}

	int numberInit{ 0 }; // number of initialized cards
	Card::Rang returnRang;

	for (auto& current : m_deck) {
		if (current.mode == Card::Mode::INIT) {
			++numberInit;
		}

		if (numberInit == number) {
			returnRang = current.rang;
			break;
		}
	}

	if (numberInit == number) {
		return returnRang;
	}
	// if the number of initialized elements is less than the specified number
	throw Exception("Number of number out of range init. cards\n");
}

void DeckOfCards::inverseDeck() noexcept {
	m_type = TypeLocationCards::INVERSION;

	initDeck();

	// reinitialization

	for (int current = 0; current < sizeStandartDeck; ++current) {
		if (m_deck[current].rang == Card::Rang::EIGHT) {
			current += static_cast<int>(Card::Rang::ACE) -		// move on to the next suit, because to completely 
				static_cast<int>(Card::Rang::EIGHT) + 1;		// replace one suit, it is enough to pass exactly half of the cards

			if (current == 52) {
				break;
			}
		}													

		Card::Mode bufferMode{ m_deck[current].mode };

		int numberSuit{ current / (numberCardsInSuit - 1) };
		int inverseCurrent{ (numberCardsInSuit - current % numberCardsInSuit - 1) +
														numberSuit * numberCardsInSuit };

		m_deck[current].mode = m_deck[inverseCurrent].mode;
		m_deck[inverseCurrent].mode = bufferMode;
	}
}

DeckOfCards& DeckOfCards::getCardsSameSuit(const Card::Suit& suit, DeckOfCards& outDeck) const noexcept { 
	int numberCardsSameSuit{ 0 };

	int startIndex{ static_cast<int>(suit) * numberCardsInSuit };
	int endIndex{ startIndex + static_cast<int>(Card::Rang::ACE) - 1 };

	for (int current = startIndex; current < endIndex; ++current) {
		if (m_deck[current].mode == Card::Mode::INIT) {
			outDeck.m_deck[current].mode = Card::Mode::INIT;

			++numberCardsSameSuit;			
		}
	}
	
	return outDeck;
}