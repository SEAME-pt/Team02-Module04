#include "../include/RacingGame.h"
#include "../ui/ui_RacingGame.h"
#include "../include/CarThread.h"
#include <iostream>

RacingGame::RacingGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RacingGame)
{
    ui->setupUi(this);

    car1 = ui->car1;
    car1Pixmap = QPixmap(":/ui/assets/SportCar.png");
    car1->setPixmap(car1Pixmap);

    car2 = ui->car2;
    car2Pixmap = QPixmap(":/ui/assets/SportCar.png");
    car2->setPixmap(car2Pixmap);

    raceTrack = ui->RaceTrack;
    raceTrackPixmap = QPixmap(":/ui/assets/Race.jpg");
    raceTrack->setPixmap(raceTrackPixmap);

    Car* car11 = new Car;
    // Car* car22 = new Car;

    carList.append(car11);
    // carList.append(car22);

    //connect(ui->pushButton, &QPushButton::clicked, this, &RacingGame::accelerate);
    this->startRace();
    //example of a button connection to a slot (Object instance, in this case is a button, Signal from the object button, Object instance to connect, slot from the object to receive)
}

RacingGame::~RacingGame()
{
    
    delete ui;

}

void RacingGame::openGameWindow()
{
    emit accelerate();
}

void RacingGame::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_W:
            emit accelerate();
            break;
        case Qt::Key_S:
            emit deaccelerate();
            break;
        case Qt::Key_A:
            emit turnLeft();
            break;
        case Qt::Key_D:
            emit turnRight();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

void RacingGame::startRace() 
{
    QSize raceTrackSize = ui->RaceTrack->size();
    int raceTrackWidth = raceTrackSize.width();
    int raceTrackHeight = raceTrackSize.height();
    
    RaceTrack *raceTrack = new RaceTrack;
    raceTrack->setWidth(raceTrackWidth);
    raceTrack->setHeight(raceTrackHeight);

    foreach (Car *car, carList)
    {
        CarThread *carThread = new CarThread(car);
    
        connect(this, &RacingGame::accelerate, carThread, &CarThread::onAccelerate);
        connect(this, &RacingGame::deaccelerate, carThread, &CarThread::onBrake);
        connect(this, &RacingGame::turnRight, carThread, &CarThread::onTurnRight);
        connect(this, &RacingGame::turnLeft, carThread, &CarThread::onTurnLeft);

        connect(carThread, &CarThread::updatePosition, this, &RacingGame::updateGameWindow);
        connect(carThread, &CarThread::finished, carThread, &CarThread::deleteLater);
    
        threadList.append(carThread);
        carThread->setRaceTrack(raceTrack);
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

void RacingGame::updateGameWindow(int xPos, int yPos, int dir)
{
    QTransform transform;
    car1->move(xPos, yPos);

    transform.rotate(dir);
    car1->setPixmap(car1Pixmap.transformed(transform));
}

void RacingGame::updateGameWindow(int xPos, int yPos, int dir)
{
    QTransform transform;
    car1->move(xPos, yPos);

    transform.rotate(dir);
    car1->setPixmap(car1Pixmap.transformed(transform));
}

void RacingGame::addToCarList(Car* car)
{
    carList.append(car);
}

QList <QThread *>RacingGame::getThreadList()
{
    return threadList;
}