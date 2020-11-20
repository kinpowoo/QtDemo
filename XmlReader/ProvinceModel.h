#include <QList>
#include <QString>
#include "CityModel.h"
#include <QMetaType>

#ifndef PROVINCEMDOEL_H
#define PROVINCEMDOEL_H


class ProvinceModel{
//    Q_OBJECT
//    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
//    Q_PROPERTY(QList<CityModel*> cities READ getCities NOTIFY citiesChanged);
public:
    explicit ProvinceModel();
    ~ProvinceModel();

    void setName(const QString &n);
    void appendCity(CityModel *city);
    QList<CityModel *> getCities() const;
    void clearCity();


    QString name() const{
        return m_name;
    }
private:
     QString m_name;
     QList<CityModel *> m_cities;
};

Q_DECLARE_METATYPE(ProvinceModel);
#endif // PROVINCEMDOEL_H
