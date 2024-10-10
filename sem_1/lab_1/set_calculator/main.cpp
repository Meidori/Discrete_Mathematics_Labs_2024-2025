#include "setcalculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetCalculator w;
    w.show();
    return a.exec();
}
