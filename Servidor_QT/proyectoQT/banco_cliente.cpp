#include "banco_cliente.h"
#include "ui_banco_cliente.h"

#include "qmessagebox.h"
#include <QTextStream>
#include <QDate>

Banco_cliente::Banco_cliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Banco_cliente)
{
    ui->setupUi(this);
    QRegExpValidator* rxv = new QRegExpValidator(QRegExp("\\d*"), this); // only pos
    ui->lineEdit->setValidator(rxv);
    ui->lineEdit_2->setValidator(rxv);
    ui->lineEdit_3->setValidator(rxv);
    ui->lineEdit_4->setValidator(rxv);
    ui->lineEdit_5->setValidator(rxv);
    ui->lineEdit_6->setValidator(rxv);
    ui->lineEdit_7->setValidator(rxv);

    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();

    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();

    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    conectado = false;
}

Banco_cliente::~Banco_cliente()
{
    if(conectado)
    {
        cliente.conectar();
        cliente.enviar("desconectar");
        cliente.enviar(ui->lineEdit->text().toUtf8().constData());
        cliente.desconectar();
    }
    delete ui;
}

void Banco_cliente::on_pushButton_clicked()
{
    if((ui->lineEdit->text().isEmpty()) | (ui->lineEdit_2->text().isEmpty()))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Hay campos vacios");
        msgBox.exec();
    }
    else
    {
        cliente.conectar();
        cliente.enviar("verificar");
        cliente.enviar(ui->lineEdit->text().toUtf8().constData());
        string resp = cliente.recibir();
        cliente.desconectar();
        if(!resp.compare("no"))
        {
            QMessageBox msgBox;
            msgBox.setText("Error");
            msgBox.setInformativeText("la cuenta no existe");
            msgBox.exec();
        }
        else
        {
            cliente.conectar();
            cliente.enviar("login");
            cliente.enviar(ui->lineEdit->text().toUtf8().constData());
            cliente.enviar(ui->lineEdit_2->text().toUtf8().constData());
            string resp_login = cliente.recibir();
            cliente.desconectar();
            if(!resp_login.compare("no"))
            {
                QMessageBox msgBox;
                msgBox.setText("Error");
                msgBox.setInformativeText("clave invalida");
                msgBox.exec();
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("Conectado");
                conectado = true;
                msgBox.exec();
                ui->lineEdit->setEnabled(false);
                ui->lineEdit_2->setEnabled(false);
                ui->pushButton->setEnabled(false);


                ui->pushButton_2->show();
                ui->pushButton_3->show();
                ui->pushButton_4->show();
                ui->pushButton_5->show();
                ui->pushButton_6->show();
                ui->pushButton_7->show();

                ui->lineEdit_3->show();
                ui->lineEdit_4->show();
                ui->lineEdit_5->show();
                ui->lineEdit_6->show();
                ui->lineEdit_7->show();

                ui->label_3->show();
                ui->label_4->show();
                ui->label_5->show();
                ui->label_6->show();
                ui->label_7->show();
                ui->label_8->show();

                cliente.conectar();
                cliente.enviar("obtener");
                cliente.enviar(ui->lineEdit->text().toUtf8().constData());
                string nombre = cliente.recibir();
                cliente.recibir();
                cliente.desconectar();
                ui->label_6->setText(nombre.c_str());
            }
        }
    }
}

void Banco_cliente::on_pushButton_6_clicked()
{
    cliente.conectar();
    cliente.enviar("desconectar");
    cliente.enviar(ui->lineEdit->text().toUtf8().constData());
    cliente.desconectar();
    conectado = false;

    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->pushButton->setEnabled(true);


    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();

    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();

    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
}

void Banco_cliente::on_pushButton_3_clicked()
{
    if((ui->lineEdit_3->text().isEmpty()) | (ui->lineEdit_3->text().toInt()< 0))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("error con el monto seleccionado");
        msgBox.exec();
    }
    else
    {
        cliente.conectar();
        cliente.enviar("consignar");
        cliente.enviar(ui->lineEdit->text().toUtf8().constData());
        cliente.enviar(ui->lineEdit_3->text().toUtf8().constData());
        cliente.desconectar();
        Generar_recibo();
    }
}

void Banco_cliente::on_pushButton_2_clicked()
{
    cliente.conectar();
    cliente.enviar("obtener");
    cliente.enviar(ui->lineEdit->text().toUtf8().constData());
    cliente.recibir();
    string saldo = "$ " + cliente.recibir();
    cliente.desconectar();
    QMessageBox msgBox;
    msgBox.setText("Su saldo actual es de:");
    msgBox.setInformativeText(saldo.c_str());
    msgBox.exec();
    Generar_recibo();
}

void Banco_cliente::on_pushButton_4_clicked()
{
    if((ui->lineEdit_4->text().isEmpty()) | (ui->lineEdit_4->text().toInt()< 0))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("error con el monto seleccionado");
        msgBox.exec();
    }
    else
    {
        long int retiro = ui->lineEdit_4->text().toInt() * -1;
        cliente.conectar();
        cliente.enviar("obtener");
        cliente.enviar(ui->lineEdit->text().toUtf8().constData());
        cliente.recibir();
        string saldo = cliente.recibir();
        long int msaldo = atoi(saldo.c_str());
        cliente.desconectar();

        if(msaldo < (retiro*-1))
        {
            QMessageBox msgBox;
            msgBox.setText("Error");
            msgBox.setInformativeText("El retiro excede el saldo disponible");
            msgBox.exec();
        }
        else
        {
            QString sretiro = QString::number(retiro);

            cliente.conectar();
            cliente.enviar("consignar");
            cliente.enviar(ui->lineEdit->text().toUtf8().constData());
            cliente.enviar(sretiro.toUtf8().data());
            cliente.desconectar();
            Generar_recibo();
        }
    }
}

void Banco_cliente::on_pushButton_5_clicked()
{
    if((ui->lineEdit_5->text().isEmpty())  | (ui->lineEdit_6->text().isEmpty()))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("error con el monto seleccionado");
        msgBox.exec();
    }
    else
    {
        cliente.conectar();
        cliente.enviar("verificar");
        cliente.enviar(ui->lineEdit_5->text().toUtf8().constData());
        string resp = cliente.recibir();
        cliente.desconectar();
        if(!resp.compare("no"))
        {
            QMessageBox msgBox;
            msgBox.setText("Error");
            msgBox.setInformativeText("la cuenta no existe");
            msgBox.exec();
        }
        else
        {
            long int retiro = ui->lineEdit_6->text().toInt() * -1;
            cliente.conectar();
            cliente.enviar("obtener");
            cliente.enviar(ui->lineEdit->text().toUtf8().constData());
            cliente.recibir();
            string saldo = cliente.recibir();
            long int msaldo = atoi(saldo.c_str());
            cliente.desconectar();

            if(msaldo < (retiro*-1))
            {
                QMessageBox msgBox;
                msgBox.setText("Error");
                msgBox.setInformativeText("El retiro excede el saldo disponible");
                msgBox.exec();
            }
            else
            {
                //retirar de la cuenta 1
                QString sretiro = QString::number(retiro);

                cliente.conectar();
                cliente.enviar("consignar");
                cliente.enviar(ui->lineEdit->text().toUtf8().constData());
                cliente.enviar(sretiro.toUtf8().data());
                cliente.desconectar();

                //consignar a la cuenta 2
                sretiro = QString::number(retiro*-1);

                cliente.conectar();
                cliente.enviar("consignar");
                cliente.enviar(ui->lineEdit_5->text().toUtf8().constData());
                cliente.enviar(sretiro.toUtf8().data());
                cliente.desconectar();
                Generar_recibo();
            }
        }
    }
}

void Banco_cliente::Generar_recibo()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Recibo", "Deseea generar un recibo",QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
      {
          FILE * pFile;
          string ruta = "../../Recibo.txt";
          pFile = fopen (ruta.c_str(),"w");
          QDate cd = QDate::currentDate();
          QTime ct = QTime::currentTime();

          fprintf(pFile,"\n");
          fprintf(pFile,"       --------------------------------------------------------\n");
          fprintf(pFile,"       --------------------------------------------------------\n");
          fprintf(pFile,"         _    _  _____ _______       ____          _   _ _  __\n");
          fprintf(pFile,"        | |  | |/ ____|__   __|/\\   |  _ \\   /\\   | \\ | | |/ /\n");
          fprintf(pFile,"        | |  | | (___    | |  /  \\  | |_) | /  \\  |  \\| | ' / \n");
          fprintf(pFile,"        | |  | |\\___ \\   | | / /\\ \\ |  _ < / /\\ \\ | . ` |  <  \n");
          fprintf(pFile,"        | |__| |____) |  | |/ ____ \\| |_) / ____ \\| |\\  | . \\ \n");
          fprintf(pFile,"         \\____/|_____/   |_/_/    \\_\\____/_/    \\_\\_| \\_|_|\\_\\\n");
          fprintf(pFile,"       --------------------------------------------------------\n");

          QString temp = "       " + cd.toString() + " " + ct.toString();
          fprintf(pFile,"%s\n",temp.toLatin1().data());
          fprintf(pFile,"\n");
          fprintf(pFile,"       --------------------------------------------------------\n");
          temp = "       Cuenta N° " + ui->lineEdit->text();
          fprintf(pFile,"%s\n",temp.toLatin1().data());
          fprintf(pFile,"\n");
          cliente.conectar();
          cliente.enviar("obtener");
          cliente.enviar(ui->lineEdit->text().toUtf8().constData());
          string nombre = cliente.recibir();
          string saldo = cliente.recibir();
          temp = "       Nombre:" + QString::fromStdString(nombre);
          fprintf(pFile,"%s\n",temp.toLatin1().data());
          fprintf(pFile,"\n");
          temp = "       Saldo Actual: $" + QString::fromStdString(saldo);
          fprintf(pFile,"%s\n",temp.toLatin1().data());
          fprintf(pFile,"       --------------------------------------------------------\n");
          fprintf(pFile,"       Gracias por preferirnos\n");
          fprintf(pFile,"       Vuelva pronto :)\n");
          fprintf(pFile,"       --------------------------------------------------------\n");

          fclose (pFile);
      }
}

void Banco_cliente::on_pushButton_7_clicked()
{
    cliente.conectar();
    cliente.enviar("cambio_clave");
    cliente.enviar(ui->lineEdit->text().toLatin1().data());
    cliente.enviar(ui->lineEdit_7->text().toLatin1().data());
    cliente.desconectar();
    QMessageBox msgBox;
    msgBox.setText("Se ha cambiado la clave");
    msgBox.exec();
}
