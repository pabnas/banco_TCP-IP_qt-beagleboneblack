/********************************************************************************
** Form generated from reading UI file 'informacion_server.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMACION_SERVER_H
#define UI_INFORMACION_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Informacion_server
{
public:
    QLabel *label;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *Informacion_server)
    {
        if (Informacion_server->objectName().isEmpty())
            Informacion_server->setObjectName(QStringLiteral("Informacion_server"));
        Informacion_server->resize(581, 570);
        label = new QLabel(Informacion_server);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 67, 17));
        checkBox = new QCheckBox(Informacion_server);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(20, 30, 92, 23));
        checkBox_2 = new QCheckBox(Informacion_server);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(20, 60, 92, 23));
        checkBox_3 = new QCheckBox(Informacion_server);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(20, 90, 92, 23));
        lineEdit = new QLineEdit(Informacion_server);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(130, 30, 211, 25));
        lineEdit->setMaxLength(100);
        lineEdit_2 = new QLineEdit(Informacion_server);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(130, 60, 141, 25));
        lineEdit_2->setMaxLength(10);
        pushButton = new QPushButton(Informacion_server);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 30, 89, 25));
        plainTextEdit = new QPlainTextEdit(Informacion_server);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 120, 501, 411));

        retranslateUi(Informacion_server);

        QMetaObject::connectSlotsByName(Informacion_server);
    } // setupUi

    void retranslateUi(QDialog *Informacion_server)
    {
        Informacion_server->setWindowTitle(QApplication::translate("Informacion_server", "Dialog", Q_NULLPTR));
        label->setText(QString());
        checkBox->setText(QApplication::translate("Informacion_server", "Usuario", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("Informacion_server", "ID", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("Informacion_server", "Ver Todo", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Informacion_server", "Buscar", Q_NULLPTR));
        plainTextEdit->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class Informacion_server: public Ui_Informacion_server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMACION_SERVER_H
