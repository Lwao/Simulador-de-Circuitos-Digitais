#include "circuitomain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CircuitoMain w;
    w.show();

    return a.exec();
}
