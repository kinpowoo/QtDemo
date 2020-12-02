#include <QList>
#include <QString>
#include "CityModel.h"
#include <QQmlListProperty>
#include <QMetaType>
#include <stdlib.h>
#include <thread>
#include <QVariantList>

#ifndef PROVINCEMDOEL_H
#define PROVINCEMDOEL_H

using namespace std;


class ProvinceModel:public QObject{
    Q_GADGET
    Q_PROPERTY(QString name READ getName WRITE setName);
    Q_PROPERTY(QVariantList cities READ getCities);
public:
    explicit ProvinceModel(QObject *n=nullptr);
    ~ProvinceModel();
    ProvinceModel(const ProvinceModel &p);
    ProvinceModel operator=(const ProvinceModel &n);
    ProvinceModel* operator=(const ProvinceModel *n);


    void setName(const QString &n);
    void appendCity(CityModel *city);
    void setCities(QVariantList const&city);
    Q_INVOKABLE QList<CityModel*> gainCities() const;

    Q_INVOKABLE QVariantList getCities();
    Q_INVOKABLE QString getName() const;
    void clearCity();

private:
     QString m_name;
     QList<CityModel *> m_cities;
};

Q_DECLARE_METATYPE(ProvinceModel);
#endif // PROVINCEMDOEL_H
