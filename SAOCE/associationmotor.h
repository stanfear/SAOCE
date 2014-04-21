#ifndef ASSOCIATIONMOTOR_H
#define ASSOCIATIONMOTOR_H

#include "participant.h"
#include "participantslist.h"
#include "associationlist.h"
#include <QProgressDialog>

class AssociationMotor
{
public:

    AssociationList* _AssocList;

    AssociationMotor();
    ~AssociationMotor();

    bool AddParticipant(Participant*);

    void ComputeAssociationsMethode1(QProgressDialog *progress);
    void ComputeAssociationsMethode2(QProgressDialog *progress);

    bool IsGlobalAssociationPossible();
    void ComputeAssociationsValues(QProgressDialog *progress);

    void ResetAssociationList();

private:
    ParticipantsList* _PartList;
    QList<Association*>* _AssocDictionnary;

    Association *findAssociation(Participant*, Participant*);

    void InitLists(QList<Participant*>*, QList<Participant*>*);
    int CountDriversAssociation(Participant* participant);

};

#endif // ASSOCIATIONMOTOR_H
