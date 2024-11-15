#include <gtest/gtest.h>
#include "../../include/Car.h"

TEST(GettersTest, empty) {
    Car car("a");
    
    EXPECT_EQ(car.getXPosition(), 0);
    EXPECT_EQ(car.getYPosition(), 0);
    EXPECT_EQ(car.getSpeed(), 0);
    EXPECT_EQ(car.getDirection(), 0);
}

TEST(SettersTest, filled) {
    Car car("a");

    car.setPosition(2, 3);
    car.setSpeed(2);
    car.setDirection(2);

    EXPECT_EQ(car.getXPosition(), 2);
    EXPECT_EQ(car.getYPosition(), 3);
    EXPECT_EQ(car.getSpeed(), 2);
    EXPECT_EQ(car.getDirection(), 2);
}

TEST(GettersTest, filled) {
    Car car("a");

    car.setPosition(2, 3);
    car.setSpeed(2);
    car.setDirection(2);
    
    EXPECT_EQ(car.getXPosition(), 2);
    EXPECT_EQ(car.getYPosition(), 3);
    EXPECT_EQ(car.getSpeed(), 2);
    EXPECT_EQ(car.getDirection(), 2);
}