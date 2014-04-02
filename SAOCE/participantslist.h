#ifndef PARTICIPANTSLIST_H
#define PARTICIPANTSLIST_H

#include <QList>
#include "participant.h"

class ParticipantsList
{
public:
    ParticipantsList();
    ~ParticipantsList();

    bool Add(Participant*);


private:
    QList<Participant*>* _list;
};

#endif // PARTICIPANTSLIST_H
