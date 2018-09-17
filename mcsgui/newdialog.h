#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include "pipenum.h"
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class NewDialog;
}

class NewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDialog(QWidget *parent = 0);
    ~NewDialog();

    QLineEdit *rowEdit;
    QLineEdit *inputPipeEdit[INPUTPIPENUM];
    QLineEdit *outputPipeEdit[OUTPUTPIPENUM];
    QPushButton *okButton;
    QPushButton *resetButton;
    QPushButton *cancelBUtton;


public slots:
    void reset();
    void enableOK();

private:
    void initial();
    bool pipeDataValid();

    Ui::NewDialog *ui;
};


#endif // NEWDIALOG_H
