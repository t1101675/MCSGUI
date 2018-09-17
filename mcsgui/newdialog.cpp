#include "newdialog.h"
#include "ui_newdialog.h"
#include <iostream>
#include <QRegExpValidator>
#include <QPushButton>

NewDialog::NewDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewDialog){
    ui->setupUi(this);

    rowEdit = ui->rowEdit;
    inputPipeEdit[0] = ui->inputPipeEdit1;
    inputPipeEdit[1] = ui->inputPipeEdit2;
    outputPipeEdit[0] = ui->outputPipeEdit1;
    outputPipeEdit[1] = ui->outputPipeEdit2;
    outputPipeEdit[2] = ui->outputPipeEdit3;

    okButton = ui->okButton;
    resetButton = ui->resetButton;
    cancelBUtton = ui->cancelButton;

    QRegExp rowRegExp("[5-8]");
    rowEdit->setValidator(new QRegExpValidator(rowRegExp, this));

    QRegExp inputRegExp[2];
    for (int i = 0; i < INPUTPIPENUM; i++) {
        inputRegExp[i].setPattern("[1-8]");
        inputPipeEdit[i]->setValidator(new QRegExpValidator(inputRegExp[i], this));
        connect(inputPipeEdit[i], SIGNAL(textChanged(const QString&)), this, SLOT(enableOK()));
    }
    QRegExp outputRegExp[3];
    for (int i = 0; i < OUTPUTPIPENUM; i++) {
        outputRegExp[i].setPattern(("[1-8]"));
        outputPipeEdit[i]->setValidator(new QRegExpValidator(outputRegExp[i], this));
        connect(outputPipeEdit[i], SIGNAL(textChanged(const QString&)), this, SLOT(enableOK()));
    }
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(cancelBUtton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(rowEdit, SIGNAL(textChanged(const QString&)), this, SLOT(enableOK()));

    layout()->setSizeConstraint(QLayout::SetFixedSize);
    enableOK();
    initial();
}

bool NewDialog::pipeDataValid() {
    if (!rowEdit->hasAcceptableInput()) return false;
    for (int i = 0; i < INPUTPIPENUM; i++) if (!inputPipeEdit[i]->hasAcceptableInput()) return false;
    for (int i = 0; i < OUTPUTPIPENUM; i++) if (!outputPipeEdit[i]->hasAcceptableInput()) return false;

    int row = rowEdit->text().toInt();
    for (int i = 0; i < INPUTPIPENUM; i++) if (inputPipeEdit[i]->text().toInt() > row) return false;
    for (int i = 0; i < OUTPUTPIPENUM; i++) if (outputPipeEdit[i]->text().toInt() > row) return false;

    if (inputPipeEdit[0]->text() == inputPipeEdit[1]->text()) return false;
    if ( (outputPipeEdit[0]->text() == outputPipeEdit[1]->text()) ||
         (outputPipeEdit[1]->text() == outputPipeEdit[2]->text()) ||
         (outputPipeEdit[0]->text() == outputPipeEdit[2]->text()) ) return false;

    return true;
}

void NewDialog::initial() {
}

void NewDialog::enableOK() {
    okButton->setEnabled(pipeDataValid());
}

void NewDialog::reset() {
    QPushButton button;
    button.setGeometry(1, 1, 1, 1);
}

NewDialog::~NewDialog() {
    delete ui;
}
