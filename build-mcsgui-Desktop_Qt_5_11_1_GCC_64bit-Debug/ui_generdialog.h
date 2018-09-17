/********************************************************************************
** Form generated from reading UI file 'generdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERDIALOG_H
#define UI_GENERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_generdialog
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *o1;
    QLabel *label_2;
    QLineEdit *o2;
    QLabel *label_3;
    QLineEdit *o3;
    QPushButton *OKButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *generdialog)
    {
        if (generdialog->objectName().isEmpty())
            generdialog->setObjectName(QStringLiteral("generdialog"));
        generdialog->resize(286, 214);
        widget = new QWidget(generdialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 20, 247, 167));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        o1 = new QLineEdit(widget);
        o1->setObjectName(QStringLiteral("o1"));

        gridLayout->addWidget(o1, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        o2 = new QLineEdit(widget);
        o2->setObjectName(QStringLiteral("o2"));

        gridLayout->addWidget(o2, 1, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        o3 = new QLineEdit(widget);
        o3->setObjectName(QStringLiteral("o3"));

        gridLayout->addWidget(o3, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 2);

        OKButton = new QPushButton(widget);
        OKButton->setObjectName(QStringLiteral("OKButton"));
        OKButton->setEnabled(true);

        gridLayout_3->addWidget(OKButton, 1, 0, 1, 1);

        CancelButton = new QPushButton(widget);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout_3->addWidget(CancelButton, 1, 1, 1, 1);


        retranslateUi(generdialog);
        QObject::connect(OKButton, SIGNAL(clicked()), generdialog, SLOT(accept()));
        QObject::connect(CancelButton, SIGNAL(clicked()), generdialog, SLOT(reject()));

        OKButton->setDefault(true);


        QMetaObject::connectSlotsByName(generdialog);
    } // setupUi

    void retranslateUi(QDialog *generdialog)
    {
        generdialog->setWindowTitle(QApplication::translate("generdialog", "Dialog", nullptr));
        label_4->setText(QApplication::translate("generdialog", "Enter the aim speed:", nullptr));
        label->setText(QApplication::translate("generdialog", "Output1:", nullptr));
        o1->setText(QApplication::translate("generdialog", "200", nullptr));
        label_2->setText(QApplication::translate("generdialog", "Output2:", nullptr));
        o2->setText(QApplication::translate("generdialog", "100", nullptr));
        label_3->setText(QApplication::translate("generdialog", "Output3:", nullptr));
        o3->setText(QApplication::translate("generdialog", "100", nullptr));
        OKButton->setText(QApplication::translate("generdialog", "OK", nullptr));
        CancelButton->setText(QApplication::translate("generdialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class generdialog: public Ui_generdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERDIALOG_H
