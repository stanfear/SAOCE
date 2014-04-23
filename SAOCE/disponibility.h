#ifndef DISPONIBILITY_H
#define DISPONIBILITY_H

#include <QObject>
#include <QGeoAddress>
#include <QTime>

class Disponibility
{
public:
    Disponibility(QGeoAddress, QTime, QTime);
    ~Disponibility();

    QString GetDetailedString();
    QTime getDispoStart();
    QTime getDispoEnd();

private:
    QGeoAddress _address;
    QTime _disponnibilityIntervalStart;
    QTime _disponnibilityIntervalEnd;

};

#endif // DISPONIBILITY_H
