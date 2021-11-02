#pragma once

#include "Card.h"

enum class ModeComp {
	FIRST_GEATER = 0,
	SECOND_GREATER = 1,
};

class Comparator {
private:
	mutable ModeComp m_mode = ModeComp::FIRST_GEATER;

public:
	void setMode(const ModeComp& mode) noexcept { m_mode = mode; }
	bool operator()(const Card& firstCard, const Card& secondCard) const noexcept;
};