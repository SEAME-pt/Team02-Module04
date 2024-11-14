#include <QtTest/QtTest>

#include "../../include/RacingGame.h"
#include "../../include/Car.h"
#include "../../include/CarThread.h"
#include <QSignalSpy>


class MockCar : public Car {
public:
    MockCar(QObject *parent = nullptr) : Car(parent) {}
    void move() { setPosition(getXPosition() + 10, getYPosition() + 10); emit positionChanged(getSpeed(), getDirection()); }
};

class MockCarThread : public CarThread {
public:
    MockCarThread(Car *car) : CarThread(car) {}
    void run() override {
            getMutex()->lock();
            _car->move();
            _mutex->unlock();
            msleep(10);
        emit finished();
    }
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
    MockCar *car1 = new MockCar();
    MockCar *car2 = new MockCar();
    carList.append(car1);
    carList.append(car2);
    racingGame = new RacingGame();

}

void RacingGameTest::cleanupTestCase() {
    
    threadList[0]->terminate();
    threadList[1]->terminate();
    delete racingGame;

}

void RacingGameTest::testStartRace() {
    startRace();
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

    // Verify that the pixmaps are set correctly
    QLabel *car1 = racingGame->findChild<QLabel*>("car1");
    QLabel *car2 = racingGame->findChild<QLabel*>("car2");
    QLabel *raceTrack = racingGame->findChild<QLabel*>("RaceTrack");

    QVERIFY(!car1->pixmap().isNull());
    QVERIFY(!car2->pixmap().isNull());
    QVERIFY(!raceTrack->pixmap().isNull());
}

QTEST_MAIN(RacingGameTest)
#include "test_racingGame_class.moc"