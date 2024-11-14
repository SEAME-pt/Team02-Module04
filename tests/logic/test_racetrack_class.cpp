#include <gtest/gtest.h>
#include <QSignalSpy>
#include "../../include/RaceTrack.h"

TEST(RaceTrack_GettersTest, empty) {
    RaceTrack raceTrack;

    EXPECT_EQ(raceTrack.getSize(), 0);
    EXPECT_EQ(raceTrack.getFinishLine(), 0);
}

TEST(RaceTrack_SettersTest, filled) {
    RaceTrack raceTrack;

    raceTrack.setSize(5);
    raceTrack.setFinishLine(3);

    EXPECT_EQ(raceTrack.getSize(), 5);
    EXPECT_EQ(raceTrack.getFinishLine(), 3);
}

TEST(RaceTrack_GettersTest, filled) {
    RaceTrack raceTrack;

    raceTrack.setSize(10);
    raceTrack.setFinishLine(2);

    EXPECT_EQ(raceTrack.getSize(), 10);
    EXPECT_EQ(raceTrack.getFinishLine(), 2);
}

TEST(RaceTrack_BoundaryTest, boundaryValues) {
    RaceTrack raceTrack;

    raceTrack.setSize(INT_MAX);
    raceTrack.setFinishLine(INT_MAX);

    EXPECT_EQ(raceTrack.getSize(), INT_MAX);
    EXPECT_EQ(raceTrack.getFinishLine(), INT_MAX);

    raceTrack.setSize(INT_MIN);
    raceTrack.setFinishLine(INT_MIN);

    EXPECT_EQ(raceTrack.getSize(), INT_MIN);
    EXPECT_EQ(raceTrack.getFinishLine(), INT_MIN);
}

TEST(RaceTrack_NegativeTest, negativeValues) {
    RaceTrack raceTrack;

    raceTrack.setSize(-5);
    raceTrack.setFinishLine(-3);

    EXPECT_EQ(raceTrack.getSize(), -5);
    EXPECT_EQ(raceTrack.getFinishLine(), -3);
}

TEST(RaceTrack_ZeroTest, zeroValues) {
    RaceTrack raceTrack;

    raceTrack.setSize(0);
    raceTrack.setFinishLine(0);

    EXPECT_EQ(raceTrack.getSize(), 0);
    EXPECT_EQ(raceTrack.getFinishLine(), 0);
}
