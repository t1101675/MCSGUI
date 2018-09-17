#ifndef WIDTHMODIFYDIALOG_H
#define WIDTHMODIFYDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include "ui_widthmodify.h"

namespace Ui{
    class WidthModifyDialog;
}

class WidthModifyDialog : public QDialog {
    Q_OBJECT

public:
    WidthModifyDialog(QWidget *parent = 0);
    ~WidthModifyDialog();

    void setMaxWidth(int w) { maxW = w; }

    QSpinBox *spinBox;
    QSlider *slider;
    QPushButton *okButton;
    QPushButton *cancelButton;

private:
    bool okToContinue();

    int maxW;
    Ui::WidthModifyDialog *ui;

public slots:
    void endDialog();

};

#endif // WIDTHMODIFYDIALOG_H
