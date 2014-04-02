#include "participantslist.h"
#include <iostream>

ParticipantsList::ParticipantsList()
{
    _list = new QList<Participant*> ();
    std::clog << "Participants List : Instantiating\n";
}


ParticipantsList::~ParticipantsList()
{
    std::clog << "Participants List : Start clearing data (" << _list->count() << " elements to wipe)\n";
    for( int i=_list->count()-1; i>=0; i--)
    {
        delete _list->at(i);
        _list->removeAt(i);
    }
    delete _list;
    std::clog << "Participants List : End clearing data\n";
}


bool ParticipantsList::Add(Participant* part)
{
    std::clog << "Participants List : Attempt to add Participants " << part->ToString();
    if(_list->contains(part))
    {
        std::clog << " ... Failed (participant already in the list)\n";
        return false;
    }
    else
    {
        _list->append(part);
        std::clog << " ... Succeded\n";
        return true;
    }
}
