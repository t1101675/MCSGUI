/********************************************************************************
** Form generated from reading UI file 'widthmodify.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDTHMODIFY_H
#define UI_WIDTHMODIFY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidthModifyDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QSlider *widthSlider;
    QSpinBox *widthSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelButton;

    void setupUi(QDialog *WidthModifyDialog)
    {
        if (WidthModifyDialog->objectName().isEmpty())
            WidthModifyDialog->setObjectName(QStringLiteral("WidthModifyDialog"));
        WidthModifyDialog->resize(285, 154);
        layoutWidget = new QWidget(WidthModifyDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 218, 102));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widthSlider = new QSlider(layoutWidget);
        widthSlider->setObjectName(QStringLiteral("widthSlider"));
        widthSlider->setMinimum(20);
        widthSlider->setMaximum(3400);
        widthSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(widthSlider);

        widthSpinBox = new QSpinBox(layoutWidget);
        widthSpinBox->setObjectName(QStringLiteral("widthSpinBox"));
        widthSpinBox->setMinimum(20);
        widthSpinBox->setMaximum(3400);

        horizontalLayout->addWidget(widthSpinBox);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout_3->addWidget(okButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(WidthModifyDialog);
        QObject::connect(widthSlider, SIGNAL(valueChanged(int)), widthSpinBox, SLOT(setValue(int)));
        QObject::connect(widthSpinBox, SIGNAL(valueChanged(int)), widthSlider, SLOT(setValue(int)));
        QObject::connect(cancelButton, SIGNAL(clicked()), WidthModifyDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(WidthModifyDialog);
    } // setupUi

    void retranslateUi(QDialog *WidthModifyDialog)
    {
        WidthModifyDialog->setWindowTitle(QApplication::translate("WidthModifyDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("WidthModifyDialog", "Edit Width:", nullptr));
        okButton->setText(QApplication::translate("WidthModifyDialog", "OK", nullptr));
        cancelButton->setText(QApplication::translate("WidthModifyDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidthModifyDialog: public Ui_WidthModifyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDTHMODIFY_H
