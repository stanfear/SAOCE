#ifndef ASSOCIATIONLIST_H
#define ASSOCIATIONLIST_H

#include <QList>
#include "association.h"

class AssociationList
{
public:
    AssociationList();
    ~AssociationList();
    double GetGeneralCost();
    bool IsSolutionValide();

    bool CreateAssociation(Participant*,Participant*);

private:
    QList<Association*>* _list;
};

#endif // ASSOCIATIONLIST_H
