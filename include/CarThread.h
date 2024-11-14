
#pragma once

#include <QThread>
#include <QMutex>
#include "RaceTrack.h"
#include "Car.h"

class CarThread : public QThread 
{
  Q_OBJECT
public:

  CarThread(Car *car);
  void run( void );
  void setRaceTrack( RaceTrack *raceTrack);
  QMutex *getMutex( void );
  Car *getCar( void );
  RaceTrack *getRaceTrack( void );

private:
  Car *_car;
  RaceTrack *_raceTrack;
  QMutex *_mutex;

signals:
  void updatePosition( int xPos, int yPos, int dir );

public slots:
  void onAccelerate();
  void onBrake();
  void onTurnLeft();
  void onTurnRight();
};