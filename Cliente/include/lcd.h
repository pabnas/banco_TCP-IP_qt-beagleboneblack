#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <list>
#include <sstream>


#include "BlackGPIO.h"
#include "Teclado.h"

using namespace std;
using namespace BlackLib;


class LCD
{
	private:
		string usuario;
		string clave;
		string nombre;
		
		Teclado teclado;
		BlackGPIO *DB7;
		BlackGPIO *DB6;
		BlackGPIO *DB5;
		BlackGPIO *DB4;
		BlackGPIO *DB3;
		BlackGPIO *DB2;
		BlackGPIO *DB1;
		BlackGPIO *DB0;
		BlackGPIO *RS;
		BlackGPIO *EN;
	
	public:	
		void enviar_inst();
		void inicializar();
		void borrar_pantalla();
		void ubicar_cursor(int x,int y);
		void escribir(string mensaje);
		void escribir_atras();
		
		char gettecla();

		//para la interfaz
		string print_numero();
		string print_monto();		

		//metodos para el login
		void menu_usuario();
		string getusuario();
		string getclave();
		void setnombre(string Snombre);
	
		//metodos para el menu
		int menu();		//retorna la opcion seleccionada
		bool recibo();
		
};

