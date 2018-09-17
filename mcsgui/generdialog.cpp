#include "generdialog.h"
#include "ui_generdialog.h"
#include <iostream>

generdialog::generdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generdialog)
{
    ui->setupUi(this);
    outEdit[0] = ui->o1;
    outEdit[1] = ui->o2;
    outEdit[2] = ui->o3;
    OKButton = ui->OKButton;
    cancelButton = ui->CancelButton;
    for (int i = 0; i < 3; i++) {
        connect(outEdit[i], SIGNAL(textChanged(QString)), this, SLOT(enableOK()));
    }
}

void generdialog::enableOK() {
    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += outEdit[i]->text().toDouble();
    }
    if (sum == 400) OKButton->setEnabled(true);
}

generdialog::~generdialog()
{
    delete ui;
}
