#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QString>
#include "disponibility.h"
#include <string>

class Participant
{
public:
    Participant(QString name, QString lastName, int places);
    ~Participant();

    bool HasCar();
    int GetAvailablesPlacesCount();
    std::string ToString();

    private:
        QString _name;
        QString _lastName;
        int _availablesPlacesCount;
        QList<Disponibility*>* _disponibilities;

};

#endif // PARTICIPANT_H
