#include "../include/lcd.h"


void LCD::enviar_inst()
{
	EN->setValue(low);
	usleep(20);
	EN->setValue(high);
	usleep(20);	
	EN->setValue(low);
}

void LCD::inicializar()
{
	teclado.inicializar();
	/*
	BlackGPIO temp7(GPIO_39,output, SecureMode);
	DB7 = temp7;
	BlackGPIO temp6(GPIO_35,output, SecureMode);
	DB7 = temp6;
	BlackGPIO temp5(GPIO_67,output, SecureMode);
	DB7 = temp5;
	BlackGPIO temp4(GPIO_68,output, SecureMode);
	DB7 = temp4;
	BlackGPIO temp3(GPIO_44,output, SecureMode);
	DB7 = temp3;
	BlackGPIO temp2(GPIO_26,output, SecureMode);
	DB7 = temp2;
	BlackGPIO temp1(GPIO_46,output, SecureMode);
	DB7 = temp1;
	BlackGPIO temp0(GPIO_65,output, SecureMode);
	DB7 = temp0;
	
	
	BlackGPIO tempEN(GPIO_38,output, SecureMode);
	EN = tempEN;
	BlackGPIO tempRS(GPIO_34,output, SecureMode);
	RS = tempRS;*/

	
	DB7 = new BlackGPIO(GPIO_39, output);
	DB6 = new BlackGPIO(GPIO_35, output);
	DB5 = new BlackGPIO(GPIO_67, output);
	DB4 = new BlackGPIO(GPIO_68, output);
	DB3 = new BlackGPIO(GPIO_44, output);
	DB2 = new BlackGPIO(GPIO_26, output);
	DB1 = new BlackGPIO(GPIO_46, output);
	DB0 = new BlackGPIO(GPIO_65, output);
	RS = new BlackGPIO(GPIO_38, output);
	EN = new BlackGPIO(GPIO_34, output);
	
	
	//modo de 8 bits
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(high);
	DB4->setValue(high);
	DB3->setValue(high);
	DB2->setValue(low);
	DB1->setValue(low);
	DB0->setValue(low);
	enviar_inst();
	
	//mode set 
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(low);
	DB4->setValue(low);
	DB3->setValue(low);
	DB2->setValue(high);
	DB1->setValue(low);
	DB0->setValue(high);
	enviar_inst();
	
	//display on	
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(low);
	DB4->setValue(low);
	DB3->setValue(high);
	DB2->setValue(high);
	DB1->setValue(low);//sin cursor
	DB0->setValue(low);//sin parpadeo
	enviar_inst();
	
	borrar_pantalla();
	
	//home
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(low);
	DB4->setValue(low);
	DB3->setValue(low);
	DB2->setValue(low);
	DB1->setValue(high);
	DB0->setValue(low);
	enviar_inst();
	
}

void LCD::borrar_pantalla()
{	
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(low);
	DB4->setValue(low);
	DB3->setValue(low);
	DB2->setValue(low);
	DB1->setValue(low);
	DB0->setValue(high);
	enviar_inst();

	//home
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(low);
	DB4->setValue(low);
	DB3->setValue(low);
	DB2->setValue(low);
	DB1->setValue(high);
	DB0->setValue(low);
	enviar_inst();
}

void LCD::ubicar_cursor(int x, int y)
{	
	//home
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(low);
	DB4->setValue(low);
	DB3->setValue(low);
	DB2->setValue(low);
	DB1->setValue(high);
	DB0->setValue(low);
	enviar_inst();
	
	if(y == 2)
	{
		for(int j=0; j < 41;y++)
		{			
			RS->setValue(low);
			DB7->setValue(low);
			DB6->setValue(low);
			DB5->setValue(low);
			DB4->setValue(high);
			DB3->setValue(low);
			DB2->setValue(high);
			DB1->setValue(low);
			DB0->setValue(low);
			enviar_inst();
		}
	}
	
	for(int j=0; j < x;y++)
	{			
		RS->setValue(low);
		DB7->setValue(low);
		DB6->setValue(low);
		DB5->setValue(low);
		DB4->setValue(high);
		DB3->setValue(low);
		DB2->setValue(high);
		DB1->setValue(low);
		DB0->setValue(low);
		enviar_inst();
	}	
}

void LCD::escribir_atras()
{
	//moverme una pos atras	
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(low);
	DB4->setValue(high);
	DB3->setValue(low);
	DB2->setValue(low);
	DB1->setValue(low);
	DB0->setValue(low);
	enviar_inst();
	
	//imprimir espacio	
	escribir(" ");
	
	//moverme atras	
	RS->setValue(low);
	DB7->setValue(low);
	DB6->setValue(low);
	DB5->setValue(low);
	DB4->setValue(high);
	DB3->setValue(low);
	DB2->setValue(low);
	DB1->setValue(low);
	DB0->setValue(low);
	enviar_inst();
}

void LCD::escribir(string mensaje)
{
	int lon = mensaje.length();
	char Cmensaje [100];	
	strncpy(Cmensaje, mensaje.c_str(), sizeof(mensaje));
	Cmensaje[sizeof(Cmensaje) - 1] = 0;
	
	char temporal;
	
	
	for(int i = 0; i < lon;i++)
	{
		temporal = Cmensaje[i];
		RS->setValue(high);
		
		if(temporal & 0x80)
			DB7->setValue(high);
		else
			DB7->setValue(low);
			
		if(temporal & 0x40)
			DB6->setValue(high);
		else
			DB6->setValue(low);
			
		if(temporal & 0x20)
			DB5->setValue(high);
		else
			DB5->setValue(low);
			
		if(temporal & 0x10)
			DB4->setValue(high);
		else
			DB4->setValue(low);
			
		if(temporal & 0x08)
			DB3->setValue(high);
		else
			DB3->setValue(low);
			
		if(temporal & 0x04)
			DB2->setValue(high);
		else
			DB2->setValue(low);
			
		if(temporal & 0x02)
			DB1->setValue(high);
		else
			DB1->setValue(low);
			
		if(temporal & 0x01)
			DB0->setValue(high);
		else
			DB0->setValue(low);
			
		enviar_inst();
	}
}

void LCD::menu_usuario()
{
	std::string::size_type sz;   // alias of size_t
	
	borrar_pantalla();
	ubicar_cursor(1,1);
	escribir("ID:");
	ubicar_cursor(2,1);
	escribir("Clave:");
	
	ubicar_cursor(4,1);
	usuario = print_numero();
	ubicar_cursor(7,2);
	clave = print_numero();
}

string LCD::print_numero()
{
	string res;
	char digitos[100];
	char temp;
	int num_teclas = 0;
	while(1)
	{
		temp=teclado.gettecla();
		num_teclas = teclado.getteclas();
		
		if(((temp == 'B')&(num_teclas != 1))|(num_teclas > 10))
		{
			escribir_atras();
			teclado.decteclas();
		}
		else if((temp == 'A')&(num_teclas <= 10)&(num_teclas >= 4))
			break;
		else
		{		
			digitos[num_teclas-1] = temp;
			digitos[num_teclas] = 0;
			string Sres(digitos);
			escribir(Sres);
			res = Sres;
		}
	}
	return res;
}

string LCD::getusuario()
{
	return usuario;
}

string LCD::getclave()
{
	return clave;
}

int LCD::menu()
{
	int opcion = 1;//empieza en consultar saldo
	int max_opcion = 5;
	char tecla;
	
	while(1)
	{
		tecla = teclado.gettecla();
		if(tecla == '8')//bajar opcion
		{
			opcion++;
			if(opcion > max_opcion)
				opcion = 1;
		}
		else if(tecla == '2')//subir opcion
		{
			opcion--;
			if(opcion < 1)
				opcion = max_opcion;
		}
		else if(tecla == 'A')//aceptar
		{
			break;
		}
		
		borrar_pantalla();
		ubicar_cursor(1,1);
		if(opcion == 1)//consultar
			escribir("Consultar saldo");
		else if(opcion == 2)//retirar
			escribir("Retirar");
		else if(opcion == 3)//consignar
			escribir("Consignar");
		else if(opcion == 4)//Transferir
			escribir("Transferir");
		else if(opcion == 5)//Salir
			escribir("Salir");
		else
			escribir("error");
		ubicar_cursor(1,2);
		escribir(nombre);
	
	}
	return opcion;
}

void LCD::setnombre(string Snombre)
{
	nombre = Snombre;
}

bool LCD::recibo()
{
	borrar_pantalla();
	ubicar_cursor(1,1);
	escribir("Desea un recibo");
	ubicar_cursor(1,2);
	escribir("A(y) B(n)");
	char temp;
	bool resultado = false;
	while(1)
	{
		temp = teclado.gettecla();
		if(temp == 'A')
		{
			resultado = true;
			break;
		}
		else if(temp == 'B')
		{
			resultado = false;
			break;
		}
	}
	return resultado;
}

char LCD::gettecla()
{
	return teclado.gettecla();	
}

string LCD::print_monto()
{
	string res;
	char digitos[100];
	char temp;
	int num_teclas = 0;
	while(1)
	{
		temp=teclado.gettecla();
		num_teclas = teclado.getteclas();
		
		if(((temp == 'B')&(num_teclas != 1))|(num_teclas > 10))
		{
			escribir_atras();
			teclado.decteclas();
		}
		else if((temp == 'A')&(num_teclas <= 10)&(num_teclas >= 2))
			break;
		else
		{		
			digitos[num_teclas-1] = temp;
			digitos[num_teclas] = 0;
			string Sres(digitos);
			escribir(Sres);
			res = Sres;
		}
	}
	return res;
}

	
