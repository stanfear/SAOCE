#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QProgressDialog>
#include "dialogcreateparticipant.h"

#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), motor()
{
    ui->setupUi(this);

    connect(ui->AddParticipant, SIGNAL(clicked()), this, SLOT(AddParticipant_Click()));
    connect(ui->ResetAssociations, SIGNAL(clicked()), this, SLOT(ResetAssociations_Click()));
    connect(ui->DeleteParticipant, SIGNAL(clicked()), this, SLOT(DeleteParticipant_Click()));
    connect(ui->ComputeAssociations, SIGNAL(clicked()), this, SLOT(ComputeAssociations_Click()));

    ui->treeView_2->setModel(motor._AssocList);
    ui->treeView->setModel(motor._PartList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddParticipant_Click()
{
    DialogCreateParticipant diag;
    int ret = diag.exec();

    if(ret == QMessageBox::Accepted)
    {
        Participant *part = diag.GetGeneratedParticipant();
        motor.AddParticipant(part);
    }

    motor._PartList->UpdateDataFromScratch();
    ui->treeView->reset();

}


void MainWindow::DeleteParticipant_Click()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    this->motor._PartList->RemoveParticipant(index);


    motor._PartList->UpdateDataFromScratch();
    ui->treeView->reset();
}

void MainWindow::ResetAssociations_Click()
{
    QMessageBox msgBox;
    msgBox.setText("Les Associations seront supprimés");
    msgBox.setInformativeText("Voullez-vous vraiment supprimer toutes les associations ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Warning);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Ok) // Ok was clicked
        motor.ResetAssociationList();

    ui->treeView_2->setModel(motor._AssocList);
    motor._AssocList->UpdateDataFromScratch();
    ui->treeView_2->reset();
}

void MainWindow::ComputeAssociations_Click()
{
    QProgressDialog *progress = new QProgressDialog("Computing Associations", "Abort Computing", 0, 100, this);
    progress->setWindowModality(Qt::WindowModal);

    progress->show();
    progress->setValue(0);

    progress->setLabelText("Calcul de la meilleur combinaison d'association (1/2)");
    motor.ComputeAssociationsValues(progress);

    progress->setValue(0);

    progress->setLabelText("Calcul de la meilleur combinaison d'association (2/2)");
    motor.ComputeAssociationsMethode1(progress);

    progress->setValue(100);
    delete progress;

    motor._AssocList->UpdateDataFromScratch();
    ui->treeView_2->reset();
}
