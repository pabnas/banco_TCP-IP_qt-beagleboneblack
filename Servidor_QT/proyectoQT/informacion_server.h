#ifndef INFORMACION_SERVER_H
#define INFORMACION_SERVER_H

#include <QDialog>

namespace Ui {
class Informacion_server;
}

class Informacion_server : public QDialog
{
    Q_OBJECT

public:
    explicit Informacion_server(QWidget *parent = 0);
    ~Informacion_server();

private slots:
    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::Informacion_server *ui;
    void buscar_usuario();
    void buscar_id();
    void buscar_todo();
};

#endif // INFORMACION_SERVER_H
