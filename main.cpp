#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QList>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
