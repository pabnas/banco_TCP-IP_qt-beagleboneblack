#include "informacion_server.h"
#include "ui_informacion_server.h"
#include "qmessagebox.h"
#include <sstream>
#include <fstream>
#include "Comandos_generales.h"

using namespace std;

Informacion_server::Informacion_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Informacion_server)
{
    ui->setupUi(this);QRegExpValidator* rxv = new QRegExpValidator(QRegExp("\\d*"), this); // only pos
    //ui->lineEdit->setValidator(rxv);
    ui->lineEdit_2->setValidator(rxv);
}

Informacion_server::~Informacion_server()
{
    delete ui;
}

void Informacion_server::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->checkBox_2->setEnabled(false);
        ui->lineEdit_2->setText("");
        ui->lineEdit_2->setEnabled(false);
        ui->checkBox_3->setEnabled(false);
    }
    else
    {
        ui->checkBox_2->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->checkBox_3->setEnabled(true);
    }
}

void Informacion_server::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked())
    {
        ui->checkBox->setEnabled(false);
        ui->lineEdit->setText("");
        ui->lineEdit->setEnabled(false);
        ui->checkBox_3->setEnabled(false);
    }
    else
    {
        ui->checkBox->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->checkBox_3->setEnabled(true);
    }
}

void Informacion_server::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked())
    {
        ui->checkBox_2->setEnabled(false);
        ui->checkBox->setEnabled(false);
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
    }
    else
    {
        ui->checkBox_2->setEnabled(true);
        ui->checkBox->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
    }
}

void Informacion_server::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();

    if(ui->checkBox->isChecked())
        buscar_usuario();
    else if(ui->checkBox_2->isChecked())
        buscar_id();
    else if(ui->checkBox_3->isChecked())
        buscar_todo();
    else
    {
        QMessageBox ms;
        ms.setText("Porfavor eliga una opcion");
        ms.exec();
    }
}


void Informacion_server::buscar_usuario()
{
    QString usuario = ui->lineEdit->text();
    usuario = usuario.simplified();
    usuario = usuario.toLower();
    usuario.replace(" ","_");

    QString ruta = "../../Servidor/Usuarios/" + usuario + "/info.txt";

    ifstream my_file("test.txt");
    my_file.open(ruta.toLatin1().data());

    if(my_file.fail())//si no esta
    {
        QMessageBox ms;
        ms.setText("Error");
        ms.setInformativeText("No se encuentra ese usuario");
        ms.exec();
    }
    else//si encuentra el archivo de info
    {
        FILE * pFile;
        char Linea[1024];
        pFile = fopen (ruta.toLatin1().data(),"r");

        Ubicar_cursor(2,0,pFile);
        fscanf(pFile, "%s" , Linea);//nombre
        string LineaTemp(Linea);
        QString x = QString::fromStdString(LineaTemp);
        x.replace("_"," ");
        QString nombre = "Nombre : " + x;
        nombre.replace("_"," ");
        ui->plainTextEdit->appendPlainText(nombre);


        Ubicar_cursor(5,0,pFile);
        fscanf(pFile, "%s" , Linea);//edad
        LineaTemp = Linea;
        QString edad = "Edad : " + QString::fromStdString(LineaTemp);
        ui->plainTextEdit->appendPlainText(edad);

        Ubicar_cursor(8,0,pFile);
        fscanf(pFile, "%s" , Linea);//telefono
        LineaTemp = Linea;
        QString telefono = "Telefono : " + QString::fromStdString(LineaTemp);
        ui->plainTextEdit->appendPlainText(telefono);

        Ubicar_cursor(12,0,pFile);
        fscanf(pFile, "%s" , Linea);//numero de cuentas
        long int numero_De_cuentas = atoi(Linea);
        ui->plainTextEdit->appendPlainText("Tiene " + QString::number(numero_De_cuentas-1) + " Cuentas\n");

        for(int i=0;i < numero_De_cuentas;i++)
        {
            Ubicar_cursor(13 + i,0,pFile);
            fscanf(pFile, "%s" , Linea);
            string Temp(Linea);
            if(Temp.compare("info.txt"))
            {
                LineaTemp = Linea;
                QString texto = "\nNumero de cuenta : " + QString::fromStdString(LineaTemp);
                texto.replace(".txt","");
                ui->plainTextEdit->appendPlainText(texto);

                string cuenta(Linea);//cuenta.txt
                string Stemp(usuario.toUtf8().data());//carpeta usuario
                string ruta2 = "../../Servidor/Usuarios/" + Stemp + "/" + cuenta;

                FILE * pFile2;
                char Linea2[1024];
                pFile2 = fopen (ruta2.c_str(),"r");

                Ubicar_cursor(2,0,pFile2);//conectado
                fscanf(pFile2, "%s" , Linea2);
                LineaTemp = Linea2;
                QString conectado = "Conectado : " + QString::fromStdString(LineaTemp);
                ui->plainTextEdit->appendPlainText(conectado);

                Ubicar_cursor(8,0,pFile2);//saldo
                fscanf(pFile2, "%s" , Linea2);
                LineaTemp = Linea2;
                QString saldo = "Saldo : " + QString::fromStdString(LineaTemp);
                ui->plainTextEdit->appendPlainText(saldo);

                Ubicar_cursor(14,0,pFile2);//tipo
                fscanf(pFile2, "%s" , Linea2);
                LineaTemp = Linea2;
                QString tipo = "Tipo de cuenta : " + QString::fromStdString(LineaTemp);
                ui->plainTextEdit->appendPlainText(tipo + "\n");

                fclose(pFile2);
            }
        }
        fclose(pFile);
    }
}

void Informacion_server::buscar_id()
{
    QString ID = ui->lineEdit_2->text();
    bool resultado = false;

    QString ruta = "../../Servidor/Usuarios/info.txt";
    FILE * pFile;
    char Linea[1024];
    pFile = fopen (ruta.toLatin1().data(),"r");

    fscanf(pFile, "%s" , Linea);//numero de usuarios
    long int numero_De_usuarios = atoi(Linea);
    for(int i=0;i < numero_De_usuarios;i++)
    {
        Ubicar_cursor(2+i,0,pFile);
        fscanf(pFile, "%s" , Linea);
        string Temp(Linea);
        if(Temp.compare("info.txt"))
        {
            string Tid(ID.toLatin1().data());
            string carpeta = "../../Servidor/Usuarios/" + Temp + "/" + Tid + ".txt";
            ifstream my_file("test.txt");
            my_file.open(carpeta.c_str());
            if(!my_file.fail())//si esta
            {
                resultado = true;
                ui->plainTextEdit->appendPlainText("Cuenta : " + ID);
                FILE * pFile2;
                char Linea2[1024];
                pFile2 = fopen(carpeta.c_str(),"r");

                Ubicar_cursor(2,0,pFile2);//conectado
                fscanf(pFile2, "%s" , Linea2);
                string TLinea2(Linea2);
                ui->plainTextEdit->appendPlainText("Conectado : " + QString::fromStdString(TLinea2));

                Ubicar_cursor(5,0,pFile2);//clave
                fscanf(pFile2, "%s" , Linea2);
                TLinea2 = Linea2;
                ui->plainTextEdit->appendPlainText("Clave : " + QString::fromStdString(TLinea2));

                Ubicar_cursor(8,0,pFile2);//saldo
                fscanf(pFile2, "%s" , Linea2);
                TLinea2 = Linea2;
                ui->plainTextEdit->appendPlainText("Saldo : $" + QString::fromStdString(TLinea2));

                Ubicar_cursor(11,0,pFile2);//nombre
                fscanf(pFile2, "%s" , Linea2);
                TLinea2 = Linea2;
                QString x = QString::fromStdString(TLinea2);
                x.replace("_"," ");
                ui->plainTextEdit->appendPlainText("Nombre : " + x);

                Ubicar_cursor(14,0,pFile2);//tipo
                fscanf(pFile2, "%s" , Linea2);
                TLinea2 = Linea2;
                ui->plainTextEdit->appendPlainText("Tipo : " + QString::fromStdString(TLinea2));

                fclose(pFile2);
            }
        }
    }
    fclose(pFile);

    if(resultado == false)
    {
        QMessageBox ms;
        ms.setText("Error");
        ms.setInformativeText("No se encuentra esa cuenta");
        ms.exec();
    }
}

void Informacion_server::buscar_todo()
{
    FILE * pFile3;
    char Linea3[1024];
    QString ruta3 = "../../Servidor/Usuarios/info.txt";
    pFile3 = fopen (ruta3.toLatin1().data(),"r");
    fscanf(pFile3, "%s" , Linea3);//numero de cuentas
    long int numero_De_cuentas3 = atoi(Linea3);
    for(int i=0;i < numero_De_cuentas3;i++)
    {
        ui->plainTextEdit->appendPlainText("--------------------------------------------------------------------");
        Ubicar_cursor(2+i,0,pFile3);
        fscanf(pFile3, "%s" , Linea3);
        string Temp3(Linea3);
        if(Temp3.compare("info.txt"))
        {
            QString usuario = QString::fromStdString(Temp3);


            QString ruta = "../../Servidor/Usuarios/" + usuario + "/info.txt";

            ifstream my_file("test.txt");
            my_file.open(ruta.toLatin1().data());

            if(my_file.fail())//si no esta
            {
                QMessageBox ms;
                ms.setText("Error");
                ms.setInformativeText("No se encuentra ese usuario");
                ms.exec();
            }
            else//si encuentra el archivo de info
            {
                FILE * pFile;
                char Linea[1024];
                pFile = fopen (ruta.toLatin1().data(),"r");

                Ubicar_cursor(2,0,pFile);
                fscanf(pFile, "%s" , Linea);//nombre
                string LineaTemp(Linea);
                QString x = QString::fromStdString(LineaTemp);
                x.replace("_"," ");
                QString nombre = "Nombre : " + x;
                nombre.replace("_"," ");
                ui->plainTextEdit->appendPlainText(nombre);


                Ubicar_cursor(5,0,pFile);
                fscanf(pFile, "%s" , Linea);//edad
                LineaTemp = Linea;
                QString edad = "Edad : " + QString::fromStdString(LineaTemp);
                ui->plainTextEdit->appendPlainText(edad);

                Ubicar_cursor(8,0,pFile);
                fscanf(pFile, "%s" , Linea);//telefono
                LineaTemp = Linea;
                QString telefono = "Telefono : " + QString::fromStdString(LineaTemp);
                ui->plainTextEdit->appendPlainText(telefono);

                Ubicar_cursor(12,0,pFile);
                fscanf(pFile, "%s" , Linea);//numero de cuentas
                long int numero_De_cuentas = atoi(Linea);
                ui->plainTextEdit->appendPlainText("Tiene " + QString::number(numero_De_cuentas-1) + " Cuentas\n");

                for(int i=0;i < numero_De_cuentas;i++)
                {
                    Ubicar_cursor(13 + i,0,pFile);
                    fscanf(pFile, "%s" , Linea);
                    string Temp(Linea);
                    if(Temp.compare("info.txt"))
                    {
                        LineaTemp = Linea;
                        QString texto = "\nNumero de cuenta : " + QString::fromStdString(LineaTemp);
                        texto.replace(".txt","");
                        ui->plainTextEdit->appendPlainText(texto);

                        string cuenta(Linea);//cuenta.txt
                        string Stemp(usuario.toUtf8().data());//carpeta usuario
                        string ruta2 = "../../Servidor/Usuarios/" + Stemp + "/" + cuenta;

                        FILE * pFile2;
                        char Linea2[1024];
                        pFile2 = fopen (ruta2.c_str(),"r");

                        Ubicar_cursor(2,0,pFile2);//conectado
                        fscanf(pFile2, "%s" , Linea2);
                        LineaTemp = Linea2;
                        QString conectado = "Conectado : " + QString::fromStdString(LineaTemp);
                        ui->plainTextEdit->appendPlainText(conectado);

                        Ubicar_cursor(8,0,pFile2);//saldo
                        fscanf(pFile2, "%s" , Linea2);
                        LineaTemp = Linea2;
                        QString saldo = "Saldo : " + QString::fromStdString(LineaTemp);
                        ui->plainTextEdit->appendPlainText(saldo);

                        Ubicar_cursor(14,0,pFile2);//tipo
                        fscanf(pFile2, "%s" , Linea2);
                        LineaTemp = Linea2;
                        QString tipo = "Tipo de cuenta : " + QString::fromStdString(LineaTemp);
                        ui->plainTextEdit->appendPlainText(tipo + "\n");

                        fclose(pFile2);
                    }
                }
                fclose(pFile);
            }
        }
    }
    fclose(pFile3);
}











