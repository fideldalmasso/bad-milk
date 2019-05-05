#include <iostream>
#include <chrono> 
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "frical.h"
#include "funciones_utiles.h"
#include "ranking.h"

#define ANCHO 125

#if defined (_WIN32) || defined (WIN32)
	#include <windows.h>
#endif


using namespace std;

void frical(); 
void instrucciones_frical(); //Procedimiento que contiene las instrucciones sobre cómo jugar al "FRICAL".
void jugarfrical();//Procedimiento del juego "en si mismo"

void frical() {
	
	char selector;				
	
	color("blanco");
	
	//Estructura repetitiva que contiene al menu del juego (consta de 3 opciones: 1.jugar, 2.instrucciones y 3.salir). 
	do {
		resize(ANCHO,33);
		limpiar_pantalla();
		
		gotoxy(0,7);
		centrar("- Categor"+s('í')+"a juegos num"+s('é')+"ricos -\n");
		
		leerarchivo("frical_titulo.txt", rojo);
		
		cout << "\n\n";
		dormir(300);
		colorear("amarillo",s('¡')+"Presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!\n");
		dormir(200);
		centrar("1."+s('¡')+"A jugar!");
		dormir(200);
		centrar("2."+s('¿')+"C"+s('ó')+"mo se juega?");
		dormir(200);
		colorear("rojo","9. Volver al men"+s('ú')+" de juegos");
		
		
		gotoxy(62,26);
		cin >> selector;
		
		//Estructura repetitiva que valida el ingreso de un valor válido.
		while (selector != '1' and selector != '2' and selector != '9') {
			gotoxy(0,21);
			colorear("amarillo",s('¡')+"PSSS, presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!");
			gotoxy(62,26);
			centrar("                    ");
			gotoxy(62,26);
			cin >> selector;
		}
		
		limpiar_pantalla();
		
		//Estructura de selección múltiple que permite elegir entre las opciones del menu.
		switch (selector){
		case '1':
			jugarfrical ();
			mostrar_rank(1);
			break;
		case '2':
			instrucciones_frical ();
			break;
		}
		
		
	} while (selector != '9');
	
}

void jugarfrical () {
//	srand(time(NULL));
	auto comienzo = chrono::steady_clock::now();
	
	int numeroAleatorio = (rand() % 100) + 1; //Variable donde se almacena el número que debe adivinarse.
	int numeroIngresado; //Variable donde se almacena el/los valores ingresado/s por el usuario.
	int intento = 0; //Variable que contabiliza el número de intento.
	int puntos = 10; //Variable que contabiliza el puntaje del jugador en todo momento.
	
	cout << "\n";
	centrar(" Para comenzar a jugar ingrese un n"+s('ú')+"mero entre 1 y 100.\n");
	
	do {
		intento++; //Se incrementa el contador de intentos por cada intento realizado.
		
		//Estructura repetitiva que valida la entrada de valores enteros comprendidos entre 1 y 100 (incluidos).
		do {
			centrar("Intento "+to_string(intento)+": ",0);
			cin >> numeroIngresado;
			if (numeroIngresado < 1 or numeroIngresado > 100) {
				colorear("rojo", "Por favor ingrese un n"+s('ú')+"mero entre 1 y 100.");
				
			}
			
		} while (numeroIngresado < 1 or numeroIngresado > 100);
		
		
		int duracion = (chrono::steady_clock::now() - comienzo)/chrono::seconds(1);
		
		//Estructura de selección que evalúa las diferentes situaciones que pueden darse.
		if (numeroIngresado == numeroAleatorio) { //Este "if" ejecuta las sentencias a realizar en caso de que se haya encontrado el número aleatorio (cuando el jugador gana).
			colorear(verde,s('¡')+"Acertaste!"+s('¡')+"Has ganado!");
			centrar("Puntaje obtenido: "+to_string(puntos));
			guardar_partida(1,puntos,-1,1,duracion);
			
		} else { //Dentro de este "else" se ejecutan las sentencias a ralizar en caso de que no se haya encontrado el número aleatorio.
			puntos -- ; //Como el valor ingresado es diferente al buscado, el puntaje del jugador decrementra 1 punto.
			if (numeroIngresado < numeroAleatorio) { //Dentro de este "if" se ejecutan las sentencias en caso de que el numero ingresado sea menor al buscado.
				colorear(celeste,s('¡')+"Est"+s('á')+"s fr"+s('í')+"o!") ;
				centrar("Se te descuenta 1 punto, te quedan "+to_string(puntos)+" intentos.");
			} 
			else { //Dentro de este "else" se ejecutan las sentencias en caso de que el numero ingresado sea mayor al buscado.
				colorear(rojo,s('¡')+"Est"+s('á')+"s caliente!");
				centrar("Se te descuenta 1 punto, te quedan "+to_string(puntos)+" intentos.");
			}
			if (intento == 10) { //Dentro de este "if" se ejecutan las sentencias en caso de que ya se hayan agotado todos los intentos (cuando el jugador pierde).
				cout << "\n";
				colorear(rojo, s('¡')+"Perdiste!¡M"+s('á')+"s suerte la pr"+s('ó')+"xima! El n"+s('ú')+"mero que buscabas era "+to_string(numeroAleatorio)+".\n") ;
				guardar_partida(1,0,-1,0,duracion);
			}
		}
		centrar(" ----------------------------------------------------------------\n");
		
	} while (numeroIngresado!=numeroAleatorio and intento < 10);
	
	//Para volver al menu se solicita que presione una tecla.
	pausa(1);
	
}

void instrucciones_frical () {
	limpiar_pantalla();
	cout << "\n";
	centrar("INSTRUCCIONES\n");
	leerarchivo("frical_instrucciones.txt");
	cout << "\n";
	pausa(1);
	limpiar_pantalla();
}
