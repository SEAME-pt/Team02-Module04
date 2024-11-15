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
  void updatePosition( double xPos, double yPos, double dir, const std::string& plate );

public slots:
  void onAccelerate(const std::string& plate);
  void onBrake(const std::string& plate);
  void onTurnLeft(const std::string& plate);
  void onTurnRight(const std::string& plate);
  void pauseThreads();
  void unpauseThreads();
};