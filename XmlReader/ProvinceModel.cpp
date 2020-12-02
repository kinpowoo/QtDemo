#include "ProvinceModel.h"

ProvinceModel::ProvinceModel(QObject *n):m_name(),m_cities(){
}

ProvinceModel::~ProvinceModel(){

}

ProvinceModel::ProvinceModel(const ProvinceModel &p){
    this->m_name = p.m_name;
    QList<CityModel> nCities;
    this->m_cities.clear();
    QList<CityModel*> tmpCities = p.gainCities();
    for(CityModel *c : tmpCities){
        this->m_cities.append(c);
    }
}
ProvinceModel ProvinceModel::operator=(const ProvinceModel &n){
    if(this != &n){
        ProvinceModel temp(n);
        this->m_name = temp.m_name;
        this->m_cities = temp.gainCities();
    }
    return *this;
}

ProvinceModel* ProvinceModel::operator=(const ProvinceModel *n){
    if(this != n){
        ProvinceModel temp(*n);
        this->m_name = temp.m_name;
        this->m_cities = temp.m_cities;
    }
    return this;
}

void ProvinceModel::setName(const QString &n){
    m_name = n;
}

QString ProvinceModel::getName() const{
    return m_name;
}


void ProvinceModel::appendCity(CityModel *city){
    m_cities.append(city);
}

QVariantList ProvinceModel::getCities(){
    QVariantList list;
    for(int i =0;i<m_cities.count();i++){
        CityModel* city = m_cities[i];
        CityModel tmp = *city;
        list << QVariant::fromValue(tmp);
    }
    return list;
}

QList<CityModel*> ProvinceModel::gainCities() const{
    return m_cities;
}

void ProvinceModel::setCities(QVariantList const&city){
    m_cities.clear();
    for(int i =0;i<city.count();i++){
        QVariant c = city.at(i);
        CityModel tmp = c.value<CityModel>();
        m_cities.append(&tmp);
    }
}

void ProvinceModel::clearCity(){
    m_cities.clear();
}
