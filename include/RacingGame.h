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
#include "CarThread.h"

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
    void addToCarList(Car*);
    QList <QThread *>getThreadList();

private:
    Ui::RacingGame *ui;
    QLabel *car1;
    QLabel *car2;
    QLabel *raceTrack;
    QPixmap car1Pixmap;
    QPixmap car2Pixmap;
    QPixmap raceTrackPixmap;

protected:
    QList<Car*> carList;
    QList<QThread*> threadList;
    RaceTrack *raceTrackPtr;

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void accelerate();
    void deaccelerate();
    void turnLeft();
    void turnRight();

public slots:


protected slots:
    void openGameWindow();
    void updateGameWindow(int xPos, int yPos, int dir);
    void startRace();
    void pauseRace();
    void exitGame();
    void unpauseRace();
};
#endif // RACINGGAME_H
