#include "ProvinceModel.h"

ProvinceModel::ProvinceModel():m_name(),m_cities(){

}

ProvinceModel::~ProvinceModel(){

}


void ProvinceModel::setName(const QString &n){
    m_name = n;
}


void ProvinceModel::appendCity(CityModel *city){
    m_cities.append(city);
}

QList<CityModel*> ProvinceModel::getCities() const{
    return m_cities;
}

void ProvinceModel::clearCity(){
    m_cities.clear();
}
