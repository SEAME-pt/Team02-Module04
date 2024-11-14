#include <gtest/gtest.h>
#include "../../include/Car.h"

TEST(GettersTest, empty) {
    Car car;

    car.setPosition(2, 3);
    
    EXPECT_EQ(car.getXPosition(), 2);
    EXPECT_EQ(car.getYPosition(), 2);
}
