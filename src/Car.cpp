
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
    _xPos += _speed * cos(_direction * 3.14);
    _yPos += _speed * sin(_direction * 3.14);
}