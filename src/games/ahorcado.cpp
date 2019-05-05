#include <iostream>
#include <chrono> 

#include "ahorcado.h"
#include "funciones_utiles.h"
#include "ranking.h"

#if defined (_WIN32) || defined (WIN32)
	#define windows
#endif

#define ANCHO 106

using namespace std;

void ahorcado1(); 

void ahorcado1() {
	
	char opcion;
	
	do {
		limpiar_pantalla();
		resize(106,30);
		gotoxy(0,7);
		centrar("- Categor"+s('í')+"a juegos de letras -");
		
		gotoxy(0,9);
		leerarchivo("ahorcado_titulo.txt",celeste);
		
		cout << "\n\n";
		dormir(300);
		colorear("amarillo",s('¡')+"Presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!\n");
		dormir(200);
		centrar("1."+s('¡')+"A jugar!");
		dormir(200);
		centrar("2."+s('¿')+"C"+s('ó')+"mo se juega?");
		dormir(200);
		colorear("rojo","9. Volver al men"+s('ú')+" de juegos");
		
		opcion = '0';
		
		while(opcion!='1' and opcion!='2' and opcion!='9'){
			gotoxy(0,26);
			centrar("                    ");
			gotoxy(53,26);
			cin >> opcion;
			
			switch (opcion)
			{
			case '1':{
				limpiar_pantalla();
				resize(80,30);
				auto comienzo = chrono::steady_clock::now();
				
				int puntaje =0;
#ifdef windows
				puntaje = ahorcado();
#endif

				int resultado=0;
				if(puntaje!=0)
					resultado=1;
				
				int duracion = (chrono::steady_clock::now() - comienzo)/chrono::seconds(1);
				guardar_partida(5,puntaje,-1,resultado,duracion);
				cout << "\n \n";
				pausa();
				mostrar_rank(5);
				limpiar_pantalla();
			}
				break;
			case '2': 
				limpiar_pantalla();
#ifdef windows
				cout << "\n";
				centrar("INSTRUCCIONES\n");
				leerarchivo("ahorcado_instrucciones.txt");
#endif
				cout << "\n";
				pausa(1);
				limpiar_pantalla();
				break;
			case '9':
				break;
				
			default: 
				gotoxy(0,21);
				colorear("amarillo",s('¡')+"PSSS, presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!");
			}
		}		
	}while(opcion != '9');

}
