/********************************************************************************
** Form generated from reading UI file 'MyServer.ui'
**
** Created by: Qt User Interface Compiler version 6.0.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSERVER_H
#define UI_MYSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyServer
{
public:

    void setupUi(QWidget *MyServer)
    {
        if (MyServer->objectName().isEmpty())
            MyServer->setObjectName(QString::fromUtf8("MyServer"));
        MyServer->resize(800, 600);

        retranslateUi(MyServer);

        QMetaObject::connectSlotsByName(MyServer);
    } // setupUi

    void retranslateUi(QWidget *MyServer)
    {
        MyServer->setWindowTitle(QCoreApplication::translate("MyServer", "MyServer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyServer: public Ui_MyServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSERVER_H
