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

private:
    Ui::RacingGame *ui;
    QLabel *car1;
    QLabel *car2;
    QLabel *raceTrack;
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
    void deaccelerate();
    void turnLeft();
    void turnRight();

private slots:
    void openGameWindow();
    void updateGameWindow(double xPos, double yPos, double dir);
    void startRace();
    void pauseRace();
    void exitGame();
    void unpauseRace();
};
#endif // RACINGGAME_H
