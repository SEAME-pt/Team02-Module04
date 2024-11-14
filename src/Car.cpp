
#include "../include/Car.h"
#include <math.h>

Car::Car() : _xPos(0), _yPos(0), _speed(0), _direction(1)
{}

Car::~Car()
{}

void Car::setPosition( int x, int y )
{
    _xPos = x;
    _yPos = y;
}

void Car::setSpeed ( int speed )
{
    if (speed < 8 && speed > -8)
        _speed = speed;
}

void Car::setDirection (int dir )
{
    _direction = dir;
}

int Car::getXPosition( void )
{
    return _xPos;
}

int Car::getYPosition( void )
{
    return _yPos;
}

int Car::getSpeed( void )
{
    return _speed;
}

int Car::getDirection( void )
{
    return _direction;
}

void Car::move()
{
    double radians = _direction * M_PI / 180.0;

    double stepSize = 1.0;

    // Apply the rotation matrix to calculate the new position
    double deltaX = _speed * stepSize * cos(radians);
    double deltaY = _speed * stepSize * sin(radians);
    _xPos += deltaX;
    _yPos += deltaY;
}