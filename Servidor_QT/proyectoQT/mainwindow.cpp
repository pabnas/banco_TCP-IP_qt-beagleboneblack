#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crear_user.h"
#include "banco_cliente.h"
#include "informacion_server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_released()
{
    Crear_user ventana1;
    ventana1.setModal(true);
    this->hide();
    ventana1.exec();
    this->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    Informacion_server inf;
    inf.setModal(true);
    this->hide();
    inf.exec();
    this->show();
}

void MainWindow::on_pushButton_3_clicked()//cliente
{
    Banco_cliente banco;
    banco.setModal(true);
    this->hide();
    banco.exec();
    this->show();
}
