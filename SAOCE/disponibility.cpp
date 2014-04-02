#include "disponibility.h"
#include <iostream>
#include <ctime>
#include <string>

Disponibility::Disponibility(QGeoAddress address, time_t intervalStart, time_t intervalEnd) :
    _address(address), _disponnibilityIntervalStart(intervalStart), _disponnibilityIntervalEnd(intervalEnd)
{
    std::clog << "Disponnibilité : Instantiating" ;
    std::clog << address.text().toUtf8().constData() << " - ";


    struct tm * timeinfo;
    timeinfo = localtime (&intervalEnd);
    time_t timedispo = mktime(timeinfo);
    std::clog << ctime(&timedispo);

    timeinfo = localtime (&intervalStart);
    timedispo = mktime(timeinfo);
    std::clog << ctime(&timedispo) << std::endl;
}

Disponibility::~Disponibility()
{
}
