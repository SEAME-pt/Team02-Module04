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
        _car->move(width, height);
        emit updatePosition(_car->getXPosition(), _car->getYPosition(), _car->getDirection(), _car->getPlate());
        _mutex->unlock();
        msleep(1);
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
}

void CarThread::onTurnLeft(const std::string& plate)
{
    _mutex->lock();
    if (_car->getPlate() == plate)
    {
        int dir = _car->getDirection();
        _car->setDirection(dir - 4);
    }
    _mutex->unlock(); 
}

void CarThread::onTurnRight(const std::string& plate)
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

Car *CarThread::getCar( void )
{
    return _car;
}

RaceTrack *CarThread::getRaceTrack( void )
{
    return _raceTrack;
}

void CarThread::pauseThreads()
{
    _mutex->lock();
}

void CarThread::unpauseThreads()
{
    _mutex->unlock();
}