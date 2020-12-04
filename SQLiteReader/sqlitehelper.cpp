#include "sqlitehelper.h"

SqliteHelper::SqliteHelper(QObject *obj):m_list()
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
    QSqlQuery qry = db.exec();
    //创建table
    qry.prepare("CREATE TABLE IF NOT EXISTS names (id INTEGER UNIQUE PRIMARY KEY autoincrement, firstname VARCHAR(30), lastname VARCHAR(30), age INTEGER)" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug() << "Table created!";
}

SqliteHelper::~SqliteHelper(){
    db.close();
}

//SqliteHelper::SqliteHelper(const SqliteHelper &p){
//}
//SqliteHelper& SqliteHelper::operator=(const SqliteHelper &p){
//    return *this;
//}


bool SqliteHelper::insert(const QJsonValue &p){
    //增
    qDebug()<<"firstName:"<<p["firstName"].toString()
           <<"; lastName:"<<p["lastName"].toString()
           <<"; age:"<<p["age"].toInt();

    QSqlQuery qry = db.exec();
    bool isPrepare = qry.prepare( "INSERT INTO names (firstname, lastname,age) VALUES (?,?,?)");
    if(!isPrepare){
        qDebug() << qry.lastError();
        return false;
    }

    qry.bindValue(0,QVariant(p["firstName"].toString()));
    qry.bindValue(1,QVariant(p["lastName"].toString()));
    qry.bindValue(2,QVariant(p["age"].toInt()));

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
bool SqliteHelper::update(int rowId,const QJsonValue &p){
    QSqlQuery qry = db.exec();
    QString c1 = p["firstName"].toString();
    QString c2 = p["lastName"].toString();
    int age = p["age"].toInt();

    bool isPrepare = qry.prepare( "UPDATE names SET firstname=?,lastname=?,age=? WHERE id=?");
    if(!isPrepare){
        qDebug() << qry.lastError();
        return false;
    }
    qry.bindValue(0,QVariant(c1));
    qry.bindValue(1,QVariant(c2));
    qry.bindValue(2,QVariant(age));
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
bool SqliteHelper::del(int rowId){
    QSqlQuery qry = db.exec();
    bool isPrepare = qry.prepare( "DELETE FROM names WHERE id=?");
    if(!isPrepare){
        qDebug() << qry.lastError();
        return false;
    }
    qry.bindValue(0,QVariant(rowId));
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return false;
     }else{
        qDebug()<<"Delete!" <<rowId;
        if(qry.numRowsAffected()>0)
            return true;
        else
            return false;
    }
}
bool SqliteHelper::delAll(){
    QSqlQuery qry = db.exec();
    bool isPrepare = qry.prepare( "DELETE FROM names WHERE 1=1");
    if(!isPrepare){
        qDebug() << qry.lastError();
        return false;
    }
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return false;
     }else{
        qDebug( "Delete All!" );
        if(qry.numRowsAffected()>0)
            return true;
        else
            return false;
    }
}
bool SqliteHelper::del(const QString &c1,const QString &c2){
    QSqlQuery qry = db.exec();
    bool isPrepare = false;
    if((c1 != NULL && c1.trimmed() != "") && (c2 == NULL || c2.trimmed() == "")){
        isPrepare = qry.prepare("DELETE FROM names WHERE firstname=?");
        if(!isPrepare){
            qDebug() << qry.lastError();
            return false;
        }
        qry.bindValue(0,QVariant(c1));
    }else  if((c2 != NULL && c2.trimmed() != "") && (c1 == NULL || c1.trimmed() == "")){
        isPrepare = qry.prepare("DELETE FROM names WHERE lastname=?");
        if(!isPrepare){
            qDebug() << qry.lastError();
            return false;
        }
        qry.bindValue(0,QVariant(c2));
    }else{
        isPrepare = qry.prepare("DELETE FROM names WHERE firstname=? AND lastname=?");
        if(!isPrepare){
            qDebug() << qry.lastError();
            return false;
        }
        qry.bindValue(0,QVariant(c1));
        qry.bindValue(1,QVariant(c2));
    }
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
QVariantList SqliteHelper::queryAll(){
    QSqlQuery qry = db.exec();
    m_list.clear();
    bool isPrepare = qry.prepare("SELECT id,firstname,lastname,age FROM names");
    if(!isPrepare){
        qDebug() << qry.lastError();
        return QVariantList();
    }
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return QVariantList();
     }else{
       qDebug( "Selected!" );

       QSqlRecord rec = qry.record();
       int cols = rec.count();
       QVariantList list;
       if(qry.isActive() && qry.isSelect()){

           int r=0;
           while(qry.next()){
               People *p = new People();
               People p2;
               for( int c=0; c<cols; c++ ){
                   QString value = qry.value(c).toString();
                   if(c == 0){
                       p->setId(value.toInt());
                       p2.setId(value.toInt());
                   }else if(c==1){
                       p->setFirstName(value);
                       p2.setFirstName(value);
                   }else if(c==2){
                       p->setLastName(value);
                       p2.setLastName(value);
                   }else if(c==3){
                       p->setAge(value.toInt());
                       p2.setAge(value.toInt());
                   }
                   qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
               }
               list<<QVariant::fromValue(p);
               r++;
           }
           return list;
       }else{
           qDebug()<<"没有查询到记录";
           return QVariantList();
       }
    }
}


QVariantList SqliteHelper::queryByLimit(int limit){
    QSqlQuery qry = db.exec();
    bool isPrepare = qry.prepare("SELECT id,firstname,lastname,age FROM names limit ?");
    if(!isPrepare){
        qDebug() << qry.lastError();
        return QVariantList();
    }
    qry.bindValue(0,QVariant(limit));
    if(!qry.exec() ){
        qDebug() << qry.lastError();
        return QVariantList();
     }else{
       qDebug( "Selected!" );

       QSqlRecord rec = qry.record();
       int cols = rec.count();
       for( int c=0; c<cols; c++ )
           qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

       if(qry.isActive() && qry.isSelect()){
           QVariantList list;
           int r = 0;
           while(qry.next()){
               People p;
               for( int c=0; c<cols; c++ ){
                   QString value = qry.value(c).toString();
                   if(c == 0){
                       p.setId(value.toInt());
                   }else if(c==0){
                       p.setFirstName(value);
                   }else if(c==1){
                       p.setLastName(value);
                   }else if(c==2){
                       p.setAge(value.toInt());
                   }
                   //qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
               }
               list.append(QVariant::fromValue(p));
               r++;
           }
           return list;
       }else{
           return QVariantList();
       }
    }
}



QVariantList SqliteHelper::queryByCond(const QString &c1,const QString &c2){
    QSqlQuery qry = db.exec();
    bool isPrepare = false;
    if((c1 != NULL && c1.trimmed() != "") && (c2 == NULL || c2.trimmed() == "")){
        isPrepare = qry.prepare("SELECT id,firstname,lastname,age FROM names WHERE firstname like ?");
        if(!isPrepare){
            qDebug() << qry.lastError();
            return QVariantList();
        }
        qry.bindValue(0,QVariant(c1));
    }else  if((c2 != NULL && c2.trimmed() != "") && (c1 == NULL || c1.trimmed() == "")){
        isPrepare = qry.prepare("SELECT id,firstname,lastname,age FROM names WHERE lastname like ?");
        if(!isPrepare){
            qDebug() << qry.lastError();
            return QVariantList();
        }
        qry.bindValue(0,QVariant(c2));
    }else{
        isPrepare = qry.prepare("SELECT id,firstname,lastname,age FROM names WHERE firstname like ? AND lastname like ?");
        if(!isPrepare){
            qDebug() << qry.lastError();
            return QVariantList();
        }
        qry.bindValue(0,QVariant(c1));
        qry.bindValue(1,QVariant(c2));
    }

    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return QVariantList();
     }else{
       qDebug( "Selected!" );

       QSqlRecord rec = qry.record();
       int cols = rec.count();
       for( int c=0; c<cols; c++ )
           qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

       if(qry.isActive() && qry.isSelect()){
           QVariantList list;
           int r = 0;
           while(qry.next()){
               People *p = new People();
               for( int c=0; c<cols; c++ ){
                   QString value = qry.value(c).toString();
                   if(c == 0){
                       p->setId(value.toInt());
                   }else if(c==0){
                       p->setFirstName(value);
                   }else if(c==1){
                       p->setLastName(value);
                   }else if(c==2){
                       p->setAge(value.toInt());
                   }
//                   qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
               }
               list.append(QVariant::fromValue(p));
               r++;
           }
           return list;
       }else{
           return QVariantList();
       }
    }
}
