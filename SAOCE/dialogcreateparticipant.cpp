#include "dialogcreateparticipant.h"
#include "ui_dialogcreateparticipant.h"

DialogCreateParticipant::DialogCreateParticipant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateParticipant)
{
    ui->setupUi(this);
}

DialogCreateParticipant::~DialogCreateParticipant()
{
    delete ui;
}

Participant* DialogCreateParticipant::GetGeneratedParticipant()
{
    QGeoAddress adresse;
    adresse.setCity(this->ui->liVille->text());
    adresse.setStreet(this->ui->liRue->text() + this->ui->liComplement->text());
    adresse.setPostalCode(this->ui->liCP->text());

    Disponibility * dispoParticipant = new Disponibility(
                adresse,
                this->ui->timeEditStart->time(),
                this->ui->timeEditEnd->time());

    Participant *participant = new Participant(
                this->ui->leFirstName->text(),
                this->ui->leLastName->text(),
                this->ui->checkBox->isChecked() ? this->ui->spinBox->value() : 0);

    participant->AddDisponnibility(dispoParticipant);

    return participant;
}
