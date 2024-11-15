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
#include <QSet>
#include <QKeyEvent>
#include <QThread>
#include <QDialog>
#include "RaceTrack.h"
#include "Car.h"
#include "../ui/ui_menuwindow.h"

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
    void addToCarList(Car*);
    QList <QThread *>getThreadList();

private:
    Ui::RacingGame *ui;
    QGraphicsPixmapItem *car1;
    QGraphicsPixmapItem *car2;
    QGraphicsPixmapItem *raceTrack;
    QPixmap car1Pixmap;
    QPixmap car2Pixmap;
    QPixmap raceTrackPixmap;
    QDialog *pauseMenu;
    Ui::menuwindow *uiPause;

protected:
    QList<Car*> carList;
    QList<QThread *> threadList;
    RaceTrack *raceTrackPtr;
    QSet<int> pressedKeys; // Add this line

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void accelerate(const std::string& plate);
    void deaccelerate(const std::string& plate);
    void turnLeft(const std::string& plate);
    void turnRight(const std::string& plate);
    void stopAll();
    void startAll();

protected slots:
    void openGameWindow();
    void updateGameWindow(double xPos, double yPos, double dir, const std::string &plate);
    void startRace();
    void exitGame();

public slots:
    void pauseRace();
    void unpauseRace();
};
#endif // RACINGGAME_H
