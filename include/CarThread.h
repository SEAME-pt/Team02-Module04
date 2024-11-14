
#pragma once

#include <QThread>
#include <QMutex>
#include "RaceTrack.h"
#include "Car.h"

class CarThread : public QThread {

  Q_OBJECT
  public:

    CarThread(Car *car);
    void run();
    void setRaceTrack( RaceTrack raceT);
    QMutex *getMutex();

  private:
    Car *_car;
    RaceTrack *_raceTrack;
    QMutex *_mutex;

  public slots:
    void updatePosition( int speed, int dir );
    // void onAccelerate();
    // void onBrake();
    // void onTurnLeft();
    // void onTurnRight();
};