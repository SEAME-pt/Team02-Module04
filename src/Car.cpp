
#include "../include/Car.h"
#include <math.h>

Car::Car(const std::string& plate) : _xPos(0), _yPos(0), _speed(0), _direction(1), _plate(plate)
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
    if (speed < 10 && speed > -10)
        _speed = speed;
}

void Car::setDirection (double dir )
{
    _direction = dir;
}

double Car::getXPosition( void )
{
    return this->_xPos;
}

double Car::getYPosition( void )
{
    return this->_yPos;
}

double Car::getSpeed( void )
{
    return this->_speed;
}

double Car::getDirection( void )
{
    return this->_direction;
}

const std::string& Car::getPlate( void )
{
    return this->_plate;
}

void Car::move(int width, int height)
{
    double radians = _direction * M_PI / 180.0;
    double deltaX = cos(radians);
    double deltaY = sin(radians);

    double tempX = _xPos; 
    double tempY = _yPos;

    _xPos += deltaX * _speed;
    _yPos += deltaY * _speed;

    if (_speed < 0)
        _speed += 0.01;
    else if (_speed > 0)
        _speed -= 0.01;
    
    if (_xPos < 0 || _xPos > width)
        _xPos = tempX;
    if (_yPos < 0 || _yPos > height)
        _yPos = tempY;
}