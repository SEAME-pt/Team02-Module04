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

    Car* carA = new Car("a");
    Car* carB = new Car("b");

    carList.append(carA);
    carList.append(carB);

    this->startRace();
    //example of a button connection to a slot (Object instance, in this case is a button, Signal from the object button, Object instance to connect, slot from the object to receive)
    //connect(ui->pushButton, &QPushButton::clicked, this, &RacingGame::accelerate);
}

RacingGame::~RacingGame()
{
    delete ui;
}

void RacingGame::openGameWindow()
{
}

// void RacingGame::keyPressEvent(QKeyEvent *event)
// {
//     switch (event->key()) {
//         case Qt::Key_W:
//             emit accelerate("a");
//             break;
//         case Qt::Key_S:
//             emit deaccelerate("a");
//             break;
//         case Qt::Key_A:
//             emit turnLeft("a");
//             break;
//         case Qt::Key_D:
//             emit turnRight("a");
//             break;
//         case Qt::Key_I:
//             emit accelerate("b");
//             break;
//         case Qt::Key_K:
//             emit deaccelerate("b");
//             break;
//         case Qt::Key_J:
//             emit turnLeft("b");
//             break;
//         case Qt::Key_L:
//             emit turnRight("b");
//             break;
//         default:
//             QMainWindow::keyPressEvent(event);
//     }
// }

void RacingGame::keyPressEvent(QKeyEvent *event)
{
    pressedKeys.insert(event->key()); // Add the key to the set of pressed keys

    if (pressedKeys.contains(Qt::Key_W)) {
        emit accelerate("a");
    }
    if (pressedKeys.contains(Qt::Key_S)) {
        emit deaccelerate("a");
    }
    if (pressedKeys.contains(Qt::Key_A)) {
        emit turnLeft("a");
    }
    if (pressedKeys.contains(Qt::Key_D)) {
        emit turnRight("a");
    }
    if (pressedKeys.contains(Qt::Key_I)) {
        emit accelerate("b");
    }
    if (pressedKeys.contains(Qt::Key_K)) {
        emit deaccelerate("b");
    }
    if (pressedKeys.contains(Qt::Key_J)) {
        emit turnLeft("b");
    }
    if (pressedKeys.contains(Qt::Key_L)) {
        emit turnRight("b");
    }
}

void RacingGame::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys.remove(event->key());
}

void RacingGame::startRace() 
{
    QSize raceTrackSize = ui->RaceTrack->size();
    int raceTrackWidth = raceTrackSize.width();
    int raceTrackHeight = raceTrackSize.height();
    std::cout << raceTrackWidth << std::endl;
    std::cout << raceTrackHeight << std::endl;
    
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

void RacingGame::updateGameWindow(double xPos, double yPos, double dir, const std::string &plate)
{
    QTransform transform;
    transform.rotate(dir);
    if (plate == "a")
    {
        car1->move(xPos, yPos);
        car1->setPixmap(car1Pixmap.transformed(transform));
    }
    else
    {
        car2->move(xPos, yPos);
        car2->setPixmap(car2Pixmap.transformed(transform));
    }
}

void RacingGame::addToCarList(Car* car)
{
    carList.append(car);
}


QList <QThread *> RacingGame::getThreadList()
{
    return threadList;
}