
#include "CityModel.h"

CityModel::CityModel():m_name(),areas(){

}

CityModel::~CityModel(){

}


void CityModel::setName(const QString &n){
    m_name = n;
}


QList<QString> CityModel::getAreas() const
{
    return areas;
}

void CityModel::appendArea(QString &areaName){
    areas.append(areaName);
}

void CityModel::clearAreas(){
    areas.clear();
}
