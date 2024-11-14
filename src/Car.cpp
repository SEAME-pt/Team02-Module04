
#include "../include/Car.h"
#include <math.h>

Car::Car() : _xPos(0), _yPos(0), _speed(0), _direction(1)
{}

Car::~Car()
{}

void Car::setPosition( double x, double y )
{
    _xPos = x;
    _yPos = y;
}

void Car::setSpeed ( double speed )
{
    if (speed < 4 && speed > -4)
        _speed = speed;
}

void Car::setDirection (double dir )
{
    _direction = dir;
}

double Car::getXPosition( void )
{
    return _xPos;
}

double Car::getYPosition( void )
{
    return _yPos;
}

double Car::getSpeed( void )
{
    return _speed;
}

double Car::getDirection( void )
{
    return _direction;
}

void Car::move()
{
    double radians = _direction * M_PI / 180.0;

    double deltaX = cos(radians);
    double deltaY = sin(radians);
    _xPos += deltaX * _speed;
    _yPos += deltaY * _speed;
}