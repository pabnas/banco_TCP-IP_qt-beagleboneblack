#ifndef TCP_H
#define TCP_H

#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#include "tcpconnector.h"

using namespace std;

class conexion
{
	private:
		
		char *ip;
		int puerto;
		TCPStream* stream;
		TCPConnector* connector;
		ssize_t len;
		char line[256];
		
	public:
		void conectar();
		void desconectar();
		void enviar(string mensaje);
		string recibir();
};

#endif
