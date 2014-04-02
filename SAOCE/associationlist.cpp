#include "associationlist.h"
#include <QPair>
#include <QList>
#include <iostream>

bool MapContains(QList< QPair<Participant*, int> >, Participant);

AssociationList::AssociationList()
{
    _list = new QList<Association*> ();
    std::clog << "Association List : Instantiating\n";
}

AssociationList::~AssociationList()
{
    std::clog << "Association List : Start clearing data (" << _list->count() << " elements to wipe)\n";
    for( int i=_list->count()-1; i>=0; i--)
    {
        delete _list->at(i);
        _list->removeAt(i);
    }
    delete _list;
    std::clog << "Association List : End clearing data\n";
}


double AssociationList::GetGeneralCost()
{
    double Cost = 0;
    return Cost;
}



bool AssociationList::IsSolutionValide()
{
    return true;
}
