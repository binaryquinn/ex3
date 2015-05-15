#include "healthtrack.h"

HealthTrack::HealthTrack(QObject *parent):QAbstractTableModel(parent)
{

    QList<CombatConstants::Wounds> hLevel;
    hLevel << CombatConstants::None;
    for(int loop = 0; loop <5;loop++)
        myHealth.append(hLevel);
    myHealth[1]<< CombatConstants::None;
    myHealth[2]<< CombatConstants::None;
}

HealthTrack::~HealthTrack()
{

}

int HealthTrack::rowCount(const QModelIndex &parent) const
{

}

int HealthTrack::columnCount(const QModelIndex &parent) const
{

}

QVariant HealthTrack::data(const QModelIndex &index, int role) const
{

}

bool HealthTrack::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

Qt::ItemFlags HealthTrack::flags(const QModelIndex &index) const
{

}

bool HealthTrack::insertRows(int row, int count, const QModelIndex &parent)
{

}

bool HealthTrack::removeRows(int row, int count, const QModelIndex &parent)
{

}

