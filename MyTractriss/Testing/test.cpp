#include "../MyTractriss/Tractriss.h"
#include "gtest/gtest.h"
#include "TestFunction.h"

TEST_F(TestClass, TestSetValues) {
    TestClass::createTestedObject();

    EXPECT_EQ(TestClass::tractriss->getDistance(), 0); // testing the default constructor

    double expectEqual{ TestClass::setPositiveValue() };
    EXPECT_NEAR(TestClass::tractriss->getDistance(), expectEqual, 1e-15);


    expectEqual = TestClass::setNegativeValue();
    EXPECT_NEAR(TestClass::tractriss->getDistance(), expectEqual, 1e-15);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetRadius) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_NEAR(TestClass::setOutOfRange(), -1, 1e-15);

    EXPECT_GT(TestClass::setInRange(), 0);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetDougie) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_NEAR(TestClass::setOutRangeTwoAngles(), -1, 1e-15);

    EXPECT_GT(TestClass::setInRangeTwoAngles(), 0);

    EXPECT_EQ(TestClass::secondSmallerFirst(), -1);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetArea) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_GT(TestClass::tractriss->getArea(), 0);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetVolume) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_GT(TestClass::tractriss->getVolume(), 0);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetSurface) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();

    EXPECT_GT(TestClass::tractriss->getSurface(), 0);

    TestClass::deleteTestedObject();
}

TEST_F(TestClass, TestGetCoordinates) {
    TestClass::createTestedObject();
    TestClass::setPositiveValue();
    
    EXPECT_EQ(TestClass::testCoordinatesOut(), CodeErrors::USER_FAIL);

    EXPECT_EQ(TestClass::testCoordinatesIn(), CodeErrors::SUCCESS);

    TestClass::deleteTestedObject();
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}