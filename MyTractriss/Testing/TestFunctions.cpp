#include <random>
#include <limits>
#include <cmath>

#include "TestFunction.h"

Tractriss* TestClass::tractriss{ nullptr };

void TestClass::createTestedObject() {
    tractriss =  new Tractriss;
}

void TestClass::deleteTestedObject() {
    delete tractriss;
}

double TestClass::setPositiveValue() {
    std::random_device number;
    std::mt19937 mersenne(number());
    std::uniform_real_distribution<> rd(0, std::numeric_limits<double>::max());

    double expectEqual{ rd(mersenne) };
    tractriss->setDistance(std::pow(expectEqual, static_cast<double>(1 / 3)));
    
    return std::pow(expectEqual, static_cast<double>(1 / 3));
}

double TestClass::setNegativeValue() {
    std::random_device number;       // A little code duplication in order to save test 
    std::mt19937 mersenne(number()); // performance (so as not to create a function that returns by value)
    std::uniform_real_distribution<> rd(-std::numeric_limits<double>::max(), 0);

    double expectEqual{ tractriss->getDistance() };
    tractriss->setDistance(rd(mersenne));

    return expectEqual;
}

double TestClass::angleInRange() {
    std::random_device number;
    std::mt19937 mersenne(number());
    std::uniform_real_distribution<> rd(0, pi);

    return rd(mersenne);
}

double TestClass::angleOutRange() {
    std::random_device number;
    std::mt19937 mersenne(number());
    std::uniform_real_distribution<> rd(pi, std::numeric_limits<double>::max());

    return rd(mersenne);
}

double TestClass::setOutOfRange() {
    double phi{ angleOutRange() };

    return tractriss->getRadius(phi);
}

double TestClass:: setOutRangeTwoAngles() {
    double phi_1{ angleOutRange() };
    double phi_2{ angleOutRange() };

    return tractriss->getDougieLength(phi_1, phi_2);
}

double TestClass::secondSmallerFirst() {
    double phi_1{ angleInRange() };
    double phi_2{ phi_1 / 2 };

    return tractriss->getDougieLength(phi_1, phi_2);
}

Point TestClass::testCoordinatesOut() {
    double phi{ angleOutRange() };

    return tractriss->getCoordinates(phi);
}

Point TestClass::calcCoordinates(double phi) noexcept {
    Point point;

    point.x = tractriss->getDistance() * (log(tan(phi / 2)) + cos(phi));
    point.y = tractriss->getDistance() * abs(sin(phi));

    return point;
}

