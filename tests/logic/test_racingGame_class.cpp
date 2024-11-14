#include <QtTest/QtTest>

#include "../../include/RacingGame.h"
#include "../../include/Car.h"
#include "../../include/CarThread.h"


class MockCar : public Car {
public:
    MockCar(QObject *parent = nullptr) : Car(parent) {}
    void move() { setPosition(getXPosition() + 10, getYPosition() + 10); emit positionChanged(getSpeed(), getDirection()); }
};

class MockCarThread : public CarThread {
public:
    MockCarThread(Car *car) : CarThread(car) {}
    void run() override {
        while (_car->getXPosition() < _raceTrack->getFinishLine()) {
            getMutex()->lock();
            _car->move();
            _mutex->unlock();
            msleep(10);
        }
        emit finished();
    }
    void updatePosition(int speed, int dir) override {}
};

class RacingGameTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testStartRace();

private:
    RacingGame *racingGame;
    QList<Car *> carList;
    MockCar *car1;
    MockCar *car2;
};

void RacingGameTest::initTestCase() {
    car1 = new MockCar();
    car2 = new MockCar();
    carList.append(car1);
    carList.append(car2);
    racingGame = new RacingGame();
    racingGame->addToCarList(carList);
}

void RacingGameTest::cleanupTestCase() {
    delete racingGame;
    delete car1;
    delete car2;
}

void RacingGameTest::testStartRace() {
    QCOMPARE(racingGame->getThreadList().size(), 2);
    for (QThread *thread : racingGame->getThreadList()) {
        QVERIFY(thread->isRunning());
    }
}

QTEST_MAIN(RacingGameTest)
#include "test_racingGame_class.moc"