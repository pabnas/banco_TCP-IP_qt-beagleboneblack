#include <iostream>
#include <stdio.h>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "serialib.h"
#include "TCP_IP.h"


#if defined (_WIN32) || defined( _WIN64)
#define         DEVICE_PORT             "COM1"                               // COM1 for windows
#endif

#ifdef __linux__
#define         DEVICE_PORT             "/dev/ttyACM0"                         // ttyS0 for linux
#endif

using namespace std;

FILE *file;
serialib LS;  

string recibir_puerto();
void escribir_puerto(string mensaje);
void cerrar_puerto();
void abrir_puerto();
string ReplaceAll(string str, const string& from, const string& to);

int main()
{
	system("clear");
	abrir_puerto();

	string id_user;
	string clave_user;
	conexion cliente;
	
	while(1)
	{
		string respuesta = recibir_puerto();
		//printf("\n\nrecibido = %s\n",respuesta.c_str());
		
		if(!respuesta.compare("Login"))
		{			
			printf("Login\n");
	
			string id = recibir_puerto();
			string clave = recibir_puerto();
			printf("id = %s clave = %s \n",id.c_str(),clave.c_str());

			
			cliente.conectar();
			cliente.enviar("verificar");
			cliente.enviar(id);
			string rverificar = cliente.recibir();
			cliente.desconectar();

			if(!rverificar.compare("yes"))
			{				
				cliente.conectar();
				cliente.enviar("login");
				cliente.enviar(id);
				cliente.enviar(clave);
				cliente.recibir();//recibe si esta conectado pero no se usa aca
				cliente.desconectar();

				id_user = id;
				clave_user = clave;
				
				escribir_puerto("1");
				
			}
			else
			{
				escribir_puerto("0");
			}
		}
		else if(!respuesta.compare("Saldo"))
		{
			printf("Saldo\n");
			cliente.conectar();
			cliente.enviar("obtener");
			cliente.enviar(id_user);

			cliente.recibir();						
			string saldo = cliente.recibir();
			cliente.desconectar();
			
			escribir_puerto(saldo);
		}
		else if(!respuesta.compare("Consignar"))
		{			
			printf("Consignar\n");
			string monto = recibir_puerto();

			cliente.conectar();
			cliente.enviar("consignar");
			cliente.enviar(id_user);
			cliente.enviar(monto);
			cliente.desconectar();
			//printf("Consignar %s",monto.c_str());
		}
		else if(!respuesta.compare("Retirar"))
		{
			printf("Retirar\n");
			cliente.conectar();
			cliente.enviar("obtener");
			cliente.enviar(id_user);

			cliente.recibir();						
			string saldo = cliente.recibir();
			long int isaldo = atoi(saldo.c_str());
			cliente.desconectar();
			
			string monto = recibir_puerto();	
			//printf("Retirar %s",monto.c_str());		
			long int iretiro = atoi(monto.c_str());
			long int ires = isaldo - iretiro;

			if(ires < 0)
			{
				string rc = "0";
				escribir_puerto(rc);
			}
			else
			{
				iretiro = iretiro *-1;
				stringstream ss;
				ss << iretiro;
				string retiro = ss.str();

	
				cliente.conectar();
				cliente.enviar("consignar");
				cliente.enviar(id_user);
				cliente.enviar(retiro);
				cliente.desconectar();
					
				string rc = "1";
				escribir_puerto(rc);
			}			
		}
		else if(!respuesta.compare("Transferir"))
		{
			printf("Transferir\n");
			string cuenta = recibir_puerto();
			string monto = recibir_puerto();
			//printf("Transferir id %s monto %s\n",cuenta.c_str(),monto.c_str());

			cliente.conectar();
			cliente.enviar("obtener");
			cliente.enviar(id_user);

			cliente.recibir();						
			string saldo = cliente.recibir();
			long int isaldo = atoi(saldo.c_str());
			cliente.desconectar();
					
			long int iretiro = atoi(monto.c_str());
			long int ires = isaldo - iretiro;

			if(ires < 0)
			{
				string rc = "0";
				escribir_puerto(rc);
			}
			else
			{
				cliente.conectar();
				cliente.enviar("verificar");
				cliente.enviar(cuenta);
				string rverificar = cliente.recibir();
				cliente.desconectar();
				printf("1)%s\n",rverificar.c_str());

				if(!rverificar.compare("yes"))
				{
					iretiro = iretiro *-1;
					stringstream ss;
					ss << iretiro;
					string retiro = ss.str();

		
					cliente.conectar();
					cliente.enviar("consignar");
					cliente.enviar(id_user);
					cliente.enviar(retiro);
					cliente.desconectar();

					
					cliente.conectar();
					cliente.enviar("consignar");
					cliente.enviar(cuenta);
					cliente.enviar(monto);
					cliente.desconectar();
						
					string rc = "1";
					escribir_puerto(rc);
					
				}
				else
				{
					string rc = "0";
					escribir_puerto(rc);
				}
			}			
		}
		else if(!respuesta.compare("Desconectar"))
		{
			printf("Desconectar\n");
			cliente.conectar();
			cliente.enviar("desconectar");
			cliente.enviar(id_user);
			cliente.desconectar();
		}			
	}
	cerrar_puerto();	
}


void abrir_puerto()
{
	int Ret;
	Ret=LS.Open(DEVICE_PORT,9600);                                        // Open serial link at 115200 bauds
    if (Ret!=1) {                                                           // If an error occured...
        printf ("Error while opening port. Permission problem ?\n");        // ... display a message ...
                                                                 // ... quit the application
    }
    printf ("Serial port opened successfully !\n");
    usleep(3500000);
}

void cerrar_puerto()
{
	LS.Close();
}

void escribir_puerto(string mensaje)
{
	mensaje = mensaje + "\n";
	int Ret=LS.WriteString(mensaje.c_str());                                             // Send the command on the serial port
    if (Ret!=1) {                                                           // If the writting operation failed ...
        printf ("Error while writing data\n");                              // ... display a message ...
    }
}

string recibir_puerto()
{	
	char Buffer[128];
	int Ret=LS.ReadString(Buffer,'\n',128,5000);                                // Read a maximum of 128 characters with a timeout of 5 seconds
	string resultado;
	
                                                                            // The final character of the string must be a line feed ('\n')
    if (Ret>0)                                                              // If a string has been read from, print the string
    {
		//printf ("String read from serial port : %s",Buffer);
        string temp(Buffer);
        resultado = temp;
	}
   resultado = ReplaceAll(resultado, std::string("\n"), std::string(""));
   resultado = ReplaceAll(resultado, std::string("\r"), std::string(""));
   return resultado;
}

string ReplaceAll(string str, const string& from, const string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

