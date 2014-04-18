#ifndef ASSOCIATIONLIST_H
#define ASSOCIATIONLIST_H

#include <QList>
#include "association.h"

class AssociationList
{
public:

    QList<Association*>* _list;

    AssociationList();
    ~AssociationList();
    double GetGeneralCost();
    bool IsSolutionValide();

    bool CreateAssociation(Participant*,Participant*);

private:
};

#endif // ASSOCIATIONLIST_H
