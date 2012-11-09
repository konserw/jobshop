/********************************************************************************
** Form generated from reading UI file 'marszruta.ui'
**
** Created: Tue Oct 16 19:08:57 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARSZRUTA_H
#define UI_MARSZRUTA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_marszruta
{
public:
    QFormLayout *formLayout;
    QLabel *label_machine;
    QLabel *label_time;
    QComboBox *machine;
    QSpinBox *time;

    void setupUi(QWidget *marszruta)
    {
        if (marszruta->objectName().isEmpty())
            marszruta->setObjectName(QString::fromUtf8("marszruta"));
        marszruta->resize(171, 70);
        formLayout = new QFormLayout(marszruta);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_machine = new QLabel(marszruta);
        label_machine->setObjectName(QString::fromUtf8("label_machine"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_machine);

        label_time = new QLabel(marszruta);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label_time);

        machine = new QComboBox(marszruta);
        machine->setObjectName(QString::fromUtf8("machine"));

        formLayout->setWidget(1, QFormLayout::LabelRole, machine);

        time = new QSpinBox(marszruta);
        time->setObjectName(QString::fromUtf8("time"));

        formLayout->setWidget(1, QFormLayout::FieldRole, time);


        retranslateUi(marszruta);

        QMetaObject::connectSlotsByName(marszruta);
    } // setupUi

    void retranslateUi(QWidget *marszruta)
    {
        marszruta->setWindowTitle(QApplication::translate("marszruta", "Form", 0, QApplication::UnicodeUTF8));
        label_machine->setText(QApplication::translate("marszruta", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_time->setText(QApplication::translate("marszruta", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class marszruta: public Ui_marszruta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARSZRUTA_H
