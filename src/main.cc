#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char* argv[])
{
    qDebug() << "Hello World!";
    QApplication a(argc, argv);

    QTranslator translator;
    if (translator.load("usnake_zh_CN.qm"))
    {
        a.installTranslator(&translator);
    }

    MainWindow w;

    qDebug() << "Hello World!";
    w.show();

    return a.exec();
}
