/********************************************************************************
** Form generated from reading UI file 'filosfia.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILOSFIA_H
#define UI_FILOSFIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lobby
{
public:

    void setupUi(QWidget *Lobby)
    {
        if (Lobby->objectName().isEmpty())
            Lobby->setObjectName("Lobby");
        Lobby->resize(1007, 600);
        Lobby->setAutoFillBackground(false);
        Lobby->setStyleSheet(QString::fromUtf8("background-image: url(:/Fondos/classroom.jpg);\n"
"background-repeat: no-repeat;\n"
"background-position: center;\n"
"background-origin: content;\n"
"background-size: contain;\n"
""));

        retranslateUi(Lobby);

        QMetaObject::connectSlotsByName(Lobby);
    } // setupUi

    void retranslateUi(QWidget *Lobby)
    {
        Lobby->setWindowTitle(QCoreApplication::translate("Lobby", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lobby: public Ui_Lobby {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILOSFIA_H
