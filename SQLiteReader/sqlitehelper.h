#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlTableModel>
#include <QtSql/QtSql>
#include <QtSql/QtSqlVersion>
#include <QtDebug>
#include <QVariantMap>
//#include <QMetaType>

#include "people.h"

class SqliteHelper:public QObject
{
    Q_OBJECT

public:
    SqliteHelper(QObject *obj = 0);
    ~SqliteHelper();
//    SqliteHelper(const SqliteHelper &p);
//    SqliteHelper& operator=(const SqliteHelper &p);

    Q_INVOKABLE QVariantMap insert(const QJsonValue &p);
    Q_INVOKABLE bool update(int rowId,const QJsonValue &p);
    Q_INVOKABLE bool del(int rowId);
    Q_INVOKABLE bool delAll();
    Q_INVOKABLE bool del(const QString &c1,const QString &c2);
    Q_INVOKABLE QVariantList queryAll();
    Q_INVOKABLE QVariantList queryByLimit(int limit);
    Q_INVOKABLE QVariantList queryByCond(const QString &c1,const QString &c2);

private:
    QSqlDatabase db;
    QList<People*> m_list;

};

//Q_DECLARE_METATYPE(SqliteHelper)

#endif // SQLITEHELPER_H
