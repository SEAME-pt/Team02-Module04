#include "../include/CarThread.h"
#include <QDebug>

CarThread::CarThread(Car *car): _car(car), _mutex(new QMutex()) {}

void CarThread::setRaceTrack( RaceTrack raceT)
{
    _raceTrack = new RaceTrack();
}

QMutex *CarThread::getMutex()
{
    return _mutex;
}

void CarThread::run()
{
    while (true)
    {
        _mutex->lock();
        _car->move();
        emit updatePosition(_car->getXPosition(), _car->getYPosition(), _car->getDirection());
        _mutex->unlock();
        msleep(10);
    }
}

void CarThread::onAccelerate()
{
    _mutex->lock();
    int speed = _car->getSpeed() + 1;
    _car->setSpeed(speed);
    _mutex->unlock(); 
    msleep(10);
}

void CarThread::onBrake()
{
    _mutex->lock();
    int speed = _car->getSpeed() - 1;
    _car->setSpeed(speed);
    _mutex->unlock(); 
    msleep(10);
}
