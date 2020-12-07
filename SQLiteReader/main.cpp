#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTextCodec>
#include "people.h"
#include "sqlitehelper.h"
#include <QQuickView>
#include <QDebug>
#include <QMap>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    //设置中文支持
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    qmlRegisterType<People>("People",1,0,"People");
    qmlRegisterType<SqliteHelper>("SqliteHelper",1,0,"SqliteHelper");
    qRegisterMetaType<People>("People");
    qRegisterMetaType<People>("People&");
    qRegisterMetaType<People*>("People*");
    qRegisterMetaType<QList<People>>("QList<People>");
    qRegisterMetaType<QList<People*>>("QList<People*>");
    //qRegisterMetaType<SqliteHelper>("SqliteHelper");

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
