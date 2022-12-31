#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>
#include <algorithm>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
