#include <QList>
#include <QString>
#include "CityModel.h"
#include <QMetaType>
#include <stdlib.h>
#include <thread>

#ifndef PROVINCEMDOEL_H
#define PROVINCEMDOEL_H

using namespace std;


class ProvinceModel:public QObject{
    Q_GADGET
    Q_PROPERTY(QString name READ getName WRITE setName);
    Q_PROPERTY(QList<CityModel> cities READ getCities);
public:
    explicit ProvinceModel(QObject *n=nullptr);
    ~ProvinceModel();
    ProvinceModel(const ProvinceModel &p);
    ProvinceModel operator=(const ProvinceModel &n);
    ProvinceModel* operator=(const ProvinceModel *n);


    void setName(const QString &n);
    void appendCity(CityModel &city);
    void setCities(QList<CityModel> const&city);

    Q_INVOKABLE QList<CityModel> getCities() const;
    Q_INVOKABLE QString getName() const;
    void clearCity();

private:
     QString m_name;
     QList<CityModel> m_cities;
};

Q_DECLARE_METATYPE(ProvinceModel);
#endif // PROVINCEMDOEL_H
