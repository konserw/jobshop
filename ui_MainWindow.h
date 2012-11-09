/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Tue Nov 6 10:34:14 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_machines;
    QSpinBox *machines;
    QLabel *label_rout;
    QSpinBox *rout;
    QPushButton *more;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QLabel *labelDane;
    QPushButton *importButton;
    QPushButton *exportButton;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_method;
    QComboBox *method;
    QPushButton *solve;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(928, 433);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_machines = new QLabel(centralWidget);
        label_machines->setObjectName(QString::fromUtf8("label_machines"));

        horizontalLayout->addWidget(label_machines);

        machines = new QSpinBox(centralWidget);
        machines->setObjectName(QString::fromUtf8("machines"));

        horizontalLayout->addWidget(machines);

        label_rout = new QLabel(centralWidget);
        label_rout->setObjectName(QString::fromUtf8("label_rout"));

        horizontalLayout->addWidget(label_rout);

        rout = new QSpinBox(centralWidget);
        rout->setObjectName(QString::fromUtf8("rout"));

        horizontalLayout->addWidget(rout);

        more = new QPushButton(centralWidget);
        more->setObjectName(QString::fromUtf8("more"));

        horizontalLayout->addWidget(more);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        labelDane = new QLabel(centralWidget);
        labelDane->setObjectName(QString::fromUtf8("labelDane"));

        horizontalLayout->addWidget(labelDane);

        importButton = new QPushButton(centralWidget);
        importButton->setObjectName(QString::fromUtf8("importButton"));

        horizontalLayout->addWidget(importButton);

        exportButton = new QPushButton(centralWidget);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));

        horizontalLayout->addWidget(exportButton);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_method = new QLabel(centralWidget);
        label_method->setObjectName(QString::fromUtf8("label_method"));

        horizontalLayout->addWidget(label_method);

        method = new QComboBox(centralWidget);
        method->setObjectName(QString::fromUtf8("method"));

        horizontalLayout->addWidget(method);

        solve = new QPushButton(centralWidget);
        solve->setObjectName(QString::fromUtf8("solve"));

        horizontalLayout->addWidget(solve);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_machines->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_rout->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        more->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
        labelDane->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        importButton->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
        exportButton->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
        label_method->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        solve->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
