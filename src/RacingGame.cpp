#include "../include/RacingGame.h"
#include "../ui/ui_RacingGame.h"
#include "../include/CarThread.h"
#include "../include/RacingGame.h"

RacingGame::RacingGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RacingGame)
{
    ui->setupUi(this);

    QPixmap raceTrackPixmap(":/ui/assets/Race.jpg");
    QPixmap scaledTrack = raceTrackPixmap.scaled(ui->graphicsView->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(scaledTrack.rect());

    QGraphicsPixmapItem *raceTrackItem = new QGraphicsPixmapItem(scaledTrack);
    raceTrackItem->setZValue(-1);
    scene->addItem(raceTrackItem);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap car1Pixmap(":/ui/assets/SportCar.png");
    QPixmap scaledCar1 = car1Pixmap.scaled(CAR_WIDTH, CAR_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    car1 = new QGraphicsPixmapItem(scaledCar1);
    car1->setPos(CAR1_INITIAL_X, CAR1_INITIAL_Y);
    scene->addItem(car1);

    QPixmap car2Pixmap(":/ui/assets/SportCar.png");
    QPixmap scaledCar2 = car2Pixmap.scaled(CAR_WIDTH, CAR_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    car2 = new QGraphicsPixmapItem(scaledCar2);
    car2->setPos(CAR2_INITIAL_X, CAR2_INITIAL_Y);
    scene->addItem(car2);

    Car* car11 = new Car;
    carList.append(car11);

    startRace();
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
    foreach (Car *car, carList)
    {
        // QThread *thread = new QThread();
        CarThread *carThread = new CarThread(car);
        // carThread->moveToThread(thread);
    
        connect(carThread, &CarThread::updatePosition, this, &RacingGame::updateGameWindow);
        // connect(thread, &QThread::started, carThread, &CarThread::run);
        // connect(carThread, &CarThread::finished, thread, &QThread::quit);
        connect(carThread, &CarThread::finished, carThread, &CarThread::deleteLater);
        // connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    
        connect(this, &RacingGame::turnRight, carThread, &CarThread::onTurnRight);
        connect(this, &RacingGame::turnLeft, carThread, &CarThread::onTurnLeft);

        connect(carThread, &CarThread::updatePosition, this, &RacingGame::updateGameWindow);
        threadList.append(carThread);
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

void RacingGame::updateGameWindow(int xPos, int yPos, int angle)
{
    car1->setRotation(angle);
    car1->setPos(xPos, yPos);
}
