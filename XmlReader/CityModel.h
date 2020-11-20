#include <QList>
#include <QString>
#include <QObject>
#include <QMetaType>

#ifndef CITYMODEL_H
#define CITYMODEL_H

class CityModel{
    //Q_OBJECT
    //Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
    //Q_PROPERTY(QList<QString> areas READ getAreas NOTIFY areasChanged);


public:
    explicit CityModel();
    ~CityModel();

    void setName(const QString &n);
    QString name() const{return m_name;}

    QList<QString> getAreas() const;
    void appendArea(QString &areaName);
    void clearAreas();

private:
    QString m_name;
    QList<QString> areas;

};

Q_DECLARE_METATYPE(CityModel);

#endif // CITYMODEL_H
