#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "associationmotor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void AddParticipant_Click();
    void ResetAssociations_Click();
    void ComputeAssociations_Click();
    void DeleteParticipant_Click();

private:
    Ui::MainWindow *ui;
    AssociationMotor motor;
};

#endif // MAINWINDOW_H
