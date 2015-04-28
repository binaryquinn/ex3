#ifndef HEALTHTRACK_H
#define HEALTHTRACK_H

#include <QAbstractTableModel>



class HealthTrack : public QAbstractTableModel
{
    Q_OBJECT
public:
    HealthTrack(QObject *parent = 0);
    ~HealthTrack();
};

#endif // HEALTHTRACK_H
