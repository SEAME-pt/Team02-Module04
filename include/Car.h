#pragma once

#include <QObject>

class Car:  public QObject
{
    Q_OBJECT

    private:
        int _xPos;
        int _yPos;
        int _speed;
        int _direction;
    
    public:
        Car(QObject *parent = nullptr);
        ~Car();

        void move();
        
        void setPosition( int x , int y );
        void setSpeed ( int speed );
        void setDirection (int dir );

        int getXPosition( void );
        int getYPosition( void );
        int getSpeed( void );
        int getDirection( void );

    // signals:
    //     void positionChanged(int speed, int dir);
};
