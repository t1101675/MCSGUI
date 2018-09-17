/********************************************************************************
** Form generated from reading UI file 'newdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWDIALOG_H
#define UI_NEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewDialog
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *resetButton;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *rowEdit;
    QFrame *line;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLineEdit *inputPipeEdit1;
    QLabel *label_4;
    QLineEdit *inputPipeEdit2;
    QFrame *line_2;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *label_11;
    QLineEdit *outputPipeEdit1;
    QLabel *label_10;
    QLineEdit *outputPipeEdit2;
    QLabel *label_9;
    QLineEdit *outputPipeEdit3;

    void setupUi(QDialog *NewDialog)
    {
        if (NewDialog->objectName().isEmpty())
            NewDialog->setObjectName(QStringLiteral("NewDialog"));
        NewDialog->resize(408, 355);
        gridLayout_3 = new QGridLayout(NewDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);

        resetButton = new QPushButton(NewDialog);
        resetButton->setObjectName(QStringLiteral("resetButton"));

        gridLayout->addWidget(resetButton, 1, 1, 1, 1);

        cancelButton = new QPushButton(NewDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout->addWidget(cancelButton, 2, 1, 1, 1);

        okButton = new QPushButton(NewDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setEnabled(true);

        gridLayout->addWidget(okButton, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(NewDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        rowEdit = new QLineEdit(NewDialog);
        rowEdit->setObjectName(QStringLiteral("rowEdit"));

        horizontalLayout->addWidget(rowEdit);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(NewDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        groupBox = new QGroupBox(NewDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        inputPipeEdit1 = new QLineEdit(groupBox);
        inputPipeEdit1->setObjectName(QStringLiteral("inputPipeEdit1"));

        gridLayout_2->addWidget(inputPipeEdit1, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        inputPipeEdit2 = new QLineEdit(groupBox);
        inputPipeEdit2->setObjectName(QStringLiteral("inputPipeEdit2"));

        gridLayout_2->addWidget(inputPipeEdit2, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        line_2 = new QFrame(NewDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        groupBox_2 = new QGroupBox(NewDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        outputPipeEdit1 = new QLineEdit(groupBox_2);
        outputPipeEdit1->setObjectName(QStringLiteral("outputPipeEdit1"));

        formLayout->setWidget(0, QFormLayout::FieldRole, outputPipeEdit1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_10);

        outputPipeEdit2 = new QLineEdit(groupBox_2);
        outputPipeEdit2->setObjectName(QStringLiteral("outputPipeEdit2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, outputPipeEdit2);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_9);

        outputPipeEdit3 = new QLineEdit(groupBox_2);
        outputPipeEdit3->setObjectName(QStringLiteral("outputPipeEdit3"));

        formLayout->setWidget(2, QFormLayout::FieldRole, outputPipeEdit3);


        verticalLayout->addWidget(groupBox_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 4, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(NewDialog);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(NewDialog);
    } // setupUi

    void retranslateUi(QDialog *NewDialog)
    {
        NewDialog->setWindowTitle(QApplication::translate("NewDialog", "New Graph", nullptr));
        resetButton->setText(QApplication::translate("NewDialog", "Reset", nullptr));
        cancelButton->setText(QApplication::translate("NewDialog", "Cancel", nullptr));
        okButton->setText(QApplication::translate("NewDialog", "OK", nullptr));
        label->setText(QApplication::translate("NewDialog", "Rows/Columns:", nullptr));
        rowEdit->setText(QApplication::translate("NewDialog", "5", nullptr));
        rowEdit->setPlaceholderText(QApplication::translate("NewDialog", "Between 5 to 8", nullptr));
        groupBox->setTitle(QApplication::translate("NewDialog", "Input Pipes:", nullptr));
        label_3->setText(QApplication::translate("NewDialog", "Pipe1:", nullptr));
        inputPipeEdit1->setText(QApplication::translate("NewDialog", "1", nullptr));
        inputPipeEdit1->setPlaceholderText(QApplication::translate("NewDialog", "Input pipe's column", nullptr));
        label_4->setText(QApplication::translate("NewDialog", "Pipe2:", nullptr));
        inputPipeEdit2->setText(QApplication::translate("NewDialog", "2", nullptr));
        inputPipeEdit2->setPlaceholderText(QApplication::translate("NewDialog", "Input pipe's column", nullptr));
        groupBox_2->setTitle(QApplication::translate("NewDialog", "Output Pipes:", nullptr));
        label_11->setText(QApplication::translate("NewDialog", "Pipe1:", nullptr));
        outputPipeEdit1->setText(QApplication::translate("NewDialog", "1", nullptr));
        outputPipeEdit1->setPlaceholderText(QApplication::translate("NewDialog", "Output pipe's column", nullptr));
        label_10->setText(QApplication::translate("NewDialog", "Pipe2:", nullptr));
        outputPipeEdit2->setText(QApplication::translate("NewDialog", "2", nullptr));
        outputPipeEdit2->setPlaceholderText(QApplication::translate("NewDialog", "Output pipe's column", nullptr));
        label_9->setText(QApplication::translate("NewDialog", "Pipe3:", nullptr));
        outputPipeEdit3->setText(QApplication::translate("NewDialog", "3", nullptr));
        outputPipeEdit3->setPlaceholderText(QApplication::translate("NewDialog", "Output pipe's column", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewDialog: public Ui_NewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWDIALOG_H
