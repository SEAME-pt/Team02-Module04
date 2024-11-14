#include <gtest/gtest.h>
#include <QSignalSpy>
#include "../../include/Car.h"

TEST(Car_GettersTest, empty) {
    Car car;
    
    EXPECT_EQ(car.getXPosition(), 0);
    EXPECT_EQ(car.getYPosition(), 0);
    EXPECT_EQ(car.getSpeed(), 0);
    EXPECT_EQ(car.getDirection(), 0);
}

TEST(Car_SettersTest, filled) {
    Car car;

    car.setPosition(2, 3);
    car.setSpeed(2);
    car.setDirection(2);

    EXPECT_EQ(car.getXPosition(), 2);
    EXPECT_EQ(car.getYPosition(), 3);
    EXPECT_EQ(car.getSpeed(), 2);
    EXPECT_EQ(car.getDirection(), 2);
}

TEST(Car_GettersTest, filled) {
    Car car;

    car.setPosition(2, 3);
    car.setSpeed(2);
    car.setDirection(2);
    
    EXPECT_EQ(car.getXPosition(), 2);
    EXPECT_EQ(car.getYPosition(), 3);
    EXPECT_EQ(car.getSpeed(), 2);
    EXPECT_EQ(car.getDirection(), 2);
}

TEST(Car_positionChangedSignalTest, SignalEmittedTest) {
    Car car;

    QSignalSpy spy(&car, &Car::positionChanged);

    car.positionChanged(1, 2);

    EXPECT_EQ(spy.count(), 1);
}

TEST(Car_moveFunctionTests, moveTest) {
    Car car;

    QSignalSpy spy(&car, &Car::positionChanged);

    car.setPosition(2, 3);
    car.setSpeed(2);
    car.setDirection(2);
    car.move();

    EXPECT_EQ(car.getXPosition(), 3);
    EXPECT_EQ(car.getYPosition(), 2);
    EXPECT_EQ(spy.count(), 1);
}