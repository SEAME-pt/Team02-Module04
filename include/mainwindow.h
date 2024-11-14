#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTransform>
#include <QGraphicsRotation>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *car1;
    QLabel *car2;
    QLabel *raceTrack;
    QPixmap car1Pixmap;
    QPixmap car2Pixmap;
    QPixmap raceTrackPixmap;

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void accelerate();
    void brake();
    void turnLeft();
    void turnRight();

private slots:
    void moveAndRotateLabel();
};
#endif // MAINWINDOW_H
