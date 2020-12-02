#include "person.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QFile>
#include <QDebug>


Person::Person(QObject *parent):m_addr(),m_phones(){

};
Person::~Person(){

};

//Person::Person(const Person &p){
//    this->m_firstName = p.m_firstName;
//    this->m_lastName = p.m_lastName;
//    this->m_age = p.m_age;
//    this->m_addr = p.m_addr;
//    this->m_phones = p.m_phones;
//};
//Person Person::operator=( Person &p){
//    if(this != &p){
//        Person temp = p;
//        this->m_firstName = temp.m_firstName;
//        this->m_lastName = temp.m_lastName;
//        this->m_age = temp.m_age;
//        this->m_addr = temp.m_addr;
//        this->m_phones = temp.m_phones;
//    }
//    return *this;
//}


QString Person::getFirstName(){
    return m_firstName;
};
QString Person::getLastName(){
    return m_lastName;
};
int Person::getAge(){
    return m_age;
};
QVariantMap Person::getAddress(){
    QVariantMap map;
    map["street"] = QVariant(m_addr.Street);
    map["city"] = QVariant(m_addr.City);
    map["country"] = QVariant(m_addr.Country);
    qDebug()<<"街道:"<<m_addr.Street<<"; 城市:"<<m_addr.City<<"; 乡镇:"<<m_addr.Country;
    return map;
};
QVector<QString> Person::getPhones(){
    return m_phones;
};

void Person::setFirstName(const QString &f){
    this->m_firstName = f;
};
void Person::setLastName(const QString &l){
    this->m_lastName = l;
};
void Person::setAge(int age){
    this->m_age = age;
};
void Person::setAddress(const QVariantMap &add){
    m_addr.Street = add["Street"].toString();
    m_addr.City = add["City"].toString();
    m_addr.Country = add["Country"].toString();
};
void Person::setPhones(const QVector<QString> &vec){
    this->m_phones = vec;
};

void Person::loadJson(){
    QFile loadFile(":/json/test.json");
    qDebug()<<"开始解析地址";
    if (!loadFile.open(QIODevice::ReadOnly | QFile::Text)) {
          qWarning("Couldn't open save file.");
       return;
    }

    QJsonParseError error;
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData,&error));


    qDebug()<<"开始解析json数据:"<<error.errorString();

    if(loadDoc.isObject()){
        QJsonObject obj = loadDoc.object();
        QJsonValue firstName = obj["FirstName"];
        setFirstName(firstName.toString());

        QJsonValue lastName = obj["LastName"];
        setLastName(lastName.toString());

        QJsonValue age = obj["Age"];
        setAge(age.toInt());

        //解析地址对象
        QJsonValue address = obj["Address"];
        QJsonObject addrObj = address.toObject();


        QJsonObject::const_iterator iter = addrObj.constBegin();
        for(;iter != addrObj.constEnd();iter++){
            qDebug()<<"key :"<<iter.key() <<  "value: "<<iter.value().toString();
        }


        QStringList list = addrObj.keys();
        int size = addrObj.length();
        QVariantMap map;
        for(int i = 0;i<size;i++){
            QString key = list.at(i);
            map[key] = QVariant(addrObj.take(key).toString());
        }
        setAddress(map);

        //解析电话数组
        QJsonValue phoneNumbers = obj["Phone numbers"];
        QJsonArray phoneArr = phoneNumbers.toArray();
        m_phones.clear();
        for(int i=0;i<phoneArr.count();i++){
            QJsonValue item = phoneArr[i];
            m_phones.append(item.toString());
        }


        qDebug()<<"对象:"<<phoneNumbers.isObject()<<"; 数组:"<<phoneNumbers.isArray();
        loadFile.close();
    }
}
