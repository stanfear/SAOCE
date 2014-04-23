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
    ParticipantsList* _PartList;

    AssociationMotor();
    ~AssociationMotor();

    bool AddParticipant(Participant*);

    void ComputeAssociationsMethode1(QProgressDialog *progress);
    void ComputeAssociationsMethode2(QProgressDialog *progress);

    bool IsGlobalAssociationPossible();
    void ComputeAssociationsValues(QProgressDialog *progress);

    void ResetAssociationList();

private:
    QList<Association*>* _AssocDictionnary;

    Association *findAssociation(Participant*, Participant*);

    void InitLists(QList<Participant*>*, QList<Participant*>*);
};

#endif // ASSOCIATIONMOTOR_H
