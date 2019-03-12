#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Comandos_generales.h"

using namespace std;

class Usuario_banco
{
	private:
		
		bool conectado;
		long int saldo;
		string tipo;
		
	public:
	
		void cargar(string cuenta);
		bool isconnected();
		void cambiarconectado();
		int consultar_saldo();
		void retirar(long int monto);
		void consignar(long int monto);
		void transferir(long int monto,string cuenta);
};

void Usuario_banco::cargar(string cuenta)
{
	FILE * pFile;
	cuenta = cuenta + ".txt"
	pFile = fopen (cuenta,"r");
	
	char Linea[1024];
	Ubicar_cursor(1,1,pFile);
	fscanf(pFile,"%s",Linea);
	if(atoi(Linea) == 1)//esta conectado
	{
		fclose(pFile);
	}
	else
	{
		conectado = 1;
	}
	
}

