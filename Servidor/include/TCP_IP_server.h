#include <stdio.h>	
#include <stdlib.h>
#include "../include/tcpacceptor.h"

using namespace std;

class conexion
{
	private:
		
		char *ip = "192.168.1.14";
		int puerto = 2000;
		TCPStream* stream;
		TCPAcceptor* acceptor;
		ssize_t len;
        	char line[256];
		
	public:
		void conectar();
		void desconectar();
		void enviar(string mensaje);
		void esperar_cliente();
		string recibir();
		TCPStream* getStream();
		void setStream(TCPStream* streamin);
};

