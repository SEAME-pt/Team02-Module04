#include "../include/RacingGame.h"
#include "../ui/ui_RacingGame.h"

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

    Car car11 = new Car;
    Car car22 = new Car;

    carList.append(car11);
    carList.append(car22);

    //example of a button connection to a slot (Object instance, in this case is a button, Signal from the object button, Object instance to connect, slot from the object to receive)
    // connect(ui->pushButton, &QPushButton::clicked, this, &RacingGame::openMenuWindow);
    connect(this, &RacingGame::accelerate, this, &RacingGame::openMenuWindow);
}

RacingGame::~RacingGame()
{
    delete ui;
}

void RacingGame::openGameWindow()
{
}

void RacingGame::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_W:
            emit accelerate();
            break;
        case Qt::Key_S:
            emit brake();
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

// void RacingGame::moveAndRotateLabel()
// {
//     // Change the position of the QLabel
//     int newX = 200; // New X position
//     int newY = 200; // New Y position
//     car1->move(newX, newY);

//     // Rotate the QLabel
//     QTransform transform;
//     transform.rotate(45); // Rotate by 45 degrees
//     car1->setPixmap(car1Pixmap.transformed(transform));
// }