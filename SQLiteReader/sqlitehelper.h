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
#include <QMetaType>

#include "people.h"

class SqliteHelper:public QObject
{
    Q_OBJECT

public:
    SqliteHelper(QObject *obj = 0);
    ~SqliteHelper();
    SqliteHelper(const SqliteHelper &p);
    SqliteHelper& operator=(const SqliteHelper &p);

    bool insert(const People &p);
    bool update(int rowId,const People &p);
    bool del(int rowId);
    bool del(const QString &c1,const QString &c2);
    QVariantList queryAll();
    QVariantList queryByLimit(int limit);
    QVariantList queryByCond(const QString &c1,const QString &c2);
    QVariant queryById(int rowId);

private:
    QSqlDatabase db;

};

Q_DECLARE_METATYPE(SqliteHelper)

#endif // SQLITEHELPER_H
