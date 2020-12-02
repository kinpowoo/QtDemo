
#include "CityModel.h"

CityModel::CityModel(QObject *n):m_name(),m_areas(){
}

CityModel::~CityModel(){

}

CityModel::CityModel(const CityModel &c){
    this->m_name = c.m_name;
    this->m_areas.clear();
    for(QString a : c.getAreas()){
        this->m_areas.append(a);
    }
}
CityModel &CityModel::operator=(const CityModel &c){
    if(this != &c){
        CityModel temp(c);
        m_name = temp.m_name;
        this->m_areas.clear();
        for(QString a : c.getAreas()){
            this->m_areas.append(a);
        }
    }
    return *this;
}

CityModel* CityModel::operator=(const CityModel *const c){
    if(this != c){
        CityModel temp(*c);
        m_name = temp.m_name;
        m_areas = temp.m_areas;
    }
    return this;
}

void CityModel::setName(const QString &n){
    m_name = n;
}

QString CityModel::getName() const{
    return m_name;
}

QStringList CityModel::getAreas() const
{
    return m_areas;
}

void CityModel::setAreas(QStringList const&area){
    this->m_areas = area;
}

void CityModel::appendArea(QString &areaName){
    m_areas.append(areaName);
}


void CityModel::clearAreas(){
    m_areas.clear();
}
