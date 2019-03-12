#ifndef CREAR_USER_H
#define CREAR_USER_H

#include <QDialog>

#include "qmessagebox.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "TCP_IP.h"

namespace Ui {
class Crear_user;
}

class Crear_user : public QDialog
{
    Q_OBJECT

public:
    explicit Crear_user(QWidget *parent = 0);
    bool crear_usuario();
    ~Crear_user();

private slots:
    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Crear_user *ui;
    conexion cliente;
};

#endif // CREAR_USER_H
