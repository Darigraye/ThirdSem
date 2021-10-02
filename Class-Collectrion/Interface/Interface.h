#pragma once

#include <string>

#include "../Class-Collectrion/DeckOfCards.h"

class Interface {
private:
	enum class Init {
		NON_INIT_DECK = 0,
		INIT_DECK = 1,
	};

	DeckOfCards m_myDeck;

	const std::string m_msgs[11] = { "0.Exit\n", "1.Init all\n", "2.Init random\n", "3.Init specific card\n",
	"4.Input card\n", "5.Out deck\n", "6.Add random card\n", "7.Inverse deck\n", "8.Get suit\n", "9.Get rang\n",
		"10. Get group card\n" };

	Init m_mode = Init::NON_INIT_DECK;

public:
	void menu();
};
