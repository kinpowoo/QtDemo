#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include "mythread.h"
#include "task.h"
#include "cppthread/taskqueue.h"
#include <qmap.h>
#include <QMap>
#include <QQmlListProperty>
#include <QQmlPropertyMap>
#include <qlist.h>
#include <QList>
#include <QString>
#include "ProvinceModel.h"
#include "CityModel.h"

class XmlParser : public QObject
{
    Q_OBJECT
public:
    explicit XmlParser(QObject *parent = nullptr);
    ~XmlParser();

signals:
    //void parseFinish(const QMap<QString,QStringList> data);
    void parseFinish(const QVariantList &data);

public slots:
    void parse();   //开始解析

public:
    Q_INVOKABLE QList<ProvinceModel*> getP();
    Q_INVOKABLE QStringList getProvinces();
    Q_INVOKABLE QStringList getCities(QString provinceName);
    Q_INVOKABLE QStringList getAreas(QString cName);

private:
    void readElement(QXmlStreamReader &reader);
    void writeXML();
    void test();

private:
    MyThread *myThread;
    int curPid;
    int curCid;

    QString curPn;
    QString curCn;

    QList<ProvinceModel*> provinces;
    QMap<QString,QList<QMap<QString,QStringList>>> saveData;
    QMap<QString,QStringList> pMap;
    QMap<QString,QStringList> cMap;
};

#endif // XMLPARSER_H
