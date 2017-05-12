#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    bool isload = translator.load(":/en_Zn");

    if (isload) {
        qDebug()<<isload<<" install Translator";
        app.installTranslator(&translator);
    }

    MainWindow w;
    w.show();

    return app.exec();
}
