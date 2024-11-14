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
