#include <gtest/gtest.h>
#include <QSignalSpy>
#include "../../include/RaceTrack.h"

TEST(RaceTrack_GettersTest, empty) {
    RaceTrack raceTrack;

    EXPECT_EQ(raceTrack.getWidth(), 0);
    EXPECT_EQ(raceTrack.getHeight(), 0);

    EXPECT_EQ(raceTrack.getFinishLine(), 0);
}

TEST(RaceTrack_SettersTest, filled) {
    RaceTrack raceTrack;

    raceTrack.setHeight(5);
    raceTrack.setWidth(5);
    raceTrack.setFinishLine(3);

    EXPECT_EQ(raceTrack.getWidth(), 5);
    EXPECT_EQ(raceTrack.getHeight(), 5);
    EXPECT_EQ(raceTrack.getFinishLine(), 3);
}

TEST(RaceTrack_GettersTest, filled) {
    RaceTrack raceTrack;

    raceTrack.setWidth(10);
    raceTrack.setHeight(10);

    raceTrack.setFinishLine(2);

    EXPECT_EQ(raceTrack.getHeight(), 10);
    EXPECT_EQ(raceTrack.getWidth(), 10);
    EXPECT_EQ(raceTrack.getFinishLine(), 2);
}

TEST(RaceTrack_BoundaryTest, boundaryValues) {
    RaceTrack raceTrack;

    raceTrack.setWidth(INT_MAX);
    raceTrack.setHeight(INT_MAX);
    raceTrack.setFinishLine(INT_MAX);

    EXPECT_EQ(raceTrack.getWidth(), INT_MAX);
    EXPECT_EQ(raceTrack.getHeight(), INT_MAX);
    EXPECT_EQ(raceTrack.getFinishLine(), INT_MAX);

    raceTrack.setHeight(INT_MIN);
    raceTrack.setWidth(INT_MIN);
    raceTrack.setFinishLine(INT_MIN);

    EXPECT_EQ(raceTrack.getHeight(), INT_MIN);
    EXPECT_EQ(raceTrack.getWidth(), INT_MIN);
    EXPECT_EQ(raceTrack.getFinishLine(), INT_MIN);
}

TEST(RaceTrack_NegativeTest, negativeValues) {
    RaceTrack raceTrack;

    raceTrack.setHeight(-5);
    raceTrack.setWidth(-5);
    raceTrack.setFinishLine(-3);

    EXPECT_EQ(raceTrack.getHeight(), -5);
    EXPECT_EQ(raceTrack.getWidth(), -5);
    EXPECT_EQ(raceTrack.getFinishLine(), -3);
}

TEST(RaceTrack_ZeroTest, zeroValues) {
    RaceTrack raceTrack;

    raceTrack.setHeight(0);
    raceTrack.setWidth(0);
    raceTrack.setFinishLine(0);

    EXPECT_EQ(raceTrack.getHeight(), 0);
    EXPECT_EQ(raceTrack.getWidth(), 0);
    EXPECT_EQ(raceTrack.getFinishLine(), 0);
}
