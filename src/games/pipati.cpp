#include <iostream>
#include <chrono> 
#include <stdlib.h>
#include <time.h>

#include "pipati.h"
#include "funciones_utiles.h"
#include "ranking.h"
#include "ingreso_usuarios.h"

#define ANCHO 125

using namespace std;

void pipati();
void jugarpipati ();
void instruccionespipati ();
string eleccion(int x);

	
void pipati() {
	char opcion;
	resize(ANCHO,33);
	limpiar_pantalla();
	
	do {
		gotoxy(0,7);
		centrar("- Categor"+s('í')+"a juegos num"+s('é')+"ricos -");
		cout << endl;
		gotoxy(0,9);
		leerarchivo("pipati_titulo.txt", verde2);
		
		cout << "\n\n";
		dormir(300);
		colorear("amarillo",s('¡')+"Presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!\n");
		dormir(200);
		centrar("1."+s('¡')+"A jugar!");
		dormir(200);
		centrar("2."+s('¿')+"C"+s('ó')+"mo se juega?");
		dormir(200);
		colorear("rojo","9. Volver al men"+s('ú')+" de juegos");
		
		gotoxy(62,27);
		cin >> opcion;
		
		while (opcion != '1' and opcion != '2' and opcion != '9') {
			gotoxy(0,21);
			colorear("amarillo",s('¡')+"PSSS, presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!");
			gotoxy(0,27);
			centrar("                    ");
			gotoxy(62,27);
			cin >> opcion;
		}
		
		switch (opcion){
		case '1':
			jugarpipati ();//modificarlo para que el juego se resetee y comience desde la ronda 1//
			mostrar_rank(2);
			resize(ANCHO,33);
			break;
		case '2': //pasar todo a una funcion//
			instruccionespipati();
			break;
		}
		
	} while (opcion != '9');
	
	
}
	
void instruccionespipati (){
	
	limpiar_pantalla();
	
	cout << "\n";
	centrar("INSTRUCCIONES\n");
	leerarchivo("pipati_instrucciones.txt");
	cout << "\n";
	pausa(1);
	
	limpiar_pantalla();
}
void jugarpipati(){
	int ingresoUsuario; 
	int cpu;
	int rondas = 1; 
	int contadorPC = 0; 
	int contadorJugador = 0; 
	
	limpiar_pantalla();
	
	cout << "\n";
	
	auto comienzo = chrono::steady_clock::now();
	
	do { 
		
		cpu=(rand()%3)+1;
		
		cout << "\n";
		colorear("verde","Ronda N"+s('°')+to_string(rondas)+"\n");
		
		centrar(" Ingrese: 1 (Piedra) - 2(Papel) - 3(Tijera)\n");
		centrar(s('¿')+"Qu"+s('é')+" quer"+s('é')+"s elegir?: ",0);
		
		do{
			cin >> ingresoUsuario; 
			if(ingresoUsuario > 3 or ingresoUsuario < 1){
				cout << "\n";
				centrar("N"+s('ú')+"mero inv"+s('á')+"lido. Por favor "+actual.nombre+", ingrese un n"+s('ú')+"mero valido\n");
			}
		} while(ingresoUsuario > 3 or ingresoUsuario < 1);
		
		cout << "\n";
		centrar(actual.nombre+" seleccion"+s('ó')+": "+eleccion(ingresoUsuario));
		
		centrar("La computadora seleccion"+s('ó')+": "+eleccion(cpu)+"\n");
		
		if(ingresoUsuario==cpu){
			centrar("Empate, nadie suma puntos\n"); 
		}
		else if ((ingresoUsuario==1 and cpu==3) or (ingresoUsuario==2 and cpu==1) or (ingresoUsuario==3 and cpu==2)){
			centrar(eleccion(ingresoUsuario)+"gana a "+eleccion(cpu));
			centrar("Ganaste "+actual.nombre+"! Sum"+s('á')+"s 1 punto\n");
			contadorJugador++;
		}
		else {
			centrar(eleccion(cpu)+" gana a "+ eleccion(ingresoUsuario));
			centrar(s('¡')+"Perdiste esta ronda "+actual.nombre+"!\n");
			contadorPC++;
		}
		
		pausa(1);
		limpiar_pantalla();
		rondas ++;
		
	} while(rondas <= 5);
	
	rondas = 1;
	
	gotoxy(0,7);
	centrar("#########################################################\n"); 
	centrar(s('¡')+"LA PARTIDA HA FINALIZADO!\n");
	
	centrar(actual.nombre+" tu puntuaci"+s('ó')+"n es de: "+to_string(contadorJugador)+" puntos");
	
	int duracion = (chrono::steady_clock::now() - comienzo)/chrono::seconds(1) ;
	if (contadorJugador > contadorPC){
		
		leerarchivo("pipati_ganaste.txt");
		
		guardar_partida(2,contadorJugador,contadorPC,1,duracion);
		
	}else if (contadorPC > contadorJugador){
		
		leerarchivo("pipati_perdiste.txt");
		
		guardar_partida(2,contadorJugador,contadorPC,2,duracion);
		
	}else {
		
		leerarchivo("pipati_empate.txt");
		
		guardar_partida(2,contadorJugador,contadorPC,3,duracion);
		
	}
	
	cout << "\n";
	centrar(s('¡')+"Gracias por jugar!\n");
	centrar("#########################################################\n");
	
	pausa(1);
	limpiar_pantalla();
}

string eleccion(int x){
	string valor;
	
	switch(x){
	case 1:
		valor = "Piedra ";
		break;
	case 2:
		valor = "Papel ";
		break;
	case 3:
		valor = "Tijera ";
		break;
	}
	
	return valor;
}
	
