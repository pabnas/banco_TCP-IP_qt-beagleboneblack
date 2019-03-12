

#include <iostream>
#include <stdlib.h>   
#include <time.h> 
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <list>
#include <stdio.h>


#include <termios.h>//kbhit
#include <fcntl.h>//kbhit

#include "../include/Comandos_generales.h"

using namespace std;

float Random()
{
	float z;
	struct timeval start;
	//struct end;
    //long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);
    srand(start.tv_usec);
 

    z=(float)rand()/RAND_MAX;
    return z;
}

double DoubleRandom()
{
	double z;
	struct timeval start;    
    gettimeofday(&start, NULL);
    srand(start.tv_usec);
 

    z=(double)rand()/RAND_MAX;
    return z;
}


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

void Ubicar_cursor(int linea,int palabra,FILE *Archivo)
{
	char Linea[1024];
	fseek(Archivo, 0 , SEEK_SET);
	for(int a = 0;a < linea-1; a++)//se ubica en la linea
		fgets(Linea,1024,Archivo);
	for(int a = 0;a < palabra;a++)//se ubica en la palabra
		fscanf(Archivo, "%s" , Linea);
}

/*int Buscar_palabra(string Palabra,FILE *Archivo)
{
	string Linea;
	int resultado = -1;
	for(int nlinea = 0;nlinea != feof(Archivo);nlinea++)
	{		
		for(int palabra = 0;palabra < 1024; palabra++)
		{
			Ubicar_cursor(nlinea,palabra,Archivo);
			fscanf(Archivo,"%s",Linea);
			if(!Linea.compare(Palabra))
				resultado = nlinea;
		}
	}	
	return resultado;
}*/

int numDigits(int number)
{
	int no=number,a=0;
	if(no<0)
	{
		no=no * -1;
	}
	else if(no==0)
	{
		no=1;
	}
	while(no>0)
	{
		no=no/10;
		a++;
	}
	if(number < 0)
		a++;
	return a;
}
void Imprimir_campo(int valor,int campo)
{
	int digitos = numDigits(valor);
	int margen1,margen2,margen;
	margen = campo - digitos;
	margen1 = margen/2;
	margen2 = margen - margen1;
	
	for(int a = 0; a != margen1 ; a++)
		printf(" ");
	printf("%d",valor);
	for(int a = 0; a != margen2 ; a++)
		printf(" ");	
	
}

