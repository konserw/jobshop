/********************************************************************************
** Form generated from reading UI file 'wykres.ui'
**
** Created: Tue Oct 16 19:08:57 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WYKRES_H
#define UI_WYKRES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_wykres
{
public:
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_alfa;
    QSpinBox *alfa;
    QHBoxLayout *horizontalLayout;
    QLabel *label_beta;
    QSpinBox *beta;
    QLabel *label;

    void setupUi(QDialog *wykres)
    {
        if (wykres->objectName().isEmpty())
            wykres->setObjectName(QString::fromUtf8("wykres"));
        wykres->setWindowModality(Qt::ApplicationModal);
        wykres->resize(538, 513);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wykres->sizePolicy().hasHeightForWidth());
        wykres->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(wykres);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        graphicsView = new QGraphicsView(wykres);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout_2->addWidget(graphicsView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tableWidget = new QTableWidget(wykres);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout_3->addWidget(tableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        label_alfa = new QLabel(wykres);
        label_alfa->setObjectName(QString::fromUtf8("label_alfa"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_alfa->sizePolicy().hasHeightForWidth());
        label_alfa->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_alfa);

        alfa = new QSpinBox(wykres);
        alfa->setObjectName(QString::fromUtf8("alfa"));
        alfa->setValue(1);

        horizontalLayout_2->addWidget(alfa);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        label_beta = new QLabel(wykres);
        label_beta->setObjectName(QString::fromUtf8("label_beta"));
        sizePolicy1.setHeightForWidth(label_beta->sizePolicy().hasHeightForWidth());
        label_beta->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_beta);

        beta = new QSpinBox(wykres);
        beta->setObjectName(QString::fromUtf8("beta"));
        beta->setValue(1);

        horizontalLayout->addWidget(beta);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(wykres);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(wykres);

        QMetaObject::connectSlotsByName(wykres);
    } // setupUi

    void retranslateUi(QDialog *wykres)
    {
        wykres->setWindowTitle(QApplication::translate("wykres", "Dialog", 0, QApplication::UnicodeUTF8));
        label_alfa->setText(QApplication::translate("wykres", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_beta->setText(QApplication::translate("wykres", "TextLabel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("wykres", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wykres: public Ui_wykres {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WYKRES_H
