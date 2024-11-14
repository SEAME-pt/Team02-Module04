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

    Car* carA = new Car("a");
    Car* carB = new Car("b");
    carList.append(carA);
    carList.append(carB);

    startRace();
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
    if (plate == "a")
    {
        car1->setPos(xPos, yPos);
        car1->setRotation(dir);
    }
    else
    {
        car2->setPos(xPos, yPos);
        car2->setRotation(dir);
    }
}

