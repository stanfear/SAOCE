#include "disponibility.h"
#include <iostream>
#include <ctime>
#include <string>

Disponibility::Disponibility(QGeoAddress address, QTime intervalStart, QTime intervalEnd) :
    _address(address), _disponnibilityIntervalStart(intervalStart), _disponnibilityIntervalEnd(intervalEnd)
{
    std::clog << "Disponnibilite : Instantiating " ;
    std::clog << intervalStart.toString("[HH:mm:ss - ").toUtf8().constData();
    std::clog << intervalEnd.toString("HH:mm:ss] - ").toUtf8().constData();
    std::clog << address.text().toUtf8().constData()<< std::endl;
}

Disponibility::~Disponibility()
{
    std::clog << "Disponnibilite : Start Destroying" ;
    std::clog << _address.text().toUtf8().constData() << std::endl;
}

QString Disponibility::GetDetailedString()
{
    return _disponnibilityIntervalStart.toString("[HH:mm:ss - ") + _disponnibilityIntervalEnd.toString("HH:mm:ss] - ") + _address.text();
}


QTime Disponibility::getDispoStart()
{
    return _disponnibilityIntervalStart;
}
QTime Disponibility::getDispoEnd()
{
    return _disponnibilityIntervalEnd;
}
