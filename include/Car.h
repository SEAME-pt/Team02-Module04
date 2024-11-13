#pragma once

#include <QObject>

class Car:  public QObject
{
    Q_OBJECT

    private:
        int _position;
        int _speed;
        int _direction;
    
    public:
        Car(QObject *parent = nullptr);
        ~Car();

        void move();
        
        void setPosition( int pos );
        void setSpeed ( int speed );
        void setDirection (int dir );

        int getPosition( void );
        int getSpeed( void );
        int getDirection( void );

    signals:
        void positionChanged(int newPosition);
};
