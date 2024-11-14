#pragma once

#include <QList>
#include <QMainWindow>
#include <QMutex>
#include <QThread>
#include "RaceTrack.h"
#include "Car.h"
#include "CarThread.h"

class RacingGame : public QMainWindow {
  public:
  
    RacingGame(QWidget *parent = 0);
    void RacingGame::unpauseRace();
    

  private slots:
    void startRace();
    void pauseRace();
    void exitGame();

  private:
    RaceTrack *raceTrack;
    QList<Car*> carList;
    QList<QThread*> threadList;
};