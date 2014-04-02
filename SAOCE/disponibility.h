#ifndef DISPONIBILITY_H
#define DISPONIBILITY_H

#include <QObject>
#include <QGeoAddress>

class Disponibility
{
public:
    Disponibility(QGeoAddress, time_t, time_t);
    ~Disponibility();


private:
    QGeoAddress _address;
    time_t _disponnibilityIntervalStart;
    time_t _disponnibilityIntervalEnd;

};

#endif // DISPONIBILITY_H
