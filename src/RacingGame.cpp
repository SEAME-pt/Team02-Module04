#include "../include/RacingGame.h"

RacingGame::RacingGame(QWidget *parent){}

void RacingGame::startRace() 
{
    // Create a new thread for each car and start the threads
    foreach (Car *car, carList)
    {
        QThread *thread = new QThread();
        CarThread *carThread = new CarThread(car);
        carThread->moveToThread(thread);
    
        connect(car, &Car::positionChanged, carThread, &CarThread::updatePosition);
        connect(thread, &QThread::started, carThread, &CarThread::run);
        connect(carThread, &CarThread::finished, thread, &QThread::quit);
        connect(carThread, &CarThread::finished, carThread, &CarThread::deleteLater);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    
        threadList.append(thread);
        carThread->start();
    }
}

void RacingGame::pauseRace()
{
    foreach (QThread *thread , threadList)
    {
        thread->findChild<CarThread *>()->getMutex()->lock();
    }
}

void RacingGame::unpauseRace()
{
    foreach (QThread *thread , threadList)
    {
        thread->findChild<CarThread *>()->getMutex()->unlock();
    }
}
    
void RacingGame::exitGame()
{
    foreach (QThread *thread , threadList)
    {
        delete (thread->findChild<CarThread *>()->getMutex());
    }
}

