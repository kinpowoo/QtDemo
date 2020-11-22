#ifndef PROVINCELISTMODEL_H
#define PROVINCELISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "ProvinceModel.h"

class ProvinceListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ProvinceListModel(const QList<ProvinceModel*> provinceList, QObject *parent = 0);

protected:
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
private:
    QList<ProvinceModel *> m_provinceList;
};

#endif // PROVINCELISTMODEL_H
