#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <list>
#include <sstream>

#include "TCP_IP.h"
#include "lcd.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>	
#include <sys/mman.h>
#include <sys/wait.h>

using namespace std;


class Usuario
{
	public:
	string id;
	string clave;
	string saldo;
	string nombre;
	string conectado;
};

bool verificar_usuario(Usuario &usuario);
bool verificar_login(Usuario &usuario);
void obtener_usuario(Usuario &usuario);
void enviar_usuario(Usuario &usuario);
void usuario_desconectado(Usuario &usuario);

void consultar_saldo(Usuario &usuario);
long int retirar_saldo(Usuario &usuario);
void consignar_saldo(Usuario &usuario);
void transferir_saldo(Usuario &usuario);
void salir(Usuario &usuario);

