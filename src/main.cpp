#include "../include/RacingGame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RacingGame w;

    w.show();

    return a.exec();
}
