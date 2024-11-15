#include <QtTest/QtTest>

#include "../../include/RacingGame.h"
#include "../../include/Car.h"
#include "../../include/CarThread.h"
#include <QSignalSpy>


class MockCar : public Car {
public:
    MockCar(const std::string &plate): Car(plate){}
    void move() { setPosition(getXPosition() + 10, getYPosition() + 10);}
};


class RacingGameTest : public RacingGame {
    Q_OBJECT

signals:
    void testSignal();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testStartRace();
    void testConstructor();

private:
    RacingGame *racingGame;

};

void RacingGameTest::initTestCase() {
    racingGame = new RacingGame();

}

void RacingGameTest::cleanupTestCase() {
    
    threadList[0]->terminate();
    threadList[1]->terminate();
    delete racingGame;

}

void RacingGameTest::testStartRace() {
    QCOMPARE(getThreadList().size(), 2);
    for (QThread *thread : getThreadList()) {
        QVERIFY(thread->isRunning());
    }
}

void RacingGameTest::testConstructor() {
    // Verify that the UI elements are initialized
    QVERIFY(racingGame->findChild<QLabel*>("car1") != nullptr);
    QVERIFY(racingGame->findChild<QLabel*>("car2") != nullptr);
    QVERIFY(racingGame->findChild<QLabel*>("RaceTrack") != nullptr);
}

QTEST_MAIN(RacingGameTest)
#include "test_racingGame_class.moc"