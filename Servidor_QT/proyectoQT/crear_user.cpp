#include "crear_user.h"
#include "ui_crear_user.h"

using namespace std;

Crear_user::Crear_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Crear_user)
{
    ui->setupUi(this);
    QRegExpValidator* rxv = new QRegExpValidator(QRegExp("\\d*"), this); // only pos
    ui->lineEdit->setValidator(rxv);
    ui->lineEdit_2->setValidator(rxv);
}

Crear_user::~Crear_user()
{
    delete ui;
}

void Crear_user::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
        ui->checkBox_2->setEnabled(false);
    else
        ui->checkBox_2->setEnabled(true);
}

void Crear_user::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked())
        ui->checkBox->setEnabled(false);
    else
        ui->checkBox->setEnabled(true);
}

void Crear_user::on_pushButton_clicked()
{
    if((ui->textEdit->toPlainText().isEmpty()) | (ui->textEdit_2->toPlainText().isEmpty()) | (ui->lineEdit_2->text().isEmpty()) | (ui->lineEdit->text().isEmpty()) | ( (!ui->checkBox->isChecked()) & (!ui->checkBox_2->isChecked()))  )
    {
        QMessageBox msgBox;
        msgBox.setText("Error              ");
        msgBox.setInformativeText("Hay campos vacios");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        cliente.conectar();
        cliente.enviar("verificar");
        cliente.enviar(ui->lineEdit_2->text().toLatin1().data());
        string respuesta = cliente.recibir();
        cliente.desconectar();

        if(!respuesta.compare("no"))//si no esta
        {
            bool temp;
            temp = crear_usuario();
            if(temp)
            {
                msgBox.setInformativeText("Se ha creado el usuario");
                msgBox.exec();
            }
            else
            {
                msgBox.setText("Error");
                msgBox.setInformativeText("Ya hay una cuenta con ese numero");
                msgBox.exec();
            }
        }
        else
        {
            msgBox.setText("Error");
            msgBox.setInformativeText("Ya hay una cuenta con ese numero");
            msgBox.exec();
        }
    }
}
/*
bool Crear_user::crear_usuario()
{
    bool resultado;
    QString carpeta = ui->textEdit->toPlainText();
    carpeta = carpeta.toLower();
    carpeta = carpeta.simplified();
    carpeta.replace(" ","_");

    QString ruta = "../../Servidor/Usuarios/"  + carpeta;
    mkdir(ruta.toLatin1().data(), 0700);
    ruta = ruta + "/" + ui->lineEdit_2->text() + ".txt";

    ifstream my_file("test.txt");
    my_file.open(ruta.toLatin1().data());
    if(my_file.fail())
    {
        resultado = true;

        FILE * pFile;
        pFile = fopen (ruta.toLatin1().data(),"w");
        fprintf(pFile,"conectado\n");
        fprintf(pFile,"0\n\n");
        fprintf(pFile,"clave\n");
        fprintf(pFile,"%s\n\n",ui->lineEdit->text().toLatin1().data());
        fprintf(pFile,"saldo\n");
        fprintf(pFile,"0\n\n");
        fprintf(pFile,"nombre\n");
        fprintf(pFile,"%s\n\n",ui->textEdit->toPlainText().toLatin1().data());
        fprintf(pFile,"tipo\n");
        QString tipo;
        if(ui->checkBox->isChecked())
            tipo = ui->checkBox->text();
        else
            tipo = ui->checkBox_2->text();
        fprintf(pFile,"%s\n\n",tipo.toLatin1().data());
        fclose (pFile);

        QString inf = "../../Servidor/Usuarios/" + carpeta  + "/info.txt";
        pFile = fopen (inf.toLatin1().data(),"w");
        fprintf(pFile,"Nombre\n");
        fprintf(pFile,"%s\n\n",ui->textEdit->toPlainText().toLatin1().data());
        fprintf(pFile,"Edad\n");
        fprintf(pFile,"%d\n\n",ui->spinBox->value());
        fprintf(pFile,"Telefono\n");
        fprintf(pFile,"%s\n\n",ui->textEdit_2->toPlainText().toLatin1().data());
        fprintf(pFile,"Cuentas\n\n");
        fclose(pFile);
        usleep(1000);
        QString comando = " ls ../../Servidor/Usuarios/" + carpeta + "| wc -l >> " + inf;
        system(comando.toLatin1().data());
        usleep(1000);
        comando = "ls ../../Servidor/Usuarios/" + carpeta + " >> " + inf;
        system(comando.toLatin1().data());

    }
    else
        resultado = false; //el archivo ya existe
    return resultado;
}*/

bool Crear_user::crear_usuario()
{
    bool resultado;
    QString carpeta = ui->textEdit->toPlainText();
    carpeta = carpeta.toLower();
    carpeta = carpeta.simplified();
    carpeta.replace(" ","_");

    QString ruta = "../Usuarios/"  + carpeta;

    cliente.conectar();
    cliente.enviar("crear");
    cliente.enviar(ruta.toLatin1().data());//crear carpeta

    ruta = ruta + "/" + ui->lineEdit_2->text() + ".txt";

    cliente.enviar(ruta.toLatin1().data());//crear archivo

    string resp = cliente.recibir();
    if(!resp.compare("yes"))
    {
        resultado = true;
        QString x = ui->textEdit->toPlainText();
        x.replace(" ","_");
        cliente.enviar(x.toLatin1().data());//nombre
        cliente.enviar(ui->lineEdit->text().toLatin1().data());//clave

        QString tipo;
        if(ui->checkBox->isChecked())
            tipo = ui->checkBox->text();
        else
            tipo = ui->checkBox_2->text();

        cliente.enviar(tipo.toLatin1().data());//envia el tipo

        QString inf = "../Usuarios/" + carpeta  + "/info.txt";

        cliente.enviar(inf.toLatin1().data());//para archivo de info
        cliente.enviar(QString::number(ui->spinBox->value()).toLatin1().data());//edad
        cliente.enviar(ui->textEdit_2->toPlainText().toLatin1().data());//telefono


        QString comando = " ls ../Usuarios/" + carpeta + "| wc -l >> " + inf;
        cliente.enviar(comando.toLatin1().data());
        comando = "ls ../Usuarios/" + carpeta + " >> " + inf;
        cliente.enviar(comando.toLatin1().data());
    }
    else
        resultado = false; //el archivo ya existe
    return resultado;
}
