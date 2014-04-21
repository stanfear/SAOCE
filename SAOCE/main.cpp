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


    //motor->ComputeAssociationsValues();

    /*if(motor->IsGlobalAssociationPossible())
        std::clog << "[DEBUG] - association Possible !!" << std::endl;
    else
        std::clog << "[DEBUG] - association non Possible !!" << std::endl;
*/
    //motor->ComputeAssociationsMethode1();



    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
