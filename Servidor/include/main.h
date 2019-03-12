#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <list>
#include <sstream>
#include <fstream>
#include <pthread.h>

#include "../include/Comandos_generales.h"
#include "../include/TCP_IP_server.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>	
#include <sys/mman.h>
#include <sys/wait.h>

using namespace std;

pthread_mutex_t mutex_archivos;
pthread_mutex_t mutex_conectado;
pthread_mutex_t mutex_stream;
pthread_mutex_t mutex_consig;

class User
{
	public:
		string conectado;
		string clave;
		string saldo;
		string nombre;
		string tipo;
		string id;
};


void *Atender_cliente(void *a);
bool verificar(string id);
void descargar_usuario(User &usuario);
void cargar_usuario(User &usuario);
bool login(string id,string clave);
void actualizar_info_general();
string Buscar_id(string id);

conexion server;
	
