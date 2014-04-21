#ifndef DIALOGCREATEPARTICIPANT_H
#define DIALOGCREATEPARTICIPANT_H

#include <QDialog>
#include "participant.h"

namespace Ui {
class DialogCreateParticipant;
}

class DialogCreateParticipant : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreateParticipant(QWidget *parent = 0);
    ~DialogCreateParticipant();
    Participant* GetGeneratedParticipant();

private:
    Ui::DialogCreateParticipant *ui;
};

#endif // DIALOGCREATEPARTICIPANT_H
