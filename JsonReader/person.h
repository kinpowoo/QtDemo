#ifndef PERSON_H
#define PERSON_H

#include <QMap>
#include <QObject>
#include <QVariantMap>
#include <QVariantList>

struct Address{
    QString Street;
    QString City;
    QString Country;
};

class Person:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName);
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName);
    Q_PROPERTY(int age READ getAge WRITE setAge);
    Q_PROPERTY(QVariantMap address READ getAddress WRITE setAddress);
    Q_PROPERTY(QVector<QString> phones READ getPhones WRITE setPhones);
public:
    Person(QObject *parent = nullptr);
    ~Person();
//    Person(const Person &p);
//    Person operator=(const Person &p);

    Q_INVOKABLE QString getFirstName();
    Q_INVOKABLE QString getLastName();
    Q_INVOKABLE int getAge();
    Q_INVOKABLE QVariantMap getAddress();
    Q_INVOKABLE QVector<QString> getPhones();

    Q_INVOKABLE void setFirstName(const QString &f);
    Q_INVOKABLE void setLastName(const QString &l);
    Q_INVOKABLE void setAge(int age);
    Q_INVOKABLE void setAddress(const QVariantMap &add);
    Q_INVOKABLE void setPhones(const QVector<QString> &vec);

    Q_INVOKABLE void loadJson();  //加载json数据

private:
    QString m_firstName;
    QString m_lastName;
    int m_age;
    Address m_addr;
    QVector<QString> m_phones;
};

#endif // PERSON_H
