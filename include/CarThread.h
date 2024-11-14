
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
  void run();
  void setRaceTrack( RaceTrack *raceTrack);
  QMutex *getMutex();

private:
  Car *_car;
  RaceTrack *_raceTrack;
  QMutex *_mutex;

signals:
  void updatePosition( double xPos, double yPos, double dir );

public slots:
  void onAccelerate();
  void onBrake();
  void onTurnLeft();
  void onTurnRight();
};