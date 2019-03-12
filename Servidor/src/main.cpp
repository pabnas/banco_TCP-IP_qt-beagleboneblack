#include "main.h"

int main(int argc, char * argv[])
{
	pthread_mutex_init(&mutex_archivos,NULL);
	pthread_mutex_init(&mutex_conectado,NULL);
	pthread_mutex_init(&mutex_stream,NULL);	
	pthread_mutex_init(&mutex_consig,NULL);
	system("clear");
	server.conectar();
	printf("Inicio del server\n");
	while(1)
	{
		server.esperar_cliente();
		pthread_t atender_cliente;
		pthread_create(&atender_cliente,NULL,Atender_cliente,NULL);	
		//Atender_cliente();		
		usleep(10);
	}
	server.desconectar();
	exit(0);
}

void *Atender_cliente(void *a)
{
	printf("\n\nAtendiendo cliente\n");

	pthread_mutex_lock(&mutex_stream);
	conexion server_cliente = server;
	
	string respuesta = server_cliente.recibir();
	printf("%s\n",respuesta.c_str());

	if(!respuesta.compare("verificar"))
	{
		string usuario_id = server_cliente.recibir();
		//printf("%s\n",usuario_id.c_str());
		bool res = verificar(usuario_id);
		if(res)
			server_cliente.enviar("yes");
		else
			server_cliente.enviar("no");
	}
	else if(!respuesta.compare("login"))
	{
		string id = server_cliente.recibir();
		printf("%s\n",id.c_str());
		string clave = server_cliente.recibir();
		printf("%s\n",clave.c_str());
		bool blogin = login(id,clave);
		if(blogin)
			server_cliente.enviar("yes");
		else
			server_cliente.enviar("no");
	}
	else if(!respuesta.compare("obtener"))
	{
		User usuario;
		usuario.id = server_cliente.recibir();
		//printf("%s\n",usuario.id.c_str());
		cargar_usuario(usuario);
		server_cliente.enviar(usuario.nombre);
		server_cliente.enviar(usuario.saldo);
	}
	else if(!respuesta.compare("enviar"))
	{
		User usuario;
		usuario.id = server_cliente.recibir();
		//printf("%s\n",usuario.id.c_str());
		cargar_usuario(usuario);
		usuario.saldo = server_cliente.recibir();		
		descargar_usuario(usuario);
	}
	else if(!respuesta.compare("desconectar"))
	{
		User usuario;
		usuario.id = server_cliente.recibir();
		//printf("%s\n",usuario.id.c_str());
		cargar_usuario(usuario);
		usuario.conectado = "0";
		descargar_usuario(usuario);
	}
	else if(!respuesta.compare("consignar"))
	{
		//pthread_mutex_lock(&mutex_consig);
		User usuario;
		usuario.id = server_cliente.recibir();
		//printf("%s\n",usuario.id.c_str());
		cargar_usuario(usuario);
		string saldo_adicional = server_cliente.recibir();
		//printf("%s\n",saldo_adicional.c_str());
		//agregar saldo
		long int Isaldo = atoi(usuario.saldo.c_str());
		long int monto = atoi(saldo_adicional.c_str());
		long int resultado = Isaldo + monto;
		
		stringstream ss;
		ss << resultado;
		usuario.saldo = ss.str();
		
		descargar_usuario(usuario);		
		//pthread_mutex_unlock(&mutex_consig);
	}	
	else if(!respuesta.compare("cambio_clave"))
	{		
		string id = server_cliente.recibir();
		string clave = server_cliente.recibir();
		User usuario_clave;
		usuario_clave.id = id;
		cargar_usuario(usuario_clave);
		usuario_clave.clave = clave;
		descargar_usuario(usuario_clave);
	}
	else if(!respuesta.compare("crear"))
	{
		string carpeta = server_cliente.recibir();
		string Rarchivo = server_cliente.recibir();

		mkdir(carpeta.c_str(), 0700);

		ifstream my_file("test.txt");
		my_file.open(Rarchivo.c_str());
		if(my_file.fail())
		{
			server_cliente.enviar("yes");
			string nombre = server_cliente.recibir();
			string clave = server_cliente.recibir();
			string tipo = server_cliente.recibir();
			
			FILE * pFile;
			pFile = fopen (Rarchivo.c_str(),"w");
			fprintf(pFile,"conectado\n");
			fprintf(pFile,"0\n\n");
			fprintf(pFile,"clave\n");
			fprintf(pFile,"%s\n\n",clave.c_str());
			fprintf(pFile,"saldo\n");
			fprintf(pFile,"0\n\n");
			fprintf(pFile,"nombre\n");
			fprintf(pFile,"%s\n\n",nombre.c_str());
			fprintf(pFile,"tipo\n");
			fprintf(pFile,"%s\n\n",tipo.c_str());
			fclose (pFile);
			
			string info = server_cliente.recibir();
			string edad = server_cliente.recibir();
			string telefono = server_cliente.recibir();
			
			pFile = fopen (info.c_str(),"w");
			fprintf(pFile,"Nombre\n");
			fprintf(pFile,"%s\n\n",nombre.c_str());
			fprintf(pFile,"Edad\n");
			fprintf(pFile,"%s\n\n",edad.c_str());
			fprintf(pFile,"Telefono\n");
			fprintf(pFile,"%s\n\n",telefono.c_str());
			fprintf(pFile,"Cuentas\n\n");
			fclose(pFile);

			string comando1 = server_cliente.recibir();
			system(comando1.c_str());
			usleep(1000);
			string comando2 = server_cliente.recibir();
			system(comando2.c_str());

			system("ls ../Usuarios/ | wc -l > ../Usuarios/info.txt");
			usleep(1000);
			system("ls ../Usuarios/ >> ../Usuarios/info.txt");
		}
		else
			server_cliente.enviar("no");		
	}
	
	pthread_mutex_unlock(&mutex_stream);
	pthread_exit(NULL);	
}

bool verificar(string id)
{
	bool resultado = false;
	pthread_mutex_lock(&mutex_archivos);

	string carpeta = Buscar_id(id);
	
	pthread_mutex_unlock(&mutex_archivos);
	
	if(carpeta.compare("NULL"))//si encontro la carpeta
	{
		pthread_mutex_lock(&mutex_archivos);
		string ruta = "../Usuarios/" + carpeta + "/" + id + ".txt";
	
		ifstream my_file("test.txt");
		my_file.open(ruta.c_str());
		pthread_mutex_unlock(&mutex_archivos);

		if(my_file.fail())
			resultado = false;		// error! maybe the file doesn't exist.
		else
			resultado = true;
	}
	
	return resultado;
}

bool login(string id,string clave)
{
	pthread_mutex_lock(&mutex_conectado);
	bool resultado = false;
	User usuario;
	usuario.id = id;
	cargar_usuario(usuario);
	//printf("1) %s==%s %s  %s\n",usuario.clave.c_str(),clave.c_str(),usuario.conectado.c_str(),id.c_str());
	
	//if(!usuario.clave.compare(clave)&(!usuario.conectado.compare("0")))//si la clave es correcta y esta desconectado
	if(!usuario.clave.compare(clave))
	{
		//printf("2)\n");
		resultado = true;
		usuario.conectado = "1";
		descargar_usuario(usuario);
	}
	pthread_mutex_unlock(&mutex_conectado);
	return resultado;	
}

void cargar_usuario(User &usuario)
{
	pthread_mutex_lock(&mutex_archivos);
	string carpeta = Buscar_id(usuario.id);	
	
	FILE * pFile;
	char Linea[1024];
	string ruta = "../Usuarios/" + carpeta + "/" + usuario.id + ".txt";
	pFile = fopen (ruta.c_str(),"r");
	
	Ubicar_cursor(2,0,pFile);//conectado
	fscanf(pFile, "%s" , Linea);
	string tconectado(Linea);

	usuario.conectado = tconectado;
	
	Ubicar_cursor(5,0,pFile);//clave
	fscanf(pFile, "%s" , Linea);
	string tclave(Linea);
	usuario.clave = tclave;

	Ubicar_cursor(8,0,pFile);//saldo
	fscanf(pFile, "%s" , Linea);
	string tsaldo(Linea);
	usuario.saldo = tsaldo;

	Ubicar_cursor(11,0,pFile);//nombre
	fscanf(pFile, "%s" , Linea);
	string tnombre(Linea);
	usuario.nombre = tnombre;

	Ubicar_cursor(14,0,pFile);//edad
	fscanf(pFile, "%s" , Linea);
	string ttipo(Linea);
	usuario.tipo = ttipo;
	fclose (pFile);
	pthread_mutex_unlock(&mutex_archivos);
}

void descargar_usuario(User &usuario)
{
	pthread_mutex_lock(&mutex_archivos);	
	string carpeta = Buscar_id(usuario.id);
	
	FILE * pFile;	
	string ruta = "../Usuarios/" + carpeta + "/" + usuario.id + ".txt";
	pFile = fopen (ruta.c_str(),"w");
	fprintf(pFile,"conectado\n");
	fprintf(pFile,"%s\n\n",usuario.conectado.c_str());
	fprintf(pFile,"clave\n");	
	fprintf(pFile,"%s\n\n",usuario.clave.c_str());
	fprintf(pFile,"saldo\n");	
	fprintf(pFile,"%s\n\n",usuario.saldo.c_str());	
	fprintf(pFile,"nombre\n");	
	fprintf(pFile,"%s\n\n",usuario.nombre.c_str());
	fprintf(pFile,"tipo\n");	
	fprintf(pFile,"%s\n\n",usuario.tipo.c_str());
	fclose (pFile);
	pthread_mutex_unlock(&mutex_archivos);
}

void actualizar_info_general()
{
	system("ls ../Usuarios/ | wc -l > ../Usuarios/info.txt");
	usleep(50000);
	system("ls ../Usuarios/ >> ../Usuarios/info.txt");
	usleep(50000);
}

string Buscar_id(string id)
{
	actualizar_info_general();
	FILE* Archivo;
	char Linea[1024];
	id = "/" + id + ".txt";

	string resultado = "NULL";
	
	
	Archivo = fopen("../Usuarios/info.txt","r");
	fseek(Archivo, 0 , SEEK_SET);
	fscanf(Archivo,"%s",Linea);
	int numero_de_carpetas = atoi(Linea);//obtenemos el numero de usuarios

	for(int i = 0;i < numero_de_carpetas;i++)
	{		
		fscanf(Archivo, "%s" , Linea);//lee la carpeta
		string carpeta(Linea);
		if(carpeta.compare("info.txt"))//si no es info.txt
		{
			string ruta = "../Usuarios/" + carpeta + id;
			//printf("%s\n",ruta.c_str());
			ifstream my_file("test.txt");
			my_file.open(ruta.c_str());
			if(!my_file.fail())//si esta
				resultado = carpeta;
		}
	}
	fclose(Archivo);
	return resultado;
}






