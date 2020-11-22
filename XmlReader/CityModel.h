#include <QList>
#include <QString>
#include <QObject>
#include <QMetaType>

#include <stdlib.h>
#include <thread>


#ifndef CITYMODEL_H
#define CITYMODEL_H

using namespace std;

class CityModel : public QObject{
    Q_GADGET
    Q_PROPERTY(QString name READ name WRITE setName);
    Q_PROPERTY(QStringList areas READ getAreas);


public:
    explicit CityModel(QObject *n=nullptr);
    ~CityModel();
    CityModel(const CityModel &c);
    CityModel operator=(const CityModel &c);
    CityModel* operator=(const CityModel *const c);

    void setName(const QString &n);
    Q_INVOKABLE QString name() const{return m_name;}

    Q_INVOKABLE QStringList getAreas() const;
    void setAreas(QStringList const&area);

    void appendArea(QString &areaName);
    void clearAreas();

private:
    QString m_name;
    QStringList m_areas;

};

Q_DECLARE_METATYPE(CityModel);

#endif // CITYMODEL_H
