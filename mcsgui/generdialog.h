#ifndef GENERDIALOG_H
#define GENERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDialog>

namespace Ui {
class generdialog;
}

class generdialog : public QDialog
{
    Q_OBJECT

public:
    explicit generdialog(QWidget *parent = 0);
    ~generdialog();

    QLineEdit *outEdit[3];
    QPushButton *OKButton;
    QPushButton *cancelButton;

private:
    Ui::generdialog *ui;

public slots:
    void enableOK();
};

#endif // GENERDIALOG_H
