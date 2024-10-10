/********************************************************************************
** Form generated from reading UI file 'setcalculator.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCALCULATOR_H
#define UI_SETCALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetCalculator
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SetCalculator)
    {
        if (SetCalculator->objectName().isEmpty())
            SetCalculator->setObjectName("SetCalculator");
        SetCalculator->resize(800, 600);
        centralwidget = new QWidget(SetCalculator);
        centralwidget->setObjectName("centralwidget");
        SetCalculator->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SetCalculator);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        SetCalculator->setMenuBar(menubar);
        statusbar = new QStatusBar(SetCalculator);
        statusbar->setObjectName("statusbar");
        SetCalculator->setStatusBar(statusbar);

        retranslateUi(SetCalculator);

        QMetaObject::connectSlotsByName(SetCalculator);
    } // setupUi

    void retranslateUi(QMainWindow *SetCalculator)
    {
        SetCalculator->setWindowTitle(QCoreApplication::translate("SetCalculator", "SetCalculator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetCalculator: public Ui_SetCalculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCALCULATOR_H
