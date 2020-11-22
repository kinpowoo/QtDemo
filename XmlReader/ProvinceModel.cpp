#include "ProvinceModel.h"

ProvinceModel::ProvinceModel(QObject *n):m_name(),m_cities(){
}

ProvinceModel::~ProvinceModel(){

}

ProvinceModel::ProvinceModel(const ProvinceModel &p){
    this->m_name = p.m_name;
    QList<CityModel> nCities;
    this->m_cities.clear();
    for(CityModel c : p.getCities()){
        this->m_cities.append(c);
    }
}
ProvinceModel ProvinceModel::operator=(const ProvinceModel &n){
    if(this != &n){
        ProvinceModel temp(n);
        this->m_name = temp.m_name;
        this->m_cities = temp.getCities();
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


void ProvinceModel::appendCity(CityModel &city){
    m_cities.append(city);
}

QList<CityModel> ProvinceModel::getCities() const{
    return m_cities;
}

void ProvinceModel::setCities(QList<CityModel> const&city){
    m_cities = city;
}

void ProvinceModel::clearCity(){
    m_cities.clear();
}
