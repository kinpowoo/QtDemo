#include "sqlitehelper.h"

SqliteHelper::SqliteHelper(QObject *obj)
{
    //参数一为连接的数据库类型，这里连接的是 SQLITE3
    //参数二为连接的名字，如果不填默认为 default
    db = QSqlDatabase::addDatabase("QSQLITE","localConnect");

    // 设置数据库名与路径, 此时是放在上一个目录
    db.setDatabaseName( "testdatabase.db" );
    //打开连接
    if( !db.open() )
    {
      qDebug() << db.lastError();
      qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    //各种操作
    QSqlQuery qry;
    //创建table
    qry.prepare( "CREATE TABLE IF NOT EXISTS names (id INTEGER UNIQUE PRIMARY KEY autoincrement, firstname VARCHAR(30), lastname VARCHAR(30), age INTEGER)" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug() << "Table created!";
}

SqliteHelper::~SqliteHelper(){
    db.close();
}

SqliteHelper::SqliteHelper(const SqliteHelper &p){
}
SqliteHelper& SqliteHelper::operator=(const SqliteHelper &p){
    return *this;
}


bool insert(const People &p){
    //增
    QSqlQuery qry;
    qry.prepare( "INSERT INTO names (firstname, lastname,age) VALUES (?,?,?)");
    qry.bindValue(0,QVariant(p.getFirstName()));
    qry.bindValue(1,QVariant(p.getLastName()));
    qry.bindValue(2,QVariant(p.getAge()));
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return false;
     }else{
        qDebug( "Inserted!" );
        if(qry.numRowsAffected()>0)
            return true;
        else
            return false;
    }
}
bool update(int rowId,const People &p){
    QSqlQuery qry;
    qry.prepare( "UPDATE names SET firstname='?',lastname='?',age=? WHERE id=?");
    qry.bindValue(0,QVariant(p.getFirstName()));
    qry.bindValue(1,QVariant(p.getLastName()));
    qry.bindValue(2,QVariant(p.getAge()));
    qry.bindValue(3,QVariant(rowId));
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return false;
     }else{
        qDebug( "Update!" );
        if(qry.numRowsAffected()>0)
            return true;
        else
            return false;
    }
}
bool del(int rowId){
    QSqlQuery qry;
    qry.prepare( "DELETE FROM names WHERE id=?");
    qry.bindValue(0,QVariant(rowId));
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return false;
     }else{
        qDebug( "Delete!" );
        if(qry.numRowsAffected()>0)
            return true;
        else
            return false;
    }
}
bool del(const QString &c1,const QString &c2){
    QSqlQuery qry;
    qry.prepare( "DELETE FROM names WHERE firstname='?' AND lastname='?'");
    qry.bindValue(0,QVariant(c1));
    qry.bindValue(1,QVariant(c2));
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return false;
     }else{
        qDebug( "Delete!" );
        if(qry.numRowsAffected()>0)
            return true;
        else
            return false;
    }
}
QVariantList queryAll(){
    QSqlQuery qry;
    qry.prepare("SELECT firstname,lastname,age FROM names");
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return QVariantList();
     }else{
       qDebug( "Selected!" );

       QSqlRecord rec = qry.record();
       int cols = rec.count();
       for( int c=0; c<cols; c++ )
           qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

       QVariantList list;
       for(int r=0; qry.next(); r++ ){
           People p;
           for( int c=0; c<cols; c++ ){
               QString value = qry.value(c).toString();
               if(c==0){
                   p.setFirstName(value);
               }else if(c==1){
                   p.setLastName(value);
               }else if(c==2){
                   p.setAge(value.toInt());
               }
               qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
           }
           list<<QVariant::fromValue(p);
       }
       return list;
    }
}
QVariantList queryByLimit(int limit){
    QSqlQuery qry;
    qry.prepare("SELECT firstname,lastname,age FROM names limit=?");
    qry.bindValue(0,QVariant(limit));
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return QVariantList();
     }else{
       qDebug( "Selected!" );

       QSqlRecord rec = qry.record();
       int cols = rec.count();
       for( int c=0; c<cols; c++ )
           qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

       QVariantList list;
       for(int r=0; qry.next(); r++ ){
           People p;
           for( int c=0; c<cols; c++ ){
               QString value = qry.value(c).toString();
               if(c==0){
                   p.setFirstName(value);
               }else if(c==1){
                   p.setLastName(value);
               }else if(c==2){
                   p.setAge(value.toInt());
               }
               qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
           }
           list<<QVariant::fromValue(p);
       }
       return list;
    }
}
QVariantList queryByCond(const QString &c1,const QString &c2){
    QSqlQuery qry;
    qry.prepare("SELECT firstname,lastname,age FROM names WHRER firstname='?' AND lastname='?'");
    qry.bindValue(0,QVariant(c1));
    qry.bindValue(1,QVariant(c2));
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return QVariantList();
     }else{
       qDebug( "Selected!" );

       QSqlRecord rec = qry.record();
       int cols = rec.count();
       for( int c=0; c<cols; c++ )
           qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

       QVariantList list;
       for(int r=0; qry.next(); r++ ){
           People p;
           for( int c=0; c<cols; c++ ){
               QString value = qry.value(c).toString();
               if(c==0){
                   p.setFirstName(value);
               }else if(c==1){
                   p.setLastName(value);
               }else if(c==2){
                   p.setAge(value.toInt());
               }
               qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
           }
           list<<QVariant::fromValue(p);
       }
       return list;
    }
}
QVariant queryById(int rowId){
    QSqlQuery qry;
    qry.prepare("SELECT firstname,lastname,age FROM names WHERE id=?");
    qry.bindValue(0,QVariant(rowId));
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return QVariant();
     }else{
       qDebug( "Selected!" );

       QSqlRecord rec = qry.record();
       int cols = rec.count();
       for( int c=0; c<cols; c++ )
           qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

       QVariantList list;
       for(int r=0; qry.next(); r++ ){
           People p;
           for( int c=0; c<cols; c++ ){
               QString value = qry.value(c).toString();
               if(c==0){
                   p.setFirstName(value);
               }else if(c==1){
                   p.setLastName(value);
               }else if(c==2){
                   p.setAge(value.toInt());
               }
               qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
           }
           list<<QVariant::fromValue(p);
       }
       return list.at(0);
    }
}
