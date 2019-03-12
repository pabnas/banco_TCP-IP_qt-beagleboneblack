#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <list>
#include <sstream>


#include "BlackGPIO.h"

using namespace std;
using namespace BlackLib;

class Teclado
{
	private:

	BlackGPIO *F1;
	BlackGPIO *F2;
	BlackGPIO *F3;
	BlackGPIO *F4;
	BlackGPIO *C1;
	BlackGPIO *C2;
	BlackGPIO *C3;
	char Teclas [4][3];
	int numero_de_teclas;
	
	
	public:
	Teclado();
	int getteclas();
	void resetteclas();
	void decteclas();
	
	void inicializar();
	char gettecla();
};


