#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    qDebug() << "Hello World!";
    QApplication a(argc, argv);
    MainWindow w;

    qDebug() << "Hello World!";
    w.show();

    return a.exec();
}
