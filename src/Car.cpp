
#include "Car.h"

Car::Car(QObject *parent)
{}

Car::~Car()
{}

void Car::setPosition( int pos )
{
    _position = pos;
}

void Car::setSpeed ( int speed )
{
    _speed = speed;
}

void Car::setDirection (int dir )
{
    _direction = dir;
}

int Car::getPosition( void )
{
    return _position;
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
    _position += _speed * _direction;
    emit positionChanged(_position);
}