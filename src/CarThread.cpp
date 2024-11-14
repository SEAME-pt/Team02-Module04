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
        emit updatePosition(_car->getXPosition(), _car->getYPosition(), _car->getDirection(), _car->getPlate());
        _mutex->unlock();
        msleep(10);
    }
}

void CarThread::onAccelerate(const std::string& plate)
{
    _mutex->lock();
    if (_car->getPlate() == plate)
    {
        int speed = _car->getSpeed() - 1;
        _car->setSpeed(speed);
    }
    _mutex->unlock(); 
    msleep(10);
}

void CarThread::onBrake(const std::string& plate)
{
    _mutex->lock();
    if (_car->getPlate() == plate)
    {
        int speed = _car->getSpeed() + 1;
        _car->setSpeed(speed);
    }
    _mutex->unlock(); 
    msleep(10);
}

void::CarThread::onTurnLeft(const std::string& plate)
{
    _mutex->lock();
    if (_car->getPlate() == plate)
    {
        int dir = _car->getDirection();
        _car->setDirection(dir - 4);
    }
    _mutex->unlock(); 
    msleep(10);
}

void::CarThread::onTurnRight(const std::string& plate)
{
    _mutex->lock();
    if (_car->getPlate() == plate)
    {
        int dir = _car->getDirection();
        _car->setDirection(dir + 4);
    }
    _mutex->unlock(); 
    msleep(10);
}
