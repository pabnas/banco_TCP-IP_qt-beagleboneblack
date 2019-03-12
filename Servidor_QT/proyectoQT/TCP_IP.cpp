#include "TCP_IP.h"

void conexion::conectar()
{
    string str = "192.168.1.14";
	ip = new char[str.length() + 1];
	strcpy(ip, str.c_str());
	puerto = 2000;
	connector = new TCPConnector();
    stream = connector->connect(ip, puerto);
}

void conexion::desconectar()
{
	delete stream;
}

void conexion::enviar(string mensaje)
{
	if(stream != NULL)
		stream->send(mensaje.c_str(), mensaje.size());
    usleep(100000);
}

string conexion::recibir()
{
	len = stream->receive(line, sizeof(line));
    line[len] = 0;
    string resultado(line);
    usleep(10000);
    return resultado;
}
