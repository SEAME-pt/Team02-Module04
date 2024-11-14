#include "../include/CarThread.h"

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
    int speed = _car->getSpeed();
    _car->setSpeed(speed + 0.5);
    _mutex->unlock(); 
    msleep(10);
}

void CarThread::onBrake()
{
    _mutex->lock();
    int speed = _car->getSpeed();
    _car->setSpeed(speed - 0.5);
    _mutex->unlock(); 
    msleep(10);
}

void::CarThread::onTurnLeft()
{
    _mutex->lock();
    int dir = _car->getDirection();
    _car->setDirection(dir - 1);
    _mutex->unlock(); 
    msleep(10);
}

void::CarThread::onTurnRight()
{
    _mutex->lock();
    int dir = _car->getDirection();
    _car->setDirection(dir + 1);
    _mutex->unlock(); 
    msleep(10);
}
