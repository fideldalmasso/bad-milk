#include <iostream>
#include <chrono> 

#include "batalla_naval.h"
#include "funciones_utiles.h"
#include "ranking.h"

#define ANCHO 100

#if defined (_WIN32) || defined (WIN32)
#define windows
#endif

using namespace std;

void batalla_naval(); 

void batalla_naval() {

	
	char opcion;
	do {
		limpiar_pantalla();
		resize(ANCHO,37);
		cout << endl << endl;
		
		centrar(" - Categor"+s('í')+"a juegos con tablas -\n");
		leerarchivo("batalla_naval_titulo.txt",azul);
		dormir(300);
		gotoxy(0,27);
		colorear("amarillo",s('¡')+"Presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!\n");
		dormir(200);
		centrar("1."+s('¡')+"A jugar!");
		dormir(200);
		centrar("2."+s('¿')+"C"+s('ó')+"mo se juega?");
		dormir(200);
		colorear("rojo","9. Volver al men"+s('ú')+" de juegos");
		
		opcion = '0';
		while(opcion!='1' and opcion!='2' and opcion!='9'){
			gotoxy(0,32);
			centrar("                    ");
			gotoxy(50,32);
			cin >> opcion;
			
			switch (opcion){
			case '1':{
				limpiar_pantalla();
			
				
				auto comienzo = chrono::steady_clock::now();
				
				int puntaje = 0;
				
#ifdef windows
				puntaje = batallanaval();
#endif
				int resultado=0;
				if(puntaje!=0)
					resultado=1;
				
				int duracion = (chrono::steady_clock::now() - comienzo)/chrono::seconds(1);
				guardar_partida(7,puntaje,-1,resultado,duracion);
				cout << "\n \n";
				pausa();
				mostrar_rank(7);
				limpiar_pantalla();
			}
				break;
			case '2': 
				limpiar_pantalla();
				cout << "\n";
				centrar("INSTRUCCIONES\n");
				leerarchivo("batalla_naval_instrucciones.txt");

				cout << "\n";
				pausa(1);
				limpiar_pantalla();
				break;
			case '9':
				break;
				
			default: 
				gotoxy(0,27);
				colorear("amarillo",s('¡')+"PSSS, presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!");
			}
		}
	}while(opcion != '9');
	
}
