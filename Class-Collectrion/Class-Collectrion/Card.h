#pragma once

struct Card { 
	enum class Mode {
		NON_INIT = 0, 
		INIT = 1,
	};

	enum class Suit {
		DIAMONDS = 0,
		HEARTS = 1,
		PEAKS = 2,
		CLUBS = 3,
	};

	enum class Rang {
		TWO = 2,
		THREE = 3,
		FOUR = 4,
		FIVE = 5,
		SIX = 6,
		SEVEN = 7,
		EIGHT = 8,
		NINE = 9,
		TEN = 10,
		JACK = 11,
		QUEEN = 12,
		KING = 13,
		ACE = 14,
	};

	Mode mode = Mode::NON_INIT;
	Suit suit;
	Rang rang;
};