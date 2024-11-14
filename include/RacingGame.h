#ifndef RACINGGAME_H
#define RACINGGAME_H

#include <QMainWindow>
#include <QLabel>
#include <QTransform>
#include <QGraphicsRotation>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QMutex>
#include <QThread>
#include "RaceTrack.h"
#include "Car.h"

#define CAR_WIDTH 100
#define CAR_HEIGHT 150

#define CAR1_INITIAL_X 200
#define CAR1_INITIAL_Y 300
#define CAR2_INITIAL_X 300
#define CAR2_INITIAL_Y 300

QT_BEGIN_NAMESPACE
namespace Ui {
class RacingGame;
}
QT_END_NAMESPACE

class RacingGame : public QMainWindow
{
    Q_OBJECT

public:
    RacingGame(QWidget *parent = nullptr);
    ~RacingGame();

private:
    Ui::RacingGame *ui;
    QGraphicsPixmapItem *car1;
    QGraphicsPixmapItem *car2;
    QGraphicsPixmapItem *raceTrack;
    QPixmap car1Pixmap;
    QPixmap car2Pixmap;
    QPixmap raceTrackPixmap;

    QList<Car*> carList;
    QList<QThread*> threadList;
    RaceTrack *raceTrackPtr;

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void accelerate();
    void brake();
    void turnLeft();
    void turnRight();

private slots:
    void openGameWindow();
    void updateGameWindow(int xPos, int yPos, int dir);
    void startRace();
    void pauseRace();
    void exitGame();
    void unpauseRace();
};
#endif // RACINGGAME_H
