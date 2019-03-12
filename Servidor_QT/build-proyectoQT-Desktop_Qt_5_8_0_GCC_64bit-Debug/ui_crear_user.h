/********************************************************************************
** Form generated from reading UI file 'crear_user.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREAR_USER_H
#define UI_CREAR_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Crear_user
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;

    void setupUi(QDialog *Crear_user)
    {
        if (Crear_user->objectName().isEmpty())
            Crear_user->setObjectName(QStringLiteral("Crear_user"));
        Crear_user->resize(549, 380);
        label = new QLabel(Crear_user);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 30, 67, 17));
        label_2 = new QLabel(Crear_user);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 80, 67, 17));
        label_3 = new QLabel(Crear_user);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(410, 30, 67, 17));
        textEdit = new QTextEdit(Crear_user);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(110, 30, 261, 31));
        textEdit_2 = new QTextEdit(Crear_user);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(110, 80, 261, 31));
        spinBox = new QSpinBox(Crear_user);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(480, 30, 48, 26));
        spinBox->setReadOnly(false);
        spinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox->setMinimum(12);
        pushButton = new QPushButton(Crear_user);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(390, 320, 89, 25));
        label_4 = new QLabel(Crear_user);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 160, 67, 17));
        label_5 = new QLabel(Crear_user);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 210, 67, 17));
        label_6 = new QLabel(Crear_user);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 270, 111, 17));
        checkBox = new QCheckBox(Crear_user);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(160, 260, 92, 23));
        checkBox_2 = new QCheckBox(Crear_user);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(160, 290, 92, 23));
        checkBox_2->setChecked(false);
        lineEdit = new QLineEdit(Crear_user);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 210, 181, 31));
        lineEdit->setMaxLength(10);
        lineEdit->setEchoMode(QLineEdit::Password);
        lineEdit_2 = new QLineEdit(Crear_user);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(110, 160, 181, 31));
        lineEdit_2->setMaxLength(10);
        lineEdit_2->setEchoMode(QLineEdit::Normal);

        retranslateUi(Crear_user);

        QMetaObject::connectSlotsByName(Crear_user);
    } // setupUi

    void retranslateUi(QDialog *Crear_user)
    {
        Crear_user->setWindowTitle(QApplication::translate("Crear_user", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("Crear_user", "Nombre:", Q_NULLPTR));
        label_2->setText(QApplication::translate("Crear_user", "Telefono:", Q_NULLPTR));
        label_3->setText(QApplication::translate("Crear_user", "Edad:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Crear_user", "Crear", Q_NULLPTR));
        label_4->setText(QApplication::translate("Crear_user", "Cuenta:", Q_NULLPTR));
        label_5->setText(QApplication::translate("Crear_user", "Clave:", Q_NULLPTR));
        label_6->setText(QApplication::translate("Crear_user", "Tipo de cuenta", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Crear_user", "Ahorros", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("Crear_user", "Corriente", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Crear_user: public Ui_Crear_user {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREAR_USER_H
