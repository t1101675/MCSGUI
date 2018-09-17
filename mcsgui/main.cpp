#include "mainwindow.h"
#include <QApplication>
#include <QMetaObject>
#include <QStringList>
#include <QMetaMethod>
#include <iostream>
#include <QDebug>
#include <string>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    const QMetaObject* metaObject = w.metaObject();
    QStringList methods;
    std::cout << "OK" << std::endl;
    for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i) {
        qDebug() << QString::fromLatin1(metaObject->method(i).methodSignature());
    }

    return app.exec();
}
