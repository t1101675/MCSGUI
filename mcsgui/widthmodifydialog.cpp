#include "widthmodifydialog.h"
#include <iostream>
#include <QMessageBox>

WidthModifyDialog::WidthModifyDialog(QWidget *parent) : QDialog(parent), ui(new Ui::WidthModifyDialog)
{
    ui->setupUi(this);
    spinBox = ui->widthSpinBox;
    slider = ui->widthSlider;
    okButton = ui->okButton;
    cancelButton = ui->cancelButton;
    connect(okButton, SIGNAL(clicked()), this, SLOT(endDialog()));
}

WidthModifyDialog::~WidthModifyDialog() {

}

bool WidthModifyDialog::okToContinue() {
    if (spinBox->value() > maxW) {
        QMessageBox::critical(this, tr("Width Modify"), tr("The width can't be so large."), QMessageBox::Ok, QMessageBox::NoButton);
        return false;
    } else {
        return true;
    }
}

void WidthModifyDialog::endDialog() {
    if (okToContinue()) {
        accept();
    }
}
