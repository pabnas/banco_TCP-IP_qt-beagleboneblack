#include "../include/TCP_IP_server.h"

void conexion::conectar()
{	
	stream = NULL;
    acceptor = NULL;
    acceptor = new TCPAcceptor(puerto,ip);
    while(1)
	{
		if (acceptor->start() == 0)
			break;
	}
}

void conexion::esperar_cliente()
{	
	stream = acceptor->accept();
}

void conexion::desconectar()
{
    delete stream;
}

void conexion::enviar(string mensaje)
{	
    stream->send(mensaje.c_str(), mensaje.size());
	usleep(10000);
}

string conexion::recibir()
{	
	len = stream->receive(line, sizeof(line));
	line[len] = 0;
	string resultado(line);
	usleep(10000);
	return resultado;
}

TCPStream* conexion::getStream()
{
	return stream;
}

void conexion::setStream(TCPStream* streamin)
{
	stream = streamin;
}


