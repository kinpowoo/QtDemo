#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "xmlparser.h"
#include <QQuickView>
#include <QObject>
#include <QQmlComponent>
#include <QMap>
#include "ProvinceModel.h"
#include "CityModel.h"
#include <QList>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //可以用QQmlComponent\QQuickView\QQuickWidget的C++代码加载QML文档
      //QQuickView不能用Window做根元素
    // QQmlComponent v(QUrl("qrc:/main.qml"));

     //获取到qml根对象的指针
    // QObject *qmlObj= view.rootView();
    // XmlParser xmp;
    // QObject::connect(qmlObj,SIGNAL(queryClicked()),
      //                    &xmp,SLOT(parse()));


    //qmlRegisterType注册C++类型至QML
    //arg1:import时模块名
    //arg2:主版本号
    //arg3:次版本号
    //arg4:QML类型名
    qmlRegisterType<XmlParser>("XmlParser",1,0,"XmlParse");
    qmlRegisterType<ProvinceModel>("ProvinceModel",1,0,"ProvinceModel");
    qmlRegisterType<CityModel>("CityModel",1,0,"CityModel");
    qRegisterMetaType<ProvinceModel>("ProvinceModel");
    qRegisterMetaType<ProvinceModel>("ProvinceModel&");
    qRegisterMetaType<CityModel>("CityModel");
    qRegisterMetaType<CityModel>("CityModel&");
    qRegisterMetaType<QList<ProvinceModel>>("QList<ProvinceModel>");
    qRegisterMetaType<QList<ProvinceModel>>("QList<ProvinceModel*>");
    qRegisterMetaType<QList<CityModel>>("QList<CityModel>");
    qRegisterMetaType<QList<CityModel*>>("QList<CityModel*>");
    qRegisterMetaType<QMap<QString,QStringList>>("QMap<QString,QStringList>");

    //qRegisterMetaType<QList<ProvinceModel>>("QList<ProvinceModel&>");

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
