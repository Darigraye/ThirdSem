#include <iostream>

#include "Interface.h"
#include "../Class-Collectrion/DeckOfCards.h"
#include "../Class-Collectrion/Errors.h"
#include "../Class-Collectrion/Input.h"

using std::cin;
using std::cout;
using std::endl;

void Interface::menu() {
	try {
		int mode;

		do {
			for (auto& current : m_msgs) {
				cout << current;
			}

			cout << '\n';

			getValue(mode, cin, cout);

			switch (mode) {
			case 0:
				break;
			case 1: {
				if (m_mode == Init::INIT_DECK) {
					cout << "Failure. This deck initialized until this\n" << endl;
				}
				else {
					DeckOfCards deckOne;
					m_myDeck = deckOne;
					m_mode = Init::INIT_DECK;
				}

				break;
			}
			case 2: {
				if (m_mode == Init::INIT_DECK) {
					cout << "Failure. This deck initialized until this\n" << endl;
				}
				else {
					cout << "Input number cards: ";

					int numberCards;
					getValue(numberCards, cin, cout);

					DeckOfCards deckTwo(numberCards);
					m_myDeck = deckTwo;
					m_mode = Init::INIT_DECK;
				}

				break;
			}
			case 3: {
				if (m_mode == Init::INIT_DECK) {
					cout << "Failure. This deck initialized until this\n" << endl;
				}
				else {
					cout << "Input suit card: ";

					int suit;
					getValue(suit, cin, cout);

					cout << "\n Input rang card: ";

					int rang;
					getValue(rang, cin, cout);

					if (suit < 0 || suit > 3 || rang > 14 || rang < 2) {
						cout << "Error! Incorrect suit or rang\n";
						break;
					}

					Card card;
					card.rang = static_cast<Card::Rang>(rang);
					card.suit = static_cast<Card::Suit>(suit);

					DeckOfCards deckThree(card.rang, card.suit);
					m_myDeck = deckThree;
					m_mode = Init::INIT_DECK;
				}

				break;
			}
			case 4:
				cout << "Input first suit and second deck: ";
				m_myDeck.inDeck(cin, cout);

				break;
			case 5:
				m_myDeck.outDeck(cout);
				break;
			case 6:
				m_myDeck.addRandomCard();
				break;
			case 7:
				m_myDeck.inverseDeck();
				break;
			case 8: {
				cout << "Input number card: ";

				int numberCard;
				getValue(numberCard, cin, cout);

				Card::Suit s = m_myDeck.getSuit(numberCard);

				cout << "Suit = " << static_cast<int>(s) << '\n' << endl;

				break;
			}
			case 9: {
				cout << "Input number card: ";

				int number;
				getValue(number, cin, cout);

				Card::Rang r = m_myDeck.getRang(number);

				cout << "Rang = " << static_cast<int>(r) << '\n' << endl;

				break;
			}
				
			case 10: {
				cout << "Input suit: ";

				int suitCard;
				getValue(suitCard, cin, cout);

				if (suitCard < 0 || suitCard > 3) {
					cout << "Incorrect suit\n" << endl;
					break;
				}

				DeckOfCards deckSameSuit{ 0 };
				deckSameSuit = m_myDeck.getCardsSameSuit(static_cast<Card::Suit>(suitCard), deckSameSuit);

				int startIndex{ static_cast<int>(suitCard) };
				
				deckSameSuit.outDeck(cout);

				cout << endl;
				break;
			}
				
			default: {
				cout << "Oooops! You inpute incorrect mode! Try again\n" << endl;
				break;
			}
				
			} 

		} while (mode != 0);

	}
	catch (const Exception& exc) {
		cout << exc.what() << endl;
	}
	catch (const std::istream::failure& exc) {
		cout << exc.what() << endl;
	}
}