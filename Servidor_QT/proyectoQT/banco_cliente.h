#ifndef BANCO_CLIENTE_H
#define BANCO_CLIENTE_H

#include <QDialog>
#include "TCP_IP.h"

namespace Ui {
class Banco_cliente;
}

class Banco_cliente : public QDialog
{
    Q_OBJECT

public:
    explicit Banco_cliente(QWidget *parent = 0);
    void Generar_recibo();
    ~Banco_cliente();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Banco_cliente *ui;
    conexion cliente;
    bool conectado;
};

#endif // BANCO_CLIENTE_H
