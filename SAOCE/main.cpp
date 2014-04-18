#include "associationmotor.h"
#include "participant.h"
#include "disponibility.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <ctime>

int main(int argc, char *argv[])
{
    std::clog << argc << argv << std::endl;

    std::clog << "Programme initiation" << std::endl;

    AssociationMotor* motor = new AssociationMotor();

    std::clog << "Creating test participants" << std::endl;

    Participant* P1 = new Participant("Tristan", "Roche", 4);
    Participant* P2 = new Participant("Lorem", "Ipsum", 0);
    Participant* P3 = new Participant("floryne", "Roche", 0);


    std::clog << "attempting to create P1 adresse : ";
    QGeoAddress adresseTristan;
    adresseTristan.setCity("Bordeaux");
    adresseTristan.setCountry("France");
    adresseTristan.setCountryCode("FRA");
    adresseTristan.setStreet("30 rue Boyer");
    adresseTristan.setPostalCode("33000");
    std::clog << adresseTristan.text().toUtf8().constData() << std::endl;

    std::clog << "attempting to create P2 adresse : ";
    QGeoAddress adresseLorem;
    adresseLorem.setCity("Bordeaux");
    adresseLorem.setCountry("France");
    adresseLorem.setCountryCode("FRA");
    adresseLorem.setStreet("21 rue Boyer");
    adresseLorem.setPostalCode("33000");
    std::clog << adresseLorem.text().toUtf8().constData() << std::endl;




    std::clog << "attempting to create P1 time disponnibility : ";
    struct tm * timeInfo = new struct tm();
    timeInfo->tm_year = 2014 - 1900;
    timeInfo->tm_hour = 14;
    timeInfo->tm_mon = 4 - 1;
    timeInfo->tm_mday = 10;
    time_t timedispo = mktime(timeInfo);
    delete timeInfo;
    std::clog << ctime(&timedispo) << std::endl;


    Disponibility * dispoTristan = new Disponibility(adresseTristan, timedispo, timedispo);
    Disponibility * dispoLorem = new Disponibility(adresseLorem, timedispo, timedispo);
    Disponibility * dispofloryne = new Disponibility(adresseLorem, timedispo, timedispo);

    P1->AddDisponnibility(dispoTristan);
    P2->AddDisponnibility(dispoLorem);
    P3->AddDisponnibility(dispofloryne);


    motor->AddParticipant(P1);
    motor->AddParticipant(P2);
    motor->AddParticipant(P3);

    motor->ComputeAssociationsValues();

    if(motor->IsGlobalAssociationPossible())
        std::clog << "[DEBUG] - association Possible !!" << std::endl;
    else
        std::clog << "[DEBUG] - association non Possible !!" << std::endl;

    motor->ComputeAssociationsMethode1();



    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    delete motor;

    return EXIT_SUCCESS;//a.exec();
}
