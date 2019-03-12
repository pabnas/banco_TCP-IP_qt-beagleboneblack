#include "../include/main.h"

	LCD lcd;
	conexion cliente;
	
int main(int argc, char * argv[])
{	
	cliente.conectar();
	lcd.inicializar();
	Usuario usuario;
	
	while(1)
	{
		while(1)//lo repite hasta tener un usuario correcto
		{
			lcd.menu_usuario();
			usuario.id = lcd.getusuario();
			usuario.clave = lcd.getclave();

			bool login = verificar_login(usuario);
			if(login == false)
			{
				lcd.borrar_pantalla();
				lcd.escribir("datos erroneos");
				lcd.gettecla();
			}
			else
				break;
		}

		while(1)
		{
			int opcion;
			opcion = lcd.menu();
			if(opcion == 1)//consultar saldo
				consultar_saldo(usuario);
			else if(opcion == 2)//retirar saldo
				retirar_saldo(usuario);
			else if(opcion == 3)//consignar saldo
				consignar_saldo(usuario);
			else if(opcion == 4)//transferir saldo
				transferir_saldo(usuario);
			else if(opcion == 5)//salir
			{
				salir(usuario);
				break;
			}
		}
	}
	cliente.desconectar();
	return 0;
}

bool verificar_usuario(Usuario &usuario)//para saber si existe
{
	bool resultado = false;
	cliente.enviar("verificar");
	cliente.enviar(usuario.id);
	string temp = cliente.recibir();
	if(!temp.compare("yes"))
		resultado = true;		
	else
		resultado = false;
	return resultado;
}

bool verificar_login(Usuario &usuario)//para conectarse
{	
	bool resultado = false;
	cliente.enviar("login");
	cliente.enviar(usuario.id);
	cliente.enviar(usuario.clave);
	string temp = cliente.recibir();
	if(!temp.compare("yes"))
	{
		resultado = true;
		obtener_usuario(usuario);
	}
	else
		resultado = false;
	return resultado;

}

void obtener_usuario(Usuario &usuario)//recibe los datos
{
	cliente.enviar("obtener");
	cliente.enviar(usuario.id);
	usuario.nombre = cliente.recibir();
	usuario.saldo = cliente.recibir();
}

void enviar_usuario(Usuario &usuario)//envia los datos
{
	cliente.enviar("enviar");
	cliente.enviar(usuario.id);
	cliente.enviar(usuario.saldo);
}

void usuario_desconectado(Usuario &usuario)
{
	cliente.enviar("desconectar");
	cliente.enviar(usuario.id);
}

void usuario_consignar(Usuario &usuario)
{
	cliente.enviar("consignar");
	cliente.enviar(usuario.id);
	cliente.enviar(usuario.saldo);
}

void consultar_saldo(Usuario &usuario)
{
	lcd.borrar_pantalla();
	lcd.escribir("saldo actual");
	lcd.ubicar_cursor(1,2);
	lcd.escribir("$");
	lcd.escribir(usuario.saldo);
	lcd.gettecla();
}

long int retirar_saldo(Usuario &usuario)
{
	lcd.borrar_pantalla();
	lcd.escribir("$");
	string monto = lcd.print_monto();
	obtener_usuario(usuario);//actualiza usuario
	long int imonto = atoi(monto.c_str());
	long int saldo = atoi(usuario.saldo.c_str());
	long int resultado = saldo - imonto;
	if(resultado < 0)//si es menos
	{
		lcd.borrar_pantalla();
		lcd.escribir("saldo");
		lcd.ubicar_cursor(1,2);
		lcd.escribir("insuficiente");
		lcd.gettecla();
		imonto = 0;
	}
	else
	{
		stringstream ss;
		ss << resultado;
		usuario.saldo = ss.str();
		enviar_usuario(usuario);
	}
	return imonto;
}

void consignar_saldo(Usuario &usuario)
{
	lcd.borrar_pantalla();
	lcd.escribir("$");
	string monto = lcd.print_monto();
	obtener_usuario(usuario);//actualiza usuario
	long int imonto = atoi(monto.c_str());
	long int saldo = atoi(usuario.saldo.c_str());
	long int resultado = saldo + imonto;

	stringstream ss;
	ss << resultado;
	usuario.saldo = ss.str();
	enviar_usuario(usuario);
}

void transferir_saldo(Usuario &usuario)
{
	Usuario user2;
	bool salir = false;
	while(!salir)
	{
		lcd.borrar_pantalla();
		lcd.escribir("Cuenta");
		lcd.ubicar_cursor(1,2);
		user2.id = lcd.print_numero();
		if(!user2.id.compare("00000"))//sale al menu con 00000
			salir = true;
		else
		{
			if(verificar_usuario(user2))//si existe
			{
				long int monto = retirar_saldo(usuario);
				if(monto != 0)//si se puede transferir
				{	
					stringstream ss;
					ss << monto;
					user2.saldo = ss.str();
					consignar_saldo(user2);
					salir = true;
				}				
			}
			else
			{
				lcd.borrar_pantalla();
				lcd.escribir("datos erroneos");
				lcd.gettecla();
			}
		}
	}
	
}

void salir(Usuario &usuario)
{
	lcd.borrar_pantalla();
	lcd.escribir("Gracias");
	usuario_desconectado(usuario);
	sleep(2);
}

