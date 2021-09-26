#pragma once

#include "gtest/gtest.h"
#include "../MyTractriss/Tractriss.h"

constexpr double pi = 3.141592653589793;

// singlton
class TestClass : public ::testing::Test {
protected:
	static Tractriss* tractriss;

public:

	TestClass() = default;

	~TestClass() = default;

	static void createTestedObject();
	static void deleteTestedObject();

	static double angleOutRange();
	static double angleInRange();

	static double setPositiveValue();	  
	static double setNegativeValue();

	static double setOutOfRange();		  // for getRadius()

	static double setOutRangeTwoAngles(); // for getLenghtDougie() (there two angles)
	static double secondSmallerFirst();

	static Point testCoordinatesOut();

	// functions for calculating the correct values for area, volume, etc.

	inline static double calcArea() noexcept { 
		return (pow(tractriss->getDistance(), 2) * pi) / 2;
	}

	inline static double calcVolume() noexcept {
		return 2 * (pi * pow(tractriss->getDistance(), 3) / 3); 
	}

	inline static double calcSurface() noexcept {
		return 4 * pi * pow(tractriss->getDistance(), 2);
	}

	inline static double calcArcLenght(const double phi_1, const double phi_2) noexcept {
		return tractriss->getDistance() * abs(log(abs(sin(phi_1) / sin(phi_2))));
	}

	inline static double calcRadius(const double phi) noexcept {
		return tractriss->getDistance() / abs(tan(phi));
	}

	static Point calcCoordinates(const double phi) noexcept;
};