#include<iostream>
#include <chrono> 
#include <ctime>

#include "funciones_utiles.h"
#include "ingreso_usuarios.h"
#include "encriptacion.h"
#include "ranking.h"
#include "estadisticas.h"
	#include "frical.h"
	#include "generala.h"
	#include "generala_avanzada.h"
	#include "pares.h"
	#include "pipati.h"
	#include "ahorcado.h"
	#include "batalla_naval.h"


#if defined (_WIN32) || defined (WIN32)
	#define windows
#else 
	#define linuxx
#endif
using namespace std;


#define ANCHO 60

void logo();
bool menu_principal();
void menu_juegos();
void menu_ranking();
void menu_creditos();
bool menu_opciones();

int main(){
	resize(ANCHO,30);

	bool seguir_jugando;

	auto comienzo = chrono::steady_clock::now();
	srand(time(NULL));

	logo();
	
	
#ifdef linuxx 
	bienvenida();
#endif
	
	do{
	seguir_jugando = menu_ingreso();
		if(seguir_jugando){
			seguir_jugando = menu_principal();
		}
		
	} while(seguir_jugando);

	limpiar_pantalla();
	gotoxy(0,10);
	colorear(verde,s('¡') + "Gracias por jugar!");
	int duracion = (chrono::steady_clock::now() - comienzo)/chrono::seconds(1);
	centrar("Duraci"+s('ó')+"n de la sesi"+s('ó')+"n: "+to_string(duracion/60)+ " minutos.");
	gotoxy(0,27);
	pausa();
	return 0;
}



bool menu_principal(){
	
	char opcion;
	do{
		resize(ANCHO,30);
		limpiar_pantalla();
		
		gotoxy(0,7);
		color("celeste");
		centrar(s('¡')+"Hola "+actual.nombre+"!");
		color("blanco");
		
		gotoxy(0,9);
		colorear(verde,"MEN"+s('Ú')+" PRINCIPAL");
		centrar(" ==================\n");
		centrar("1.- Juegos              ");
		centrar("  2.- Estad"+s('í')+"sticas y logros");
		centrar(" 3.- Ver rankings        \n");
		centrar("7.- Opciones avanzadas  ");
		centrar("8.- Cr"+s('é')+"ditos           ");
		colorear(rojo,"  9.- Cerrar la aplicaci"+s('ó')+"n\n");
		colorear(amarillo,"Escrib"+s('í')+" un n"+s('ú')+"mero y presion"+s('á')+" Enter");
		
		gotoxy(30,21);
		cin >> opcion;
		while(opcion!='1' and opcion!='2' and opcion!='3' and opcion!='7' and opcion!='8' and opcion!='9'){
			gotoxy(0,20);
			colorear(amarillo,"El n"+s('ú')+"mero ingresado es incorrecto, intent"+s('á')+" de nuevo");
			gotoxy(30,21);
			centrar("                    ");
			gotoxy(30,21);
			cin>>opcion;
		}
		
		switch(opcion){
		case '1':
			menu_juegos();
			break;
		case '2':
			menu_estadisticas();
			break;
		case '3':
			menu_ranking();
			break;
		case '7':{
			bool salir = menu_opciones();
			if(salir) return true;
		}
		break;
		case '8':
			menu_creditos();
			break;
		case '9':
			return false;
		}
		
	} while(opcion!='9');

	return false;
}

void menu_juegos(){
	
	char opcion;
	do{
		resize(ANCHO,30);
		limpiar_pantalla();
		gotoxy(0,3);
		
		colorear(verde,"MEN"+s('Ú')+" DE JUEGOS");
		centrar("  ==================\n");
		centrar("- Juegos num"+s('é')+"ricos -\n");
		centrar("1.- FriCal                  ");
		centrar("2.- PiPaTi                  ");
		centrar("3.- Generala b"+s('á')+"sica         ");
		centrar("  4.- Generala avanzada      \n\n");
		centrar("- Juegos de letras -\n");
		centrar("  5. Ahorcado                \n\n");
		centrar("- Juegos con tablas -\n");
		centrar("6.- ParEs                   ");
		centrar(" 7.- Batalla Naval           \n");
		
		colorear(rojo," 9.- Volver al men"+s('ú')+" principal\n");
		colorear(amarillo,"Escrib"+s('í')+" un n"+s('ú')+"mero y presion"+s('á')+" Enter");
		
		gotoxy(0,25);
		cin >> opcion;
		
		while(opcion!='1' and opcion!='2' and opcion!='3' and opcion!='4' and opcion!='5' and opcion!='6' and opcion!='7' and opcion!='9'){
			gotoxy(0,26);
			colorear(amarillo,"El n"+s('ú')+"mero ingresado es incorrecto, intent"+s('á')+" de nuevo");
			gotoxy(0,25);
			cin>>opcion;
		}
		
		switch(opcion){
		case '1':
			frical();
			break;
		case '2':
			pipati();
			break;
		case '3':
			generala();
			break;
		case '4':
			generala_avanzada();
			break;
		case '5':
		
#ifdef windows
			ahorcado1();
#else
			limpiar_pantalla();
			gotoxy(0,13);
			colorear(rojo,"  Lo sentimos, este juego no est"+s('á')+" disponible en Linux\n\n");
			pausa(1);
#endif
			break;
		case '6':
			pares();
			break;
		case '7':
#ifdef windows
			batalla_naval();
#else
			limpiar_pantalla();
			gotoxy(0,13);
			colorear(rojo,"  Lo sentimos, este juego no est"+s('á')+" disponible en Linux\n\n");
			pausa(1);
#endif
			break;
		}
	} while(opcion!='9');
	
}

void logo(){
	int x= 8;
	int y= 12;
	string cadena;
	ifstream archivo3;
	
	color(blanco);
	archivo3.open("data/text/bad_milk.txt");
	
	gotoxy(0,2);
	while (getline (archivo3,cadena)){
		centrar(cadena);
	}
	
	archivo3.close();
	
	ifstream archivo;
	archivo.open("data/text/logo_principal.txt");
	
	ifstream archivo2;
	archivo2.open("data/text/numeros_aleatorios.txt");
	
	char vector[533];
	int vector2[533];
	
	char c;
	
	for(int i=0; i<533; i++){
		
		archivo.get(c);
		
		if(c!='\n' and  c!= 13 ){
			vector[i]=c;
		}
		else{
			i--;
		}
	}
	
	for(int i=0; i<533; i++){
		
		archivo2 >> vector2[i];
		
	}
	
	archivo.close();
	archivo2.close();
	
	int fila;
	int columna;
	for(int i=0; i<533; i++){
		
		columna = vector2[i]/41;
		fila = vector2[i]%41;
		
		gotoxy(x+fila,y+columna);
		
		if(i!=21){
			cout<< vector[vector2[i]];
			cout.flush();
			
		}
		dormir(2);

	}
			gotoxy(0,28);
	
	dormir(800);

}

void menu_creditos(){
	limpiar_pantalla();
	
	leerarchivo("bad_milk.txt");
	
	string cadena;
	ifstream archivo;
	
	archivo.open("data/text/creditos.txt");

	leerarchivo("creditos.txt",blanco,150);
	
	for (int i=0; i<30; i++){
		cout << "\n";
		dormir(150);
	}
	
	dormir(600);
	pausa(1);
	limpiar_pantalla();
}

bool menu_opciones(){
	
	char opcion;
	do{
		resize(ANCHO,30);
		limpiar_pantalla();
		gotoxy(0,9);
		colorear(verde,"OPCIONES AVANZADAS");
		centrar(" ==================\n");
		centrar("1.- Cerrar sesi"+s('ó')+"n          ");
		centrar("2.- Cambiar contrase"+s('ñ')+"a     ");
		centrar("  3.- Eliminar mi cuenta     \n\n");
		colorear(rojo," 9.- Volver al men"+s('ú')+" principal\n");
		colorear(amarillo,"Escrib"+s('í')+" un n"+s('ú')+"mero y presion"+s('á')+" Enter");
		
		gotoxy(30,22);
		cin >> opcion;
		while(opcion!='1' and opcion!='2' and opcion!='3' and opcion!='9'){
			gotoxy(0,19);
			colorear(amarillo,"El n"+s('ú')+"mero ingresado es incorrecto, intent"+s('á')+" de nuevo");
			gotoxy(30,20);
			centrar("                       ");
			gotoxy(30,20);
			cin>>opcion;
		}
		
		switch(opcion){
		case '1':{
			return cerrar_sesion();
		}
		case '2':
			cambiar_contrasenia();
			break;
		case '3':
				{
			bool salir = eliminar_cuenta();
			if(salir){
				return true;
			}
		}
			break;
		case '9':
			return false;
		}
		
	} while(opcion!='9');
	
	return false;

}
