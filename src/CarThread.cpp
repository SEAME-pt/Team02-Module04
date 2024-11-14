#include "../include/CarThread.h"

CarThread::CarThread(Car *car): _car(car), QThread(car){}

void CarThread::setRaceTrack( RaceTrack *raceT)
{
    _raceTrack = raceT;
}

QMutex *CarThread::getMutex()
{
    return _mutex;
}

Car *CarThread::getCar()
{
    return _car;
}

void CarThread::run()
{
    // while (_car->getPosition() < _raceTrack->getFinishLine())
    // {
        _mutex->lock(); // Acquire a lock before moving the car
        _car->move();
        _mutex->unlock(); // Release the lock after moving the car
        msleep(10); // Wait 10 milliseconds before moving again
    // }
}

void CarThread::updatePosition( int speed, int dir )
{
    
}