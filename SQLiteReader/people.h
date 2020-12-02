#ifndef PEOPLE_H
#define PEOPLE_H
#include <QObject>
#include <QMetaType>

class People : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName)
    Q_PROPERTY(int age READ getAge WRITE setAge)
public:
    People(QObject *parent = 0);
    ~People();
    People(const People &p);
    People& operator=(const People &p);

    Q_INVOKABLE QString getFirstName() const;
    Q_INVOKABLE QString getLastName() const;
    Q_INVOKABLE int getAge() const;

    Q_INVOKABLE void setFirstName(const QString &n);
    Q_INVOKABLE void setLastName(const QString &n);
    Q_INVOKABLE void setAge(const int a);

private:
    QString firstName;
    QString lastName;
    int age;
};

Q_DECLARE_METATYPE(People)

#endif // PEOPLE_H
