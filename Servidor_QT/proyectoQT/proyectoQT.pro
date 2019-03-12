#-------------------------------------------------
#
# Project created by QtCreator 2017-06-09T13:17:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proyectoQT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpacceptor.cpp \
    tcpconnector.cpp \
    tcpstream.cpp \
    TCP_IP.cpp \
    crear_user.cpp \
    Comandos_generales.cpp \
    banco_cliente.cpp \
    informacion_server.cpp

HEADERS  += mainwindow.h \
    ../../Servidor/include/tcpacceptor.h \
    ../../Servidor/include/tcpconnector.h \
    ../../Servidor/include/TCP_IP_server.h \
    ../../Servidor/include/tcpstream.h \
    tcpacceptor.h \
    tcpconnector.h \
    tcpstream.h \
    TCP_IP.h \
    crear_user.h \
    Comandos_generales.h \
    banco_cliente.h \
    informacion_server.h

FORMS    += mainwindow.ui \
    crear_user.ui \
    banco_cliente.ui \
    informacion_server.ui
