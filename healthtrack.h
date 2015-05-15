#ifndef HEALTHTRACK_H
#define HEALTHTRACK_H

#include <QAbstractTableModel>
#include "combatconstants.h"


class HealthTrack : public QAbstractTableModel
{
    Q_OBJECT
public:
    HealthTrack(QObject *parent = 0);
    ~HealthTrack();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    QList< QList<CombatConstants::Wounds> > myHealth;
};

#endif // HEALTHTRACK_H
