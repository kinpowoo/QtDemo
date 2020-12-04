#ifndef PEOPLE_H
#define PEOPLE_H
#include <QObject>
#include <QMetaType>
#include <QVariant>
#include <QDebug>

class People : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName)
    Q_PROPERTY(int age READ getAge WRITE setAge)
    Q_PROPERTY(int id READ getId WRITE setId)
public:
    People(QObject *parent = 0);
    ~People();
    People(const People &p);
    People operator=(const People &p);
    People* operator=(const People *const c);

    Q_INVOKABLE QString getFirstName() const;
    Q_INVOKABLE QString getLastName() const;
    Q_INVOKABLE int getAge() const;
    Q_INVOKABLE int getId() const;

    Q_INVOKABLE void setFirstName(const QString &n);
    Q_INVOKABLE void setLastName(const QString &n);
    Q_INVOKABLE void setAge(const int a);
    Q_INVOKABLE void setId(const int id);
private:
    QString m_firstName;
    QString m_lastName;
    int m_age;
    int m_id;
};

Q_DECLARE_METATYPE(People)

#endif // PEOPLE_H
