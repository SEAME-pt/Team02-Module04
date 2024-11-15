#include "../include/RacingGame.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RacingGame w;

    w.show();
    w.pauseRace();
    return a.exec();
}
