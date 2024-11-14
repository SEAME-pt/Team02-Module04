#include <QtTest/QtTest>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../include/RacingGame.h"
#include "../../include/Car.h"
#include "../../include/CarThread.h"


class MockCar : public Car {
public:
    MOCK_METHOD(int, getPosition, (), (const, override));
    MOCK_METHOD(void, move, (), (override));
    MOCK_METHOD(void, setPosition, (int position), (override));
    MOCK_METHOD(int, getFinishLine, (), (const, override));
};

class MockCarThread : public CarThread {
public:
    MockCarThread(Car *car) : CarThread(car) {}
    MOCK_METHOD(void, run, (), (override));
    MOCK_METHOD(void, updatePosition, (int speed, int dir), (override));
};

TEST(GettersTest, empty) {
    RacingGame race;

    car.setPosition;

    
    EXPECT_EQ(car.getXPosition(), 2);
    EXPECT_EQ(car.getYPosition(), 2);
}
