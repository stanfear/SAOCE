#ifndef ASSOCIATIONMOTOR_H
#define ASSOCIATIONMOTOR_H

#include "participant.h"
#include "participantslist.h"
#include "associationlist.h"

class AssociationMotor
{
public:

    AssociationList* _AssocList;

    AssociationMotor();
    ~AssociationMotor();

    bool AddParticipant(Participant*);

    void ComputeAssociationsMethode1();
    void ComputeAssociationsMethode2();

    bool IsGlobalAssociationPossible();
    void ComputeAssociationsValues();

private:
    ParticipantsList* _PartList;
    QList<Association*>* _AssocDictionnary;

    Association *findAssociation(Participant*, Participant*);
    void ResetAssociationList();
    void InitLists(QList<Participant*>*, QList<Participant*>*);
    int CountDriversAssociation(Participant* participant);

};

#endif // ASSOCIATIONMOTOR_H
