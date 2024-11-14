#include "../include/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::moveAndRotateLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveAndRotateLabel()
{
    // Change the position of the QLabel
    int newX = 200; // New X position
    int newY = 200; // New Y position
    car1->move(newX, newY);

    // Rotate the QLabel
    QTransform transform;
    transform.rotate(45); // Rotate by 45 degrees
    car1->setPixmap(car1Pixmap.transformed(transform));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
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