#include "../include/CarThread.h"
#include <QDebug>

CarThread::CarThread(Car *car): _car(car), _mutex(new QMutex())
{
}

void CarThread::setRaceTrack(RaceTrack *raceTrack)
{
    _raceTrack = raceTrack;
}

QMutex *CarThread::getMutex()
{
    return _mutex;
}

void CarThread::run()
{
    int width = this->_raceTrack->getWidth();
    int height = this->_raceTrack->getHeight();
    while (true)
    {
        _mutex->lock();
        // if (_car->getXPosition() + 100 < width  && _car->getYPosition() < height)
        _car->move();
        emit updatePosition(_car->getXPosition(), _car->getYPosition(), _car->getDirection());
        _mutex->unlock();
        msleep(10);
    }
}

void CarThread::onAccelerate()
{
    _mutex->lock();
    int speed = _car->getSpeed() - 1;
    _car->setSpeed(speed);
    _mutex->unlock(); 
    msleep(10);
}

void CarThread::onBrake()
{
    _mutex->lock();
    int speed = _car->getSpeed() + 1;
    _car->setSpeed(speed);
    _mutex->unlock(); 
    msleep(10);
}

void::CarThread::onTurnLeft()
{
    _mutex->lock();
    int dir = _car->getDirection();
    _car->setDirection(dir - 2);
    _mutex->unlock(); 
    msleep(10);
}

void CarThread::onTurnRight()
{
    _mutex->lock();
    int dir = _car->getDirection();
    _car->setDirection(dir + 2);
    _mutex->unlock(); 
    msleep(10);
}

Car *CarThread::getCar( void )
{
    return _car;
}

RaceTrack *CarThread::getRaceTrack( void )
{
    return _raceTrack;
}