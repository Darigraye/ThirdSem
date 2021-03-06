#pragma once

#include <iostream>

#include "Card.h"

constexpr int sizeStandartDeck = 52;
constexpr int numberCardsInSuit = 13;

class DeckOfCards {
private:
	enum class ModeInitDeck {
		NON_FULL_INIT = 0,
		FULL_INIT = 1,			   // deck is full
	};

	enum class TypeLocationCards {
		USUAL = 0,				   // in ascending order of rank	
		INVERSION = 1,			   // in reverse order
	};

	ModeInitDeck m_init = ModeInitDeck::NON_FULL_INIT;
	TypeLocationCards m_type = TypeLocationCards::USUAL;

	Card m_deck[sizeStandartDeck]; // type of relation - composition
	
	void initDeck() noexcept;	   // define an array of cards in a specific sequence
	void arrangeDeck() noexcept;   // ordering the deck of cards in order of 
								   // suit and increasing rank (for methods with random card generation)
public:
	DeckOfCards() noexcept;
	explicit DeckOfCards(const int number);
	DeckOfCards(const Card::Rang& rang, const Card::Suit& suit);

	void addRandomCard();
	void inverseDeck() noexcept;

	Card::Suit getSuit(const int number) const;
	Card::Rang getRang(const int number) const;
	int getCardsSameSuit(const Card::Suit& suit, DeckOfCards& outCard) const noexcept; // returnes size of array outCard

	void setCard(const Card& card);

	const Card& operator[](const int index) const;
	DeckOfCards& operator+=(const DeckOfCards& deck) noexcept;
	DeckOfCards& operator++();
	DeckOfCards& operator++(int);
	operator int() const noexcept;

	friend std::ostream& operator<<(std::ostream& out, const DeckOfCards& deck);
	friend std::istream& operator>>(std::istream& in, DeckOfCards& deck);

	friend bool operator==(const DeckOfCards& deck_1, const DeckOfCards& deck_2);
	friend bool operator!=(const DeckOfCards& deck_1, const DeckOfCards& deck_2);
	friend bool operator<(const DeckOfCards& deck_1, const DeckOfCards& deck_2);
	friend bool operator>(const DeckOfCards& deck_1, const DeckOfCards& deck_2);
	friend bool operator>=(const DeckOfCards& deck_1, const DeckOfCards& deck_2);
	friend bool operator<=(const DeckOfCards& deck_1, const DeckOfCards& deck_2);

	friend DeckOfCards operator+(const DeckOfCards& deck_1, const DeckOfCards& deck_2);

};

