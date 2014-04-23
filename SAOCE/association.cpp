#include "association.h"
#include <iostream>

Association::Association(Participant* driver,Participant* passenger)
{
    if(driver->HasCar())
    {
        _driver = driver;
        _passenger = passenger;
    }
    else if(!_driver->HasCar() && _passenger->HasCar()) // le passager et conduteur ont été enregistrés dans le mauvais ordre
    {
        _driver = passenger;
        _passenger = driver;
    }
}

Association::~Association()
{

}


double Association::GetCost()
{
    if(_cost == -1)
        ComputeCost();
    return _cost;
}
// retourne vrai si le conducteur a une voiture, mais pas le passager,
// Faux Sinon
bool Association::IsValide()
{
    if(_driver->HasCar())
        return true;
    if(!_driver->HasCar() && _passenger->HasCar()) // le passager et conduteur ont été enregistrés dans le mauvais ordre
    {
        Participant* temp = _driver;
        _driver = _passenger;
        _passenger = temp;
        return true;
    }
    return false;
}
Participant *Association::GetDriver()
{
    return _driver;
}
Participant *Association::GetPassenger()
{
    return _passenger;
}

void Association::ComputeCost()
{
    double CostDist = GetCostDistance();
    double CostTime = GetCostTime();

    _cost = CostDist + CostTime;

    std::clog << "[DEBUG] - Calcul du cout de l'association : ";
    std::clog << this->_driver->GetFullName().toUtf8().constData() << " - " <<this->_passenger->GetFullName().toUtf8().constData();
    std::clog << " Cout Calcule : " << _cost << " (distance : " << CostDist << ", temps : "<< CostTime << ")" << std::endl;
}

double Association::GetCostDistance()
{
    return 0;
}

double Association::GetCostTime()
{
    QTime drivStart, drivEnd, passStart, passEnd;
    drivStart = this->_driver->GetDipsonibility(0)->getDispoStart();
    drivEnd = this->_driver->GetDipsonibility(0)->getDispoEnd();
    passStart = this->_passenger->GetDipsonibility(0)->getDispoStart();
    passEnd = this->_passenger->GetDipsonibility(0)->getDispoEnd();

    //conducteur :           |---|
    //passager :       |---|
    // renvoi :            >-<
    if(drivStart > passEnd)
        return passEnd.msecsTo(drivStart) / 60000; // renvois en nombre de minutes


    //conducteur :     |---|
    //passager :             |---|
    // renvoi :            >-< x2 (faire attendre le conducteur (et d'autre passagers) est plus cher que faire attendre un passager)
    if(drivEnd < passStart)
        return drivEnd.msecsTo(passStart) * 2 / 60000;// renvois en nombre de minutes


    //sinon ->
    //conducteur :         |-----|      |------|           |----------|         |--|
    //passager :       |-----|      OU      |-----|    OU     |---|      OU  |---------|
    // renvoi :            0                   0                0                0
    return 0;



}
