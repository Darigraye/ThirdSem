#pragma once

#include <iostream>

#include "../MyTractriss/Tractriss.h"

constexpr short maxSizeMenu{ 9 };

constexpr short minSizeMenu{ 0 };

class Interface {
private:
	const std::string m_messages[10] { "0.Exit", "1.Set distance", "2.Get distance", "3.Get area", "4.Get volume", 
	"5.Get Surface", "6.Get dougie lenght", "7.Get radius", "8.Get coordinates", "9.Out equation by tractriss"};

	Tractriss m_tractriss;

	enum class ModeInterface {
		NULL_VALUE = 0, // Initialized by zero value
		INIT = 1,		// Initialized not by zero value
	};

	ModeInterface m_mode = ModeInterface::NULL_VALUE;

public:
	Interface() { }

	~Interface() { }

	void menu();
};