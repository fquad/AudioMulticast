#include "udpsimulation.h"

#include <QApplication>

#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UDPSimulation w;
    w.show();
    return a.exec();
}
