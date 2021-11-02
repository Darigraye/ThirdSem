#include "Comparator.h"

bool Comparator::operator()(const Card& firstCard, const Card& secondCard) const noexcept {
	Card compareFirst;
	Card compareSecond;

	if (m_mode == ModeComp::SECOND_GREATER) {
		compareFirst = secondCard;
		compareSecond = firstCard;
	}
	else {
		compareFirst = firstCard;
		compareSecond = secondCard;
	}

	if (static_cast<int>(compareFirst.rang) > static_cast<int>(compareSecond.rang) &&
		(static_cast<int>(compareFirst.suit) == static_cast<int>(compareSecond.suit))) {

		return true;
	}
	
	if (m_mode == ModeComp::FIRST_GEATER &&
		(static_cast<int>(compareFirst.suit) > static_cast<int>(compareSecond.suit)) ||
		m_mode == ModeComp::SECOND_GREATER &&
		(static_cast<int>(compareFirst.suit) < static_cast<int>(compareSecond.suit))) {

		return true;
	}
	else {
		return false;
	}
}