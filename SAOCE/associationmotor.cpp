#include "associationmotor.h"

AssociationMotor::AssociationMotor()
{
    _PartList = new ParticipantsList();
    _AssocList = new AssociationList();
}

AssociationMotor::~AssociationMotor()
{
    delete _PartList;
    delete _AssocList;
}


bool AssociationMotor::AddParticipant(Participant* participant)
{
    _PartList->Add(participant);
}
