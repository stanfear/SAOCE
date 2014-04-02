#ifndef ASSOCIATIONMOTOR_H
#define ASSOCIATIONMOTOR_H

#include "participant.h"
#include "participantslist.h"
#include "associationlist.h"

class AssociationMotor
{
public:
    AssociationMotor();
    ~AssociationMotor();

    bool AddParticipant(Participant*);

private:
    ParticipantsList* _PartList;
    AssociationList* _AssocList;

};

#endif // ASSOCIATIONMOTOR_H
