#include <iostream>
#include <chrono> 
#include <time.h>
#include <string.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cctype>

#include "pares.h"
#include "funciones_utiles.h"
#include "ranking.h"

#define ANCHO 106

#if defined (_WIN32) || defined (WIN32)
	#include <conio.h>
	#include <windows.h>
#endif
using namespace std;

struct coordenada{
	int fila;
	int columna;
}punto1,punto2;

void pares();
void jugarpares(bool modo);
void generarmatriz(char TABLERO[6][6]);
void mostrartablero(char TABLERO[6][6], bool DESCUBIERTO[6][6]);
void ingreso(int &fila, int &columna, bool DESCUBIERTO[6][6], char TABLERO[6][6], int eleccion);
void mostrarlista(char TABLERO[6][6], bool DESCUBIERTO[6][6]);
void mostrarelemento(int fila, int columna, char TABLERO[6][6]);


void pares() {
	limpiar_pantalla();
	resize(ANCHO,35);
	color("blanco");
//	srand(time(NULL));
	
	
	char opcion;
	bool modografico;
	
	gotoxy(0,17);
	dormir(200);
	colorear(amarillo,"Elige el modo de juego");
	dormir(200);
	centrar("1. Modo gr" + s('á') + "fico");
	dormir(200);
	centrar("2. Modo texto (accesibilidad)");
	dormir(200);
	
	do{
		
		gotoxy(53,25);
		cout << "  ";
		gotoxy(53,25);
		cin >> opcion;
		
		if(opcion=='1')
			modografico = true;
		if(opcion=='2')
			modografico = false;
		
		if(opcion!='1' and opcion!='2'){
			colorear(amarillo,"Se ha ingresado un n" + s('ú') + "mero incorrecto, intente nuevamente");
		}
	} while(opcion!='1' and opcion!='2');
	
	
	do{
		limpiar_pantalla();
		resize(ANCHO,35);
		gotoxy(0,4);
		
		if(modografico){
		gotoxy(0,3);
		centrar(" - Categor"+s('í')+"a juegos con tablas -\n");
		color("violeta");
		leerarchivo("pares_titulo.txt");
		}
		cout << "\n\n";
		dormir(300);
		colorear("amarillo",s('¡')+"Presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!\n");
		dormir(200);
		centrar("1."+s('¡')+"A jugar!");
		dormir(200);
		centrar("2."+s('¿')+"C"+s('ó')+"mo se juega?");
		dormir(200);
		colorear("rojo","9. Volver al men"+s('ú')+" de juegos");
		
		gotoxy(53,32);
		cin >> opcion;
		
		while(opcion!='1' and opcion!='2' and opcion!='9'){
			gotoxy(0,27);
			colorear("amarillo",s('¡')+"PSSS, presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!");
			gotoxy(0,32);
			centrar("                    ");
			gotoxy(53,32);
			cin >> opcion;
		}
		
		limpiar_pantalla();
		
		switch(opcion){
		case '1':
			jugarpares(modografico);
			break;
		case '2':
			limpiar_pantalla();
			cout << "\n";
			centrar("INSTRUCCIONES\n");
			leerarchivo("pares_instrucciones.txt");
			cout << "\n";
			pausa(1);
			limpiar_pantalla();
			break;
		}
		
	} while(opcion!='9');
}


void jugarpares(bool modo){
	
	auto comienzo = chrono::steady_clock::now();
	
	int puntaje = 100;
	char TABLERO[6][6];
	bool DESCUBIERTO[6][6];
	bool victoria = false;
	int jugada = 1;
	int acertadas = 0;
	generarmatriz(TABLERO);
	
	
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			DESCUBIERTO[i][j] = false;
		}
	}
	
	
	// aquí comienza el juego
	
	
	while(puntaje!=0 and !victoria){
		
		if(acertadas>5){
			
			
			resize(106,35+acertadas*2-10);
		}
		
		limpiar_pantalla();
		gotoxy(0,0);
		
		color("verde2");
		cout << "JUGADA #" << jugada << ":" << endl;
		cout << "PUNTOS : " << puntaje;
		color("blanco");
		
		if(modo){
			mostrartablero(TABLERO,DESCUBIERTO);
		}
		
		
		
		if(jugada>1 and !modo){
			gotoxy(0,8);
			colorear(violeta,"Si lo deseas, puedes presionar la tecla V para visualizar la lista de posiciones ya descubiertas",0);
		
		}
		jugada++;
		
		gotoxy(0,13);
		cout << "Ingrese coordenada 1 a mostrar: ";
		ingreso(punto1.fila, punto1.columna, DESCUBIERTO, TABLERO, 1);
		
		gotoxy(0,14);
		cout << "                                                                         ";
		cout << "                                                                         ";
		
		
		DESCUBIERTO[punto1.fila][punto1.columna] = true;
		
		if(modo){
			mostrartablero(TABLERO, DESCUBIERTO);
		}
		else{
			gotoxy(0,3);
			mostrarelemento(punto1.fila, punto1.columna, TABLERO);
		}
		DESCUBIERTO[punto1.fila][punto1.columna] = false;
		
		gotoxy(0,16);
		cout << endl << "Ingrese coordenada 2 a mostrar: ";
		bool error;
		do{
			error = false;
			ingreso(punto2.fila, punto2.columna, DESCUBIERTO,TABLERO, 2);
			if (punto1.fila == punto2.fila and punto1.columna == punto2.columna){
				gotoxy(0,18);
				colorear(amarillo, "Las coordenadas ingresadas son iguales                                                 ",0);
				cout << "                                               ";
				error = true;
			}
		}while(error);
		gotoxy(0,18);
		cout << "                                                                         \n";
		cout << "                                                                         ";
		
		DESCUBIERTO[punto1.fila][punto1.columna] = true;
		DESCUBIERTO[punto2.fila][punto2.columna] = true;
		
		if(modo){
			mostrartablero(TABLERO, DESCUBIERTO);
		}
		else{
			gotoxy(0,5);
			mostrarelemento(punto2.fila, punto2.columna, TABLERO);
		}
		gotoxy(0,21);
		dormir(100);
		
		if(TABLERO[punto1.fila][punto1.columna] == TABLERO[punto2.fila][punto2.columna]-32 or TABLERO[punto1.fila][punto1.columna] == TABLERO[punto2.fila][punto2.columna]+32){
			
			colorear(verde, s('¡')+"Acertaste!",0);
			acertadas++;
		}
		else{
			DESCUBIERTO[punto1.fila][punto1.columna] = false;
			DESCUBIERTO[punto2.fila][punto2.columna] = false;
		
			colorear(rojo,s('¡')+"Fallaste! Se te descuentan 5 puntos",0);
			puntaje-=5;
			
		}
		
		pausa();
		if(acertadas==18){
			victoria = true;
		}
		
	}
	
	limpiar_pantalla();
	resize(106,35);
	
	int duracion = (chrono::steady_clock::now() - comienzo)/chrono::seconds(1);	
	
	if(victoria){
		guardar_partida(6,puntaje,-1,1,duracion);
		if(modo){

		leerarchivo("pares_victoria.txt",verde);

		
		}
		
		else{
			colorear(verde,s('¡')+"Ganaste! Felicitaciones",0);
		}
		
	}
	else{
		guardar_partida(6,puntaje,-1,0,duracion);
		if(modo){
		leerarchivo("pares_juegoterminado.txt");
		}
		else{
			colorear(rojo,s('¡')+"Fallaste! ¡Pero no te desanimes!",1);
		}
		
	}
	pausa();
	mostrar_rank(6);
	
}
void generarmatriz(char TABLERO[6][6]){
	char letrasposibles[26];
	char letra = 'A';
	int TL = 26;
	
	for(int i=0; i<26; i++){                                 // genero un arreglo de 25 elementos que contiene todas las letras del abecedario.
		letrasposibles[i] = letra;
		letra++;
	}
	
	
	
	for(int i=0; i<8; i++){                                  // elimino aleatoriamente 7 elementos, quedando así 18 posibles letras para llenar mi TABLERO.
		int posicion = rand()%(TL);
		
		while(posicion!=(TL-1)){
			letrasposibles[posicion]=letrasposibles[posicion+1];
			posicion++;
		}
		TL--;
	}
	
	
	int posicion = 0;
	for (int i=0; i<6 and posicion!=TL; i++){                // copio los 18 valores generados en mi TABLERO, uno tras otro.
		for(int j=0; j<6 and posicion!=TL; j++){
			TABLERO[i][j] = letrasposibles[posicion];
			TABLERO[i+3][j] = (letrasposibles[posicion]+32); // copio la versión minúscula de cada una de mis letras generadas, uno tras otra.
			posicion++;
		}
	}
	
	cout << endl << endl;
	
	for (int i=0; i<6; i++){                                 // desordeno mi TABLERO
		for(int j=0; j<6; j++){
			char aux = TABLERO[i][j];
			int i2= rand()%6;
			int j2 = rand()%6;
			TABLERO[i][j] = TABLERO[i2][j2];
			TABLERO[i2][j2] = aux;
		}
	}
	
}

void mostrartablero(char TABLERO[6][6], bool DESCUBIERTO[6][6]){
	
	gotoxy(46,3);
	char letra='A';
	cout << "   1 2 3 4 5 6" << endl << endl; 
	int altura = 4;
	for (int i=0; i<6; i++){	
		
		gotoxy(46,altura);
		altura++;
		cout << letra << "  ";
		for(int j=0; j<6; j++){
			
			if(DESCUBIERTO[i][j]){
				color("verde");
				cout << TABLERO[i][j] << " ";
				color("blanco");
			}
			else{
				cout << "? ";
			}
			
		}
		letra++;
		
	}
	
}
void ingreso(int &fila, int &columna, bool DESCUBIERTO[6][6], char TABLERO[6][6], int eleccion){
	
	bool error; 
	do{
		error = false;
		
		do{                                                 //el código siguiente se ocupa del ingreso de fila (letra)
			
			if(eleccion==1){                                 //si eleccion=1 significa que estamos pidiendo la primer coordenada
				gotoxy(32,13);
				cout << "  " ;
				gotoxy(32,13);
			}
			else{
				gotoxy(32,17);                               //si eleccion=0 significa que estamos pidiendo la segunda coordenada
				cout << "  " ;
				gotoxy(32,17);
			}
			fila = getchx();                                  //al usar getch(), no hace falta apretar enter después de ingresar la letra 
			if(islower(fila))
				fila = toupper(fila);
			cout << char(fila);                             //necesito de un cout para mostrar el caracter
			if(fila==86){                                   //86 es el ascii correspondiente a la letra V
				mostrarlista(TABLERO,DESCUBIERTO);        // se ejecuta cuando el usuario ingresa V por teclado
			}
		}while(fila==86);
		fila -= 65;                                     //al restarle 65, lo interpreto como un número 
		
		do{                                                 //el código siguiente se ocupa del ingreso de columna (número)
			if(eleccion==1){
				gotoxy(33,13);
				cout << "  " ;
				gotoxy(33,13);
			}
			else{
				gotoxy(33,17);
				cout << "  " ;
				gotoxy(33,17);
			}
			columna = getchx();
			cout << char(columna);
			if(columna==86){
				mostrarlista(TABLERO,DESCUBIERTO);
			}
		}while(columna==86);
		
		columna-=49;                                        //le restamos 49 porque al usar getch() recibimos el ascii de un número y no el número en si
		
		if(columna<0 or columna>5 or fila<0 or fila>5){
			error = true;
			color("amarillo");
			cout << endl << "Se ha ingresado una coordenada incorrecta, por favor, intente nuevamente         " << endl;
//			cout << "Record"<<s('á')<<" siempre usar letras may"<<s('ú')<<"sculas " << endl;
			color("blanco");
		}
		else if(DESCUBIERTO[fila][columna]==true){
			error = true;
			color("amarillo");
			cout  << endl << "La coordenada ingresada ya ha sido acertada, por favor, ingrese una diferente       " << endl;
			cout << "                                               ";
			color("blanco");
		}
		
	} while(error);
}
void mostrarlista(char TABLERO[6][6], bool DESCUBIERTO[6][6]){
	
	
	bool acertado = false;
	gotoxy(0,24);
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			if(DESCUBIERTO[i][j]){
				acertado = true;
				cout << "- En la posici"<<s('ó')<<"n (" << (char)(i+65) <<"," <<  j+1 << ") se ha encontrado la letra " << TABLERO[i][j];
				if(TABLERO[i][j]>64 and TABLERO[i][j]<91){
					cout <<"(may"<<s('ú')<<"scula)." << endl;
				}
				else{
					cout <<"(min"<<s('ú')<<"scula)." << endl;
				}
			}
		}
	}
	if(!acertado){
		cout << "Todav"<<s('í')<<"a no has encontrado ninguna pareja" << endl;
	}
	gotoxy(0,0);
}


void mostrarelemento(int fila, int columna, char TABLERO[6][6]){
	
	cout << "- En la posici"<<s('ó')<<"n (" << (char)(fila+65) <<"," <<  columna+1 << ") se ha encontrado la letra " << TABLERO[fila][columna];
	if(TABLERO[fila][columna]>64 and TABLERO[fila][columna]<91){
		cout <<"(may"<<s('ú')<<"scula)." << endl;
	}
	else{
		cout <<"(min"<<s('ú')<<"scula)." << endl;
	}
}
