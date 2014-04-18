#include "participant.h"
#include <iostream>

Participant::Participant(QString name, QString lastName, int places) : _name(name), _lastName(lastName), _availablesPlacesCount(places)
{
    _disponibilities = new QList<Disponibility*>();
    std::clog << "Participant --> " << name.toUtf8().constData() << " - " << lastName.toUtf8().constData() << ", (" << places << " places disponnibles) : Instantiating\n";
}

Participant::~Participant()
{
    std::string completeName = this->ToString();
    std::clog << "Participant --> " << completeName << ": Start destroying\n";
    for( int i=_disponibilities->count()-1; i>=0; i--)
    {
        delete _disponibilities->at(i);
        _disponibilities->removeAt(i);
    }
    delete _disponibilities;
    std::clog << "Participant --> " << completeName << ": End clearing data\n";
}


bool Participant::HasCar()
{
    return _availablesPlacesCount != 0;
}
int Participant::GetAvailablesPlacesCount()
{
    return _availablesPlacesCount;
}


void Participant::AddDisponnibility(Disponibility* dispo)
{
    _disponibilities->append(dispo);
}

std::string Participant::ToString()
{
    std::string separator = " - ";
    return this->_name.toUtf8().constData() + separator +
           this->_lastName.toUtf8().constData();
}
