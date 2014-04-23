#include "associationmotor.h"

AssociationMotor::AssociationMotor()
{

    QStringList headersParticipant;
    headersParticipant << "Detail" << "places Disponnibles";
    _PartList = new ParticipantsList(headersParticipant, "");

    QStringList headers;
    headers << "Participant" << "Disponnibilité";

    _AssocList = new AssociationList(headers, "");
    _AssocDictionnary = new QList<Association*> ();
}

AssociationMotor::~AssociationMotor()
{
    delete _PartList;
    delete _AssocList;
    for( int i=_AssocDictionnary->count()-1; i>=0; i--)
    {
        delete _AssocDictionnary->at(i);
        _AssocDictionnary->removeAt(i);
    }
    delete _AssocDictionnary;
}


bool AssociationMotor::AddParticipant(Participant* participant)
{
    _PartList->Add(participant);
    return true;
}

/// permet de calculer la liste des associations possibles à l'avance afin d'accelerer le temps de calcul des associations
void AssociationMotor::ComputeAssociationsValues(QProgressDialog *progress)
{
    _AssocDictionnary->clear();

    int nbparticipants = this->_PartList->_list->count();
    progress->setMaximum(nbparticipants ^ 2);

    for( int i=nbparticipants-1; i>=0; i--)
    {
        progress->setValue((nbparticipants - i - 1) * nbparticipants);

        Participant *par1 = this->_PartList->_list->at(i);
        if(par1->HasCar())
        {
            for( int j=nbparticipants-1; j>=0; j--)
            {
                progress->setValue((nbparticipants - i - 1) * nbparticipants + (nbparticipants - j - 1));

                Participant *par2 = this->_PartList->_list->at(j);
                if(par1 != par2)
                {
                    Association *asso = new Association(par1,par2);
                    asso->ComputeCost();
                    _AssocDictionnary->append(asso);
                }
            }
        }
    }
}



void AssociationMotor::ComputeAssociationsMethode1(QProgressDialog *progress)
{
    QList<Participant*>* Conducteurs = new QList<Participant*>();
    QList<Participant*>* passagersRestant = new QList<Participant*>();
    InitLists(Conducteurs, passagersRestant);

    progress->setMaximum(passagersRestant->count());
    progress->setValue(0);


    while (passagersRestant->count() > 0 && Conducteurs->count() > 0)
    {
        Association *BestAssociaiton;
        int i=0;
        do{
        BestAssociaiton = _AssocDictionnary->at(i);
        i++;
        } while (!passagersRestant->contains(BestAssociaiton->GetPassenger()) || !Conducteurs->contains(BestAssociaiton->GetDriver()));
        for( int i=this->_AssocDictionnary->count()-1; i>=0; i--)
        {
            Association *assoc= this->_AssocDictionnary->at(i);
            if(passagersRestant->contains(assoc->GetPassenger()) && Conducteurs->contains(assoc->GetDriver()))
                if(assoc->GetCost() < BestAssociaiton->GetCost())
                    BestAssociaiton = assoc;
        }
        // la meilleur association possible (avec les participants restants) est utilisée
        _AssocList->_list->append(BestAssociaiton);
        // modification des listes de passagers et conducteurs restant
        if(_AssocList->CountDriversAssociation(BestAssociaiton->GetDriver()) >= BestAssociaiton->GetDriver()->GetAvailablesPlacesCount())
            Conducteurs->removeOne(BestAssociaiton->GetDriver());
        passagersRestant->removeOne(BestAssociaiton->GetPassenger());

        progress->setValue(progress->maximum() - passagersRestant->count());
    }
}

void AssociationMotor::ComputeAssociationsMethode2(QProgressDialog */*progress*/)
{}

bool AssociationMotor::IsGlobalAssociationPossible()
{
    QList<Participant*>* Conducteurs = new QList<Participant*>();
    QList<Participant*>* passagersRestant = new QList<Participant*>();
    InitLists(Conducteurs, passagersRestant);

    int totalPlacesLeft = 0;
    for( int i=Conducteurs->count()-1; i>=0; i--)
    {
        Participant *cond = Conducteurs->at(i);
        totalPlacesLeft = cond->GetAvailablesPlacesCount() - this->_AssocList->CountDriversAssociation(cond);
    }
    return totalPlacesLeft >= passagersRestant->count();
}

void AssociationMotor::ResetAssociationList()
{
    delete _AssocList;
    QStringList headers;
    headers << "Participant" << "Disponnibilité";

    _AssocList = new AssociationList(headers, "");
}

Association *AssociationMotor::findAssociation(Participant* conducteur, Participant* passager)
{
    Participant* cond;
    Participant* pass;
    if(conducteur->HasCar() && !passager->HasCar())
    {
        cond = conducteur;
        pass = passager;
    }
    else if(conducteur->HasCar() && !passager->HasCar())
    {
        cond = passager;
        pass = conducteur;
    }
    else if(!conducteur->HasCar() && !passager->HasCar())
        return 0;
    else // if(conducteur->HasCar() && passager->HasCar())
    {
        cond = conducteur;
        pass = passager;
    }


    for( int i=this->_AssocDictionnary->count()-1; i>=0; i--)
    {
        Association *assoc = this->_AssocDictionnary->at(i);
        if(assoc->GetDriver() == cond && assoc->GetPassenger() == pass)
            return assoc;
    }
    return 0;
}

void AssociationMotor::InitLists(QList<Participant*> *conducteurs, QList<Participant*> *passagersRestant)
{
    if(conducteurs == NULL)
        conducteurs = new QList<Participant*>();
    else
        conducteurs->clear();

    if(passagersRestant == NULL)
        passagersRestant = new QList<Participant*>();
    else
        passagersRestant->clear();


    for( int i=this->_PartList->_list->count()-1; i>=0; i--)
    {
        Participant *par = this->_PartList->_list->at(i);
        if(!par->HasCar())
            passagersRestant->append(par);
        else
            if(this->_AssocList->CountDriversAssociation(par) < par->GetAvailablesPlacesCount())
                conducteurs->append(par);
    }


    for( int i=this->_AssocList->_list->count()-1; i>=0; i--)
    {
        Association *assoc = this->_AssocList->_list->at(i);
        passagersRestant->removeOne(assoc->GetPassenger());
    }
    // conducteurs contient une liste de conducteurs avec au moins une placce disponnible
    // passagers restant contient les passager restant a associer
}
