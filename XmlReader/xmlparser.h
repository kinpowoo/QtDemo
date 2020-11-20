#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include "mythread.h"
#include "task.h"
#include "cppthread/taskqueue.h"
#include <qmap.h>
#include <QMap>
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
    void parseFinish(const ProvinceModel &data) const;


public slots:
    void parse();   //开始解析


private:
    void readElement(QXmlStreamReader &reader);
    void writeXML();
    void test();

private:
    MyThread *myThread;
    int curPid;
    int curCid;
    QList<ProvinceModel*> saveData;
    QList<CityModel*> cityData;
    QList<QString> areaData;
};

#endif // XMLPARSER_H
