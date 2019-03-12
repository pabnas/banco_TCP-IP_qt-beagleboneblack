#include "../include/Teclado.h"

Teclado::Teclado()
{
	
}


void Teclado::inicializar()
{
	/*
	BlackGPIO tempF1(GPIO_76,output, SecureMode);
	filas[0] = tempF1;
	BlackGPIO tempF2(GPIO_74,output, SecureMode);
	filas[1] = tempF2;
	BlackGPIO tempF3(GPIO_72,output, SecureMode);
	filas[2] = tempF3;
	BlackGPIO tempF4(GPIO_70,output, SecureMode);
	filas[3] = tempF4;
	
	BlackGPIO tempC1(GPIO_75,input, SecureMode);
	columnas[0] = tempC1;
	BlackGPIO tempC2(GPIO_73,input, SecureMode);
	columnas[1] = tempC2;
	BlackGPIO tempC3(GPIO_71,input, SecureMode);
	columnas[2] = tempC3;*/
	Teclas[0][0] = '1';
	Teclas[0][1] = '2';
	Teclas[0][2] = '3';
	Teclas[1][0] = '4';
	Teclas[1][1] = '5';
	Teclas[1][2] = '6';
	Teclas[2][0] = '7';
	Teclas[2][1] = '8';
	Teclas[2][2] = '9';
	Teclas[3][0] = 'A';
	Teclas[3][1] = '0';
	Teclas[3][2] = 'B';
	
	F1 = new BlackGPIO(GPIO_76, output);
	F2 = new BlackGPIO(GPIO_74, output);
	F3 = new BlackGPIO(GPIO_72, output);
	F4 = new BlackGPIO(GPIO_70, output);
	C1 = new BlackGPIO(GPIO_75, input);
	C2 = new BlackGPIO(GPIO_73, input);
	C3 = new BlackGPIO(GPIO_71, input);
	
	numero_de_teclas=0;
}

char Teclado::gettecla()
{
	char resultado = 'z';
	while(resultado == 'z')
	{
		F1->setValue(high);
		if(C1->getNumericValue() == 1)
			resultado = Teclas[0][0];		
		if(C2->getNumericValue() == 1)
			resultado = Teclas[0][1];
		if(C3->getNumericValue() == 1)
			resultado = Teclas[0][2];
		F1->setValue(low);	
		
		F2->setValue(high);
		if(C1->getNumericValue() == 1)
			resultado = Teclas[1][0];		
		if(C2->getNumericValue() == 1)
			resultado = Teclas[1][1];
		if(C3->getNumericValue() == 1)
			resultado = Teclas[1][2];
		F2->setValue(low);	
		
		F3->setValue(high);
		if(C1->getNumericValue() == 1)
			resultado = Teclas[2][0];		
		if(C2->getNumericValue() == 1)
			resultado = Teclas[2][1];
		if(C3->getNumericValue() == 1)
			resultado = Teclas[2][2];
		F3->setValue(low);
		
		F4->setValue(high);
		if(C1->getNumericValue() == 1)
			resultado = Teclas[3][0];		
		if(C2->getNumericValue() == 1)
			resultado = Teclas[3][1];
		if(C3->getNumericValue() == 1)
			resultado = Teclas[3][2];
		F4->setValue(low);	
	}
	numero_de_teclas++;
	return resultado;
}

void Teclado::resetteclas()
{
	numero_de_teclas=0;
}

void Teclado::decteclas()
{
	numero_de_teclas--;
}

int Teclado::getteclas()
{
	return numero_de_teclas;
}
