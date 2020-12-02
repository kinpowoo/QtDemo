#include "people.h"

People::People(QObject* parent):firstName(),lastName()
{
    age = 0;
}
People::~People(){

}

People::People(const People &p){
    this->firstName = p.firstName;
    this->lastName = p.lastName;
    this->age = p.age;
}
People& People::operator=(const People &p){
    if(this!=&p){
        People tmp = p;
        this->firstName = p.firstName;
        this->lastName = p.lastName;
        this->age = p.age;
    }
    return *this;
}


QString People::getFirstName() const{
    return firstName;
}
QString People::getLastName() const{
    return lastName;
}
int People::getAge() const{
    return age;
}

void People::setFirstName(const QString &n){
    firstName = n;
}
void People::setLastName(const QString &n){
    lastName = n;
}
void People::setAge(const int a){
    age = a;
}
