#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cstring>

#include "funciones_utiles.h"

#if defined (_WIN32) || defined (WIN32)
	#define windows
	#include <windows.h>
	#include <conio.h>

#else
	#define linuxx
	#include <unistd.h>
	#include <termios.h>
	#include <unistd.h>
	#include <stdio.h>
#endif

using namespace std;

int ANCHOGLOBAL;
string const blanco="blanco", rojo="rojo", amarillo="amarillo", celeste="celeste", gris = "gris";
string const verde="verde", violeta="violeta", verde2="verde2", azul="azul";


void color(string color);
void colorear(string color1,string texto, int centrado, int salto);
void resize(int anchura, int altura); 			//para cambiar el tamaño de la terminal
void gotoxy(int x, int y);
void pausa(bool centrado);								//detiene el programa hasta que se toque una tecla
void limpiar_pantalla();
void dormir(int milisegundos);				//adaptación de la funcion Sleep
char getchx();								//adaptación de getch()
string s(char letra);						//permite mostrar letras con tilde y caracteres especiales
void centrar(string cadena, int salto);
void leerarchivo(string nombre, const string & color, int velocidad);
void bienvenida();
int contar_lineas(string nombre);

//funciones visuales
void color(string color){	
#ifdef windows

	if (color=="blanco")
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),15);
	
	else if (color=="rojo")
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12);
	
	else if (color=="amarillo")
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),14);
	
	else if (color=="verde")
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),10);
	
	else if (color=="violeta")
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),13);
	else if(color=="verde2")
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),3);
	else if(color=="azul")
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),9);
	else if(color=="celeste"){
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),11);
	}
	else if(color=="gris"){
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),8);
	}
	
	
#else
	
	if (color=="blanco")
		cout << "\033[1;37m";
	
	else if (color=="rojo")
		cout << "\033[1;31m";
	
	else if (color=="amarillo")
		cout << "\033[33m";
	
	else if (color=="verde")
		cout << "\033[1;32m";
	
	else if (color=="violeta")
		cout << "\033[1;35m";
	
	else if(color=="verde2")
		cout << "\033[36m";
	
	else if(color=="azul")
		cout << "\033[1;34m";
	
	else if(color=="celeste")
		cout << "\033[1;36m";
	
	else if(color=="gris")
		cout << "\033[1;90m";
#endif
}

void colorear(string color1,string texto, int centrado, int salto){ 
	//centrado y salto son parámetros opcionales en la siguiente función
	if(centrado==1){
		color(color1);
		centrar(texto, salto);
		color("blanco");
	}
	else{							
		//si le paso algo distinto de 1 como parametro, no centra el texto
		color(color1);
		cout << texto;
		if (salto==1){
			cout << endl;
		}
		color("blanco");
	}
}

void resize(int anchura, int altura){
	ANCHOGLOBAL = anchura;
#ifdef windows	
	string cadena = "mode con: cols=" + to_string(anchura) + " lines=" + to_string(altura);
	system(cadena.c_str());		
#endif
}
void gotoxy(int x, int y){
#ifdef windows
	COORD cp;
	cp.X = x;
	cp.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
#else 
	printf("%c[%d;%df",0x1B,y+1,x);

#endif
}

void limpiar_pantalla(){
	
#ifdef windows
	system("CLS");
	
#else
	cout << "\033[2J\033[1;1H";
	
#endif
	gotoxy(0,0);
}

void dormir(int milisegundos){
#ifdef windows
	Sleep(milisegundos);
	
#else
	usleep(milisegundos*1000);
	// porque trabaja en microsegundos
	
#endif
}



string s(char letra){

	char x=letra;

	switch(letra){
		
		case -31: x = char(160); 
		break;
		case -23: x = char(130); 
		break;
		case -19: x = char(161); 
		break;
		case -13: x = char(162); 
		break;
		case -6: x = char(163); 
		break;
		case -15: x = char(164);
		break;
		case -95: x = char(173);
		break;
		case -80: x = char(248);
		break;
		case -65: x = char(168);
		break;
		case -63: x = char(181);
		break;
		case -55: x = char(144);
		break;
		case -51: x = char(214);
		break;
		case -45: x = char(224);
		break;
		case -38: x = char(233);
	
	}	
	
	string f(1,x);
	return f;
}

void centrar(string cadena, int salto){
	
	char * Ptexto = new char[ANCHOGLOBAL];
	
	
	//copio mi string en un arreglo de caracteres
	strcpy(Ptexto, cadena.c_str());
	
	int largo=strlen(Ptexto);
	
	int posicion=(int)((ANCHOGLOBAL-largo)/2);
	
	for(int i=0;i<posicion;i++){
		cout<<" ";
	}
	
	cout<< cadena;
	
	if (salto==1){
		cout << "\n";
	}
}
void leerarchivo(string nombre, const string & color, int velocidad){
	
	string cadena;
	ifstream archivo;
	archivo.open("data/text/"+nombre);
	
	
	char x;
	
	
	while(!archivo.eof()){
		archivo.get(x);
		
		if(x=='\n'){
			if(color=="ninguno")
				centrar(cadena);
			else
				colorear(color,cadena);
			if(velocidad==1)
				dormir(25);
			else
				dormir(velocidad);
			cadena = "";
		}
		else{
			cadena+=s(x);
		}
		
	}
	
	cadena[cadena.size()-1]='\0';
	
	if(color=="ninguno")
		centrar(cadena);
	else
		colorear(color,cadena);
	
	archivo.close();
}

//funciones prácticas
void bienvenida(){
	limpiar_pantalla();
	resize(60,30);
	gotoxy(0,10);
	//	centrar(s('¡')+ "Bienvenido!");
	color(blanco);
#ifdef windows
	gotoxy(0,9);
	//	centrar("Para visualizar los caracteres en forma correcta");
	centrar("Para una mejor experiencia, recomendamos usar");
	centrar("la fuente 'Lucida Console' en la ventana actual\n");
	colorear(amarillo,s('¿')+"C"+s('ó')+"mo lo hago?");
	centrar("Haciendo clic derecho en la barra superior de esta");
	centrar("ventana y seleccionando Propiedades > Fuente");
	
	
#else
	cout << "El programa se est"+s('á')+" ejecutando en un SO distinto de Windows" << endl;
	cout << "Por eso recomendamos: " << endl;
	cout << " => Correr el programa en pantalla completa" << endl;
	cout << " => Usar la terminal de xfce4" << endl;
	cout << " => Utilizar en esta ventana la configuraci"+s('ó')+"n de caracteres" << endl;
	cout << "    de la p"+s('á')+"gina de c"+s('ó')+"digos 850 (IBM850 o CP850)" << endl;
	
#endif
	gotoxy(0,25);
	pausa(1);
	limpiar_pantalla();
}

int contar_lineas(string nombre){		//de un archivo de texto
	int cantidad_lineas = 0;
	string linea;
	ifstream archivox(nombre);
	
	while (getline(archivox, linea))
		++cantidad_lineas;
	
	archivox.close();
	return cantidad_lineas;
}
void pausa(bool centrado){
	color("amarillo");
	if(!centrado){
		cout << "Presion"+s('á')+" una tecla para continuar                       " << '\r' ;
	}
	else{
		centrar("Presion"+s('á')+" una tecla para continuar");
	}
	
	getchx();
	cout << "                                 ";
	color("blanco");
	
}
char getchx(){
#ifdef windows
	return getch();
#else
	
	
	//ACLARACIÓN: el código a continuación no es de autoría propia, sino que fue extraído de 
	//https://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux/7469410
	
	char buf=0;
	struct termios old={0};
	fflush(stdout);
	if(tcgetattr(0, &old)<0)
		perror("tcsetattr()");
	old.c_lflag&=~ICANON;
	old.c_lflag&=~ECHO;
	old.c_cc[VMIN]=1;
	old.c_cc[VTIME]=0;
	if(tcsetattr(0, TCSANOW, &old)<0)
		perror("tcsetattr ICANON");
	if(read(0,&buf,1)<0)
		perror("read()");
	old.c_lflag|=ICANON;
	old.c_lflag|=ECHO;
	if(tcsetattr(0, TCSADRAIN, &old)<0)
		perror ("tcsetattr ~ICANON");
	
	return buf;
#endif
}
