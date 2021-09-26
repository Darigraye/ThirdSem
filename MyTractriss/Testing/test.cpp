#include "../MyTractriss/Tractriss.h"
#include "../MyTractriss/Errors.h"
#include "gtest/gtest.h"
#include "TestFunction.h"

TEST_F(TestClass, TestSetValues) {
    TestClass::createTestedObject();

    EXPECT_EQ(TestClass::tractriss->getDistance(), 0); // testing the default constructor

    double expectEqual{ TestClass::setPositiveValue() };
    EXPECT_NEAR(TestClass::tractriss->getDistance(), expectEqual, 1e-15);
    
    EXPECT_THROW(TestClass::setNegativeValue(), Exception);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetRadius) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_THROW(TestClass::setOutOfRange(), Exception);

    double phi{ angleInRange() };

    EXPECT_NEAR(TestClass::tractriss->getRadius(phi), TestClass::calcRadius(phi), 1e-15);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetDougie) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_THROW(TestClass::setOutRangeTwoAngles(), Exception);

    EXPECT_THROW(TestClass::secondSmallerFirst(), Exception);

    double phi_1{ angleInRange() };
    double phi_2{ phi_1 + 1e-8 };

    EXPECT_NEAR(TestClass::tractriss->getDougieLength(phi_1, phi_2), 
        TestClass::calcArcLenght(phi_1, phi_2), 1e-15);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetArea) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_NEAR(TestClass::tractriss->getArea(), TestClass::calcArea(), 1e-15);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetVolume) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_NEAR(TestClass::tractriss->getVolume(), TestClass::calcVolume(), 1e-15);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetSurface) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_NEAR(TestClass::tractriss->getSurface(), TestClass::calcSurface(), 1e-15);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetCoordinates) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();
    
    EXPECT_THROW(TestClass::testCoordinatesOut(), Exception);

    double phi{ angleInRange() };

    EXPECT_NEAR(TestClass::tractriss->getCoordinates(phi).x, 
        TestClass::calcCoordinates(phi).x, 1e-15);

    EXPECT_NEAR(TestClass::tractriss->getCoordinates(phi).y,
        TestClass::calcCoordinates(phi).y, 1e-15);

    TestClass::deleteTestedObject();
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    const int numberTests = 100; // can be specified with argv

    for (int current = 0; current < numberTests; ++current) {
        RUN_ALL_TESTS();
    }

    return 0;
}