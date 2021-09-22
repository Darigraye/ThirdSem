#pragma once

#include "gtest/gtest.h"
#include "../MyTractriss/Tractriss.h"

// singlton
class TestClass : public ::testing::Test {
protected:
	static Tractriss* tractriss;

	static double angleOutRange();
	static double angleInRange();

public:

	TestClass() = default;

	~TestClass() = default;

	static void createTestedObject();
	static void deleteTestedObject();

	static double setPositiveValue();	  
	static double setNegativeValue();

	static double setOutOfRange();		  // for getRadius()
	static double setInRange();

	static double setOutRangeTwoAngles(); // for getLenghtDougie() (there two angles)
	static double setInRangeTwoAngles();
	static double secondSmallerFirst();

	static CodeErrors testCoordinatesOut();
	static CodeErrors testCoordinatesIn();
};