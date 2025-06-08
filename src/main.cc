#include <QApplication>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    qDebug() << "USnake Starting";
    QApplication a(argc, argv);

    QTranslator translator;

    QLocale locale = QLocale::system();
    QString locale_name = locale.name();
    QStringList supported_locales = {"en_US", "zh_CN", "zh_TW"};
    QString matched_locale = supported_locales.contains(locale_name) ? locale_name : "en_US";

    if (translator.load("../translations/USnake_" + locale_name + ".qm"))
    {
        a.installTranslator(&translator);
    }
    else
    {
        qDebug() << "Failed to load translations";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
