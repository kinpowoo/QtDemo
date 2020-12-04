#include "people.h"

People::People(QObject* parent):m_firstName(),m_lastName()
{
    m_age = 0;
}
People::~People(){

}

People::People(const People &p):QObject( nullptr ){
    this->m_firstName = p.m_firstName;
    this->m_lastName = p.m_lastName;
    this->m_age = p.m_age;
    this->m_id = p.m_id;
}
People People::operator=(const People &p){
    if(this!=&p){
        People tmp = p;
        this->m_firstName = tmp.m_firstName;
        this->m_lastName = tmp.m_lastName;
        this->m_age = tmp.m_age;
        this->m_id = tmp.m_id;
    }
    return *this;
}

People *People::operator=(const People *const c){
    if(this!= c){
        People tmp(*c);
        this->m_firstName = tmp.m_firstName;
        this->m_lastName = tmp.m_lastName;
        this->m_age = tmp.m_age;
        this->m_id = tmp.m_id;
    }
    return this;
}



QString People::getFirstName() const{
    return m_firstName;
}
QString People::getLastName() const{
    return m_lastName;
}
int People::getAge() const{
    return m_age;
}

void People::setFirstName(const QString &n){
    m_firstName = n;
}
void People::setLastName(const QString &n){
    m_lastName = n;
}
void People::setAge(const int a){
    m_age = a;
}

int People::getId() const{
    return m_id;
}
void People::setId(const int id){
    m_id = id;
}

