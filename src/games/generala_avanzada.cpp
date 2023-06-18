#include <iostream>
#include <chrono> 
#include <time.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <cstdio>
#include <vector>
#include <algorithm>

#include "generala_avanzada.h"
#include "funciones_utiles.h"
#include "ranking.h"

#define ANCHO 125
#define DADOS 5
#define JUEGOS 10
#define JUGADORES 2

//#if defined (_WIN32) || defined (WIN32) 
//	#include <windows.h>
//#endif

using namespace std;

void jugar_generala_avanzada();
void instrucciones();
bool inicio();
void lanzamiento (bool, bool &, int [], int);
void evaluacion (bool, bool, int [], int [][JUGADORES]);
void resultadoParcial (int [][JUGADORES], int);
void resultadoFinal (int puntos[][JUGADORES], int duracion);
void centrar(int x,int y, int posicion);
void imagenDado (int dado, int altura, int posicion);
void animacionDado (int dado, int altura, int posicion);

void generala_avanzada() {
	char selector;
	
	limpiar_pantalla();
	color("blanco");
	
	do {
		resize(ANCHO,33);
		cout << endl;
		
		centrar("- Categoria juegos numericos -");
		gotoxy (0,3);
		leerarchivo("generala_avanzada_titulo.txt", verde);
		
		
		cout << "\n\n";
		dormir(300);
		colorear("amarillo",+"Presiona un numero y enter para elegir!\n");
		dormir(200);
		centrar("1. A jugar!");
		dormir(200);
		centrar("2. Como se juega?");
		dormir(200);
		colorear("rojo","9. Volver al menu de juegos");
		
		gotoxy(62,31);
		cin >> selector;
		
		while (selector != '1' and selector != '2' and selector != '9'){
			gotoxy(0,26);
			colorear("amarillo","PSSS, presion"+s('�')+" un n"+s('�')+"mero y enter para elegir!");
			gotoxy(0,31);
			centrar("                    ");
			gotoxy(62,31);
			cin >> selector;
		}
		
		limpiar_pantalla();
		
		switch (selector) {
		case '1':
			jugar_generala_avanzada();
			mostrar_rank(4);
			break;
			
		case '2':
			instrucciones();
			break;
		}
		
		limpiar_pantalla();
		
	} while (selector != '9');
	
	
}

//Procedimiento que ejecuta el juego en si mismo
void jugar_generala_avanzada (){
	auto comienzo = chrono::steady_clock::now();
	
	bool comienzaUsuario = inicio(); //variable que determina quien comienza (si es 1 empieza el usuario, en caso contrario la computadora)
	int tirada [DADOS]; //vector donde se almacenan loss numeros de los dados lanzados
	int puntos [JUEGOS][JUGADORES]; //matriz de 10x2 donde se almacenan los puntos obtenidos por el jugador (en la fila 0) y por la computadora (en la fila 2)
	bool segundaTirada = 0; //variable que permite distinguir cuando el jugador ha realizado un segundo intento
	
	//estructura repetitiva que inicializa la matriz en 99
	for (int f=0; f<JUEGOS; f++) {
		for (int c=0; c<JUGADORES; c++) {
			puntos [f][c]=99;
		}
	}
	
	//estructura repetitiva que ejecuta las 10 tiradas del jugador y la computadora
	for (int numeroTirada=0; numeroTirada <10; numeroTirada++ ) {
		segundaTirada = 0;
		lanzamiento (comienzaUsuario, segundaTirada, tirada, numeroTirada);
		evaluacion (comienzaUsuario, segundaTirada, tirada, puntos);
		resultadoParcial (puntos, numeroTirada);
		segundaTirada = 0;
		lanzamiento ((!(comienzaUsuario)), segundaTirada, tirada, numeroTirada);
		evaluacion ((!(comienzaUsuario)), segundaTirada, tirada, puntos);
		resultadoParcial (puntos, numeroTirada);
	}
	
	int duracion = (chrono::steady_clock::now() - comienzo)/chrono::seconds(1) ;
	
	resultadoFinal (puntos, duracion);
	
}

//Procedimiento que muestra las instrucciones del juego
void instrucciones () {
	cout << "\n";
	centrar("INSTRUCCIONES\n");
	leerarchivo("generala_avanzada_instrucciones.txt");
	cout << "\n";
	pausa(1);
	
}

//Funcion que determina quien comienza la partida.
bool inicio () {
	bool comienzaUsuario=0; //Booleano que determina quien comienza (si vale 1 comienza el jugador, si vale 0 comienza la computadora).
	int dadoUsuario; //Valor del dado lanzado por el jugador.
	int dadoComputadora; //Valor del dado lanzado por la computadora.
	srand(time(NULL)); //Se inicializa la semilla.
	
	//Estructura repetitiva que evita casos de empate.
	do {
		dadoUsuario=((rand()%6)+1);
		dadoComputadora=((rand()%6)+1);
		
		if (dadoUsuario > dadoComputadora) {
			comienzaUsuario=1;
		}
		
	} while (dadoUsuario==dadoComputadora);
	
	centrar(44,1,2);
	cout  <<"Se lanzan los dado para ver quien comienza!";
	centrar(26,4,2);
	cout << "Lanzas el dado y obtienes:";
	animacionDado(dadoUsuario, 6, 2);
	centrar(39,12,2);
	cout << "La computadora lanza el dado y obtiene: ";
	animacionDado(dadoComputadora, 14, 2);
	
	//Estructura de seleccion que anuncia quien comienza.
	if (comienzaUsuario == 1) {
		centrar(15,21,2);
		color(verde);
		cout <<"Empezas vos!";
		color(blanco);
	} else {
		centrar(25,21,2);
		color(rojo);
		cout <<"Empieza la computadora!";
		color(blanco);
	}
	
	centrar(34,24,2);
	pausa();
	limpiar_pantalla();
	
	return comienzaUsuario;
}

//Procedimiento que se utiliza para lanzar los dados.
void lanzamiento (bool comienzaUsuario, bool & segundaTirada, int tirada [], int numeroTirada){
	int dadosDescartar; //Variable que almacena el numero de dados que se descartan.
	
	//Estructura de seleccion que anuncia el numero de la tirada y a quien corresponde (computadora o jugador)
	if (comienzaUsuario==1){
		centrar(23,1,2);
		cout << "Tirada N# "<< (numeroTirada+1) << " del ";
		color(verde);
		cout << "Jugador";;
		color(blanco);
		cout << ":" << endl;
		centrar(15,3,2);
		cout << "Primer intento:";
	} else {
		centrar(30,1,2);
		cout << "Tirada N# " << (numeroTirada+1) << " de la ";
		color(rojo);
		cout << "Computadora:";
		color(blanco);
		cout << ":" << endl;
		centrar(14,3,2);
		cout << "Unico intento:";
	}
	
	//Estructura iterativa que inicializa el arreglo de dados con valores aleatorios entre 1 y 6
	for (int dado=0; dado<DADOS; dado++){
		tirada[dado]=((rand()%6)+1);
	}
	
	//Procedimientos que muestran los cinco dados arrojados
	centrar(10,4,1);
	cout << "Dado N# 1:";
	animacionDado(tirada[0], 5, 1);
	centrar(10,4,3);
	cout << "Dado N# 2:";
	animacionDado(tirada[1], 5, 3);
	centrar(10,11,1);
	cout << "Dado N# 3:";
	animacionDado(tirada[2], 12, 1);
	centrar(10,11,3);
	cout << "Dado N# 4:";
	animacionDado(tirada[3], 12, 3);
	centrar(10,18,2);
	cout << "Dado N# 5:";
	animacionDado(tirada[4], 19, 2);
	
	//Estrctura de seleccion que da la posibilidad de que el jugador tenga un segundo intento
	if (comienzaUsuario==1){
		
		centrar(31,25,2);
		cout << "Cantidad de dados a descartar: ";
		cin >> dadosDescartar;
		
		//Estructura de repeticion que evita el ingreso de cantidades erroneas
		while (dadosDescartar < 0 or dadosDescartar > 5){
			color(rojo);
			centrar(80,25,2);
			cout << "El numero de dados a descartar tiene que estar entre 0 y 5. Prueba otra vez:          ";
			color(blanco);
			centrar(99,25,0);
			cin >> dadosDescartar;
		}
		
		//Estructura de seleccion que habilita el ingreso de las posiciones a descartar en caso de que se requiera
		if (dadosDescartar != 0) {
			segundaTirada = 1;
			
			if (dadosDescartar != 5){
				centrar(19,27,2);
				cout << "Dados a descartar: ";
				
				//Estructura de repeticion que permite volver a lanzar las posiciones elegidas
				for (int i = 0; i< dadosDescartar; i++){
					int posicion;
					centrar ((99+2*i),27,0);
					cin >> posicion;
					centrar ((100+2*i),27,0);
					cout << "-";
					
					//Estructura de repeticion que evita el ingreso de posiciones erroneas a descartar
					while (posicion < 1 or posicion > 5){
						color(rojo);
						centrar(80,27,2);
						cout << "El numero del dado a descartar tiene que estar entre 1 y 5. Prueba otra vez:          ";
						color(blanco);
						centrar ((99+2*i),27,0);
						cin >> posicion;
						centrar ((100+2*i),27,0);
						cout << "-";
					}
					
					tirada[posicion-1] = 0;
				}
			} else {
				for (int i = 0; i< dadosDescartar; i++){
					tirada[i] = 0;
				}
			}
			
			limpiar_pantalla();
			
			centrar(16,2,2);
			cout << "Segundo intento:";
			
			//Estructura de repeticion que muestra los dados obtenidos y lanza los que se hayan seleccionado 
			for (int i=0; i< DADOS; i++){
				if (tirada[i]==0) {
					tirada[i] = ((rand()%6)+1);
					color(verde);
					switch (i){
					case 0:
						centrar(10,4,1);
						cout << "Dado N# 1:";
						animacionDado(tirada[i], 5, 1);
						break;
					case 1:
						centrar(10,4,3);
						cout << "Dado N# 2:";
						animacionDado(tirada[i], 5, 3);
						break;
					case 2:
						centrar(10,11,1);
						cout << "Dado N# 3:";
						animacionDado(tirada[i], 12, 1);
						break;
					case 3:
						centrar(10,11,3);
						cout << "Dado N# 4:";
						animacionDado(tirada[i], 12, 3);
						break;
					case 4:
						centrar(10,18,2);
						cout << "Dado N# 5:";
						animacionDado(tirada[i], 19, 2);
						break;
					}
					color(blanco);
				} else {
					switch (i){
					case 0:
						centrar(10,4,1);
						cout << "Dado N# 1:";
						imagenDado(tirada[i], 5, 1);
						break;
					case 1:
						centrar(10,4,3);
						cout << "Dado N# 2:";
						imagenDado(tirada[i], 5, 3);
						break;
					case 2:
						centrar(10,11,1);
						cout << "Dado N# 3:";
						imagenDado(tirada[i], 12, 1);
						break;
					case 3:
						centrar(10,11,3);
						cout << "Dado N# 4:";
						imagenDado(tirada[i], 12, 3);
						break;
					case 4:
						centrar(10,18,2);
						cout << "Dado N# 5:";
						imagenDado(tirada[i], 19, 2);
						break;
					}
				}
				dormir(150);
			}
		}
	}
}

//Procedimiento que se utiliza para asignar puntajes a las tiradas.
void evaluacion (bool comienzaUsuario, bool segundaTirada, int tirada [], int puntos [][JUGADORES]){
	bool juego[5] = {0,0,0,0,0}; // 0 = valorNumerico, 1 = escalera, 2 = full, 3 = poker, 4 = generala
	int jugador; //variable que determina en que columna debe almacenarse los puntos obtenidos
	int puntajeTotal = 0; //variable que almacena el puntaje parcial hasta dicha tirada
	
	if (comienzaUsuario == 1){
		jugador = 0;
	} else {
		jugador = 1;
	}
	
	// Validacion generala y poker
	for (int numero = 1; numero < 7; numero++) {
		int cantidadDados = 0;
		for (int dado = 0; dado < DADOS; dado++) cantidadDados += numero == tirada[dado];
		
		if (cantidadDados == 5) juego[4] = 1;
		if (cantidadDados >= 4) juego[3] = 1;
	}

	// Validacion full
	int cantidad[6] = {0,0,0,0,0,0};
	for(int dado = 0; dado<DADOS; dado++) cantidad[tirada[dado]-1]++;
	for(int dadoA = 0; dadoA<DADOS; dadoA++) 
		for(int dadoB = 0; dadoB<DADOS; dadoB++)
			if (min(cantidad[dadoA],cantidad[dadoB]) == 2 && max(cantidad[dadoA],cantidad[dadoB]) == 3)
				juego[2] = 1;
	
	// Validacion escalera
	juego[1] = 1;
	vector<int> tiradaOrdenada; 
	for(int i = 0; i<DADOS; i++) tiradaOrdenada.push_back(tirada[i]);
	sort(tiradaOrdenada.begin(), tiradaOrdenada.end());
	for(int dado = 0; dado<DADOS-1; dado++) if(tiradaOrdenada[dado]+1 != tiradaOrdenada[dado+1]) juego[1] = 0;

	// Validacion valor numerico
	int maxValorNumerico = -1;
	for(int numero = 1; numero<7; numero++){
		if(cantidad[numero-1] == 0 || puntos[numero-1][jugador] != 99) continue;
		if(maxValorNumerico == -1 || cantidad[maxValorNumerico-1]*maxValorNumerico < cantidad[numero-1]*numero){
			maxValorNumerico = numero;
			juego[0] = 1;
		}
	}

	centrar(42,27,2);
	cout << "Juego formado: ";

	// asignar puntos generala
	if (juego[4] && puntos[9][jugador] == 99) {
		cout << "generala ";
		puntos[9][jugador] = 55;
		if (segundaTirada == 0){
			cout << "servida - " << puntos[9][jugador] << " puntos." << endl;	
		} else {
			puntos[9][jugador] -= 5;
			cout << "armada - " << puntos[9][jugador] << " puntos." << endl;	
		}
	
	// asignar puntos poker
	} else if (juego[3] && puntos[8][jugador] == 99) {
		puntos[8][jugador] = 45;
		cout << "poker ";
		if (segundaTirada == 0){
			cout << "servido - " << puntos[8][jugador] << " puntos." << endl;	
		} else {
			puntos[8][jugador] -= 5;
			cout << "armado - " << puntos[8][jugador] << " puntos." << endl;	
		}
	
	// asignar puntos full
	} else if (juego[2] && puntos[7][jugador] == 99) {
		puntos[7][jugador] = 35;
		cout << "full ";	
		if (segundaTirada == 0){
			cout << "servido - " << puntos[7][jugador] << " puntos." << endl;	
		} else {
			puntos[7][jugador] -= 5;
			cout << "armado - " << puntos[7][jugador] << " puntos." << endl;	
		}

	// asignar puntos escalera
	} else if (juego[1] && puntos[6][jugador] == 99) {
		puntos[6][jugador] = 25;
		cout << "escalera ";
		
		if (segundaTirada == 0){
		cout << "servida - " << puntos[6][jugador] << " puntos." << endl;	
		} else {
			puntos[6][jugador] -= 5;
			cout << "armada - " << puntos[6][jugador] << " puntos." << endl;
		}
	
	// asignar puntos valor numerico
	} else if (juego[0]) {
		puntos[maxValorNumerico-1][jugador] = (cantidad[maxValorNumerico-1]*maxValorNumerico);
		cout << "valor numerico " << maxValorNumerico << " - " << puntos[maxValorNumerico - 1][jugador] << " puntos" << endl;
	
	// tachar juego
	} else {
		for (int filas = (JUEGOS-1); filas > -1; filas--){
			if (puntos[filas][jugador] == 99) {
				puntos[filas][jugador] = 0;
				cout << "se tacha el juego ";
				switch (filas){
				case 0:
					cout << "valor numerico 1";
					break;
				case 1:
					cout << "valor numerico 2";
					break;
				case 2:
					cout << "valor numerico 3";
					break;
				case 3:
					cout << "valor numerico 4";
					break;
				case 4:
					cout << "valor numerico 5";
					break;
				case 5:
					cout << "valor numerico 6";
					break;
				case 6:
					cout << "escalera";
					break;
				case 7:
					cout << "full";
					break;
				case 8:
					cout << "poker";
					break;	
				case 9:
					cout << "generala";
					break;
				};
				break;
			}
		}
	}
	
	// imprimir puntaje total
	for (int filas = 0; filas < JUEGOS; filas++){
		puntajeTotal += puntos[filas][jugador] == 99 ? 0 : puntos[filas][jugador];
	}
	centrar(18,29,2);
	cout << "Puntaje total: " << puntajeTotal;
	
	centrar(34,31,2);
	pausa();
	limpiar_pantalla();
}

//Procedimiento que muestra los resultados parciales
void resultadoParcial (int puntos [][JUGADORES], int numeroTirada){
	int totalComputadora=0, totalJugador=0;	
	
	for(int columna=0; columna<2; columna++){
		for(int fila=0; fila<10; fila++){
			centrar(2, (fila*2)+8, (columna+2));
			if (puntos[fila][columna]==99){
				cout << "---";
			} else if (puntos[fila][columna]==0){
				cout << "XXX";
			} else {
				cout << puntos[fila][columna];
			}
			if(columna==0 and puntos[fila][columna]!=99){
				totalJugador+=puntos[fila][columna];
			} 
			if(columna==1 and puntos[fila][columna]!=99){
				totalComputadora+=puntos[fila][columna];
			}
		}
	}
	
	centrar(20,2,2);
	cout << "RESULTADOS PARCIALES";
	centrar(5,6,1);
	cout << "JUEGO";
	centrar(11,6,3);
	cout << "COMPUTADORA";
	centrar(7,6,2);
	cout << "JUGADOR";
	centrar(16,8,1);
	cout << "Valor numerico 1";
	centrar(16,10,1);
	cout << "Valor numerico 2";
	centrar(16,12,1);
	cout << "Valor numerico 3";
	centrar(16,14,1);
	cout << "Valor numerico 4";
	centrar(16,16,1);
	cout << "Valor numerico 5";
	centrar(16,18,1);
	cout << "Valor numerico 6";
	centrar(8,20,1);
	cout << "Escalera";
	centrar(4,22,1);
	cout << "Full";
	centrar(5,24,1);
	cout << "Poker";
	centrar(8,26,1);
	cout << "Generala";
	centrar(5,28,1);
	cout << "TOTAL";
	centrar(2,28,2);
	cout << totalJugador;
	centrar(2,28,3);
	cout << totalComputadora;
	
	centrar(34,31,2);
	pausa();
	limpiar_pantalla();
}

//Procedimiento que determina el ganador de la partida
void resultadoFinal (int puntos[][JUGADORES], int duracion){
	int puntajeTotalJugador = 0; //Variable que almacena el puntaje final del jugador
	int puntajeTotalComputadora = 0; //Variable que almacena el puntaje final de la computadora
	
	//Estructura iterativa que determina los puntajes finales del jugador y la computadora
	for (int columnas = 0; columnas < 2; columnas ++){
		for (int filas = 0; filas < JUEGOS; filas++){
			if (puntos[filas][columnas] != 99) {
				if (columnas == 0) {
					puntajeTotalJugador += puntos[filas][columnas];
				} else {
					puntajeTotalComputadora += puntos[filas][columnas];
				}
				
			}
		}
	}
	
	centrar (15, 1, 2);
	cout << "RESULTADO FINAL";
	centrar (23, 8, 1);
	color(verde);
	cout << "PUNTAJE DEL JUGADOR: " << puntajeTotalJugador;
	centrar (29, 8, 3);
	color(rojo);
	cout << "PUNTAJE DE LA COMPUTADORA: " << puntajeTotalComputadora;
	color(blanco);
	
	//Estructura de seleccion que anuncia el resultado final de la partida
	centrar (9, 15, 2);
	if (puntajeTotalComputadora < puntajeTotalJugador){
		color(verde);
		cout << "GANASTE!" << endl;
		guardar_partida(4,puntajeTotalJugador,puntajeTotalComputadora,1,duracion);
	} else {
		if (puntajeTotalComputadora == puntajeTotalJugador){
			cout <<"EMPATE!" << endl;
			guardar_partida(4,puntajeTotalJugador,puntajeTotalComputadora,3,duracion);
		} else {
			color(rojo);
			cout <<"PERDISTE!" << endl;
			guardar_partida(4,puntajeTotalJugador,puntajeTotalComputadora,2,duracion);
		}
	}
	color(blanco);
	
	centrar(34,31,2);
	pausa();
	limpiar_pantalla();
}

//Procedimiento que centra caracteres en tres posiciones diferentes
void centrar (int x,int y, int posicion) {
	//Estructura de seleccion multile que determina si se centra en la izquierda, en el medio o en la derecha
	switch (posicion){
	case 1:
		x = (125/4)-(x/2); 
		break;
	case 2:
		x = (125/2)-(x/2);
		break;
	case 3:
		x = ((125/4)*3)-(x/2);
		break;
	}
	gotoxy(x,y);
}

//Procedimiento que imprime un dado en una posicion deseada
void imagenDado (int numeroDado, int altura, int posicion){
	
	centrar(7, altura, posicion);
	cout << " ----- " << endl;
	centrar(7, altura+4, posicion);
	cout << " ----- " << endl;
	switch (numeroDado){
	case 1:
		centrar(7, altura+1, posicion);
		cout << "|     |" << endl;
		centrar(7, altura+2, posicion);
		cout << "|  o  |" << endl;
		centrar(7, altura+3, posicion);
		cout << "|     |" << endl;
		break;
	case 2:
		centrar(7, altura+1, posicion);
		cout << "|o    |" << endl;
		centrar(7, altura+2, posicion);
		cout << "|     |" << endl;
		centrar(7, altura+3, posicion);
		cout << "|    o|" << endl;
		break;
	case 3:
		centrar(7, altura+1, posicion);
		cout << "|o    |" << endl;
		centrar(7, altura+2, posicion);
		cout << "|  o  |" << endl;
		centrar(7, altura+3, posicion);
		cout << "|    o|" << endl;
		break;
	case 4:
		centrar(7, altura+1, posicion);
		cout << "|o   o|" << endl;
		centrar(7, altura+2, posicion);
		cout << "|     |" << endl;
		centrar(7, altura+3, posicion);
		cout << "|o   o|" << endl;
		break;
	case 5:
		centrar(7, altura+1, posicion);
		cout << "|o   o|" << endl;
		centrar(7, altura+2, posicion);
		cout << "|  o  |" << endl;
		centrar(7, altura+3, posicion);
		cout << "|o   o|" << endl;
		break;
	case 6:
		centrar(7, altura+1, posicion);
		cout << "|o   o|" << endl;
		centrar(7, altura+2, posicion);
		cout << "|o   o|" << endl;
		centrar(7, altura+3, posicion);
		cout << "|o   o|" << endl;
		break;
	}
}

//Procedimiento que simula una animacion de dados al reproducir varias veces "imagenDado"
void animacionDado (int numeroDado, int altura, int posicion){
	int numero;
	
	for(int i = 0; i<7; i++){ 
		numero = (rand()%6)+1;
		if (i == 6){
			numero = numeroDado;
		}
		imagenDado (numero, altura, posicion);
		dormir(200);
	}

}


