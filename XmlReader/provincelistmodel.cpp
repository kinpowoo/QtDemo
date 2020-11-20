#include "provincelistmodel.h"


ProvinceListModel::ProvinceListModel(const QList<ProvinceModel*> provinceList, QObject *parent)
    :QAbstractListModel(parent),m_provinceList(provinceList)
{

}

Qt::ItemFlags ProvinceListModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index);//默认是ItemIsEnabled ItemIsSelectable
}

QVariant ProvinceListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() > m_provinceList.size())
        return QVariant();
    if(role == Qt::DisplayRole){
        return QVariant(m_provinceList.at(index.row())->name());
    }
    else
        return QVariant();
}

QVariant ProvinceListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);//列号
    if(orientation == Qt::Vertical)
        return QString("Row %1").arg(section);//行号
}

int ProvinceListModel::rowCount(const QModelIndex &parent) const
{
    return m_provinceList.count();
}
