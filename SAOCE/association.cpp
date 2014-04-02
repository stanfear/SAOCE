#include "association.h"


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
    if(_driver->HasCar() && !_passenger->HasCar())
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
    // TODO : récuperer le cout de la distance
    // TODO : Calculer le cout d'eccart temps
    _cost = 1;
}
