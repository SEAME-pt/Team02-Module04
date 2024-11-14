#pragma once

#include <iostream>

class Car
{
private:
    double _xPos;
    double _yPos;
    double _speed;
    double _direction;
    std::string _plate;

public:
    Car(const std::string &plate);
    ~Car();

    void move();
    
    void setPosition( double x , double y );
    void setSpeed ( double speed );
    void setDirection (double dir );

    double getXPosition( void );
    double getYPosition( void );
    double getSpeed( void );
    double getDirection( void );
    const std::string& getPlate( void );
};
