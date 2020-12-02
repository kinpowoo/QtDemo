#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "person.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //注册自定义类
    qmlRegisterType<Person>("Person",1,0,"Person");
    //qRegisterMetaType<Person>("Person");
    qRegisterMetaType<QMap<QString,QString>>("QMap<QString,QString>");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
