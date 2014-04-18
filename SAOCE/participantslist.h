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

    QList<Participant*>* _list;

private:
};

#endif // PARTICIPANTSLIST_H
