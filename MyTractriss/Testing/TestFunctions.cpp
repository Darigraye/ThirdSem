#include <random>
#include <limits>

#include "TestFunction.h"

constexpr double pi = 3.141592653589793;

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
    tractriss->setDistance(expectEqual);

    return expectEqual;
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

double TestClass::setInRange() {
    double phi{ angleInRange() };

    return tractriss->getRadius(phi);
}

double TestClass:: setOutRangeTwoAngles() {
    double phi_1{ angleOutRange() };
    double phi_2{ angleOutRange() };

    return tractriss->getDougieLength(phi_1, phi_2);
}

double TestClass::setInRangeTwoAngles() {
    double phi_1{ angleInRange() };
    double phi_2{ phi_1 + 1e-8 };

    return tractriss->getDougieLength(phi_1, phi_2);
}

double TestClass::secondSmallerFirst() {
    double phi_1{ angleInRange() };
    double phi_2{ phi_1 / 2 };

    return tractriss->getDougieLength(phi_1, phi_2);
}

CodeErrors TestClass::testCoordinatesOut() {
    double phi{ angleOutRange() };

    return tractriss->getCoordinates(phi, Point());
}

CodeErrors TestClass::testCoordinatesIn() {
    double phi{ angleInRange() };

    return tractriss->getCoordinates(phi, Point());
}

