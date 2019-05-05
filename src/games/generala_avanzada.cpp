#include <iostream>
#include <chrono> 
#include <time.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <cstdio>

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
		
		centrar("- Categor"+s('í')+"a juegos num"+s('é')+"ricos -");
		gotoxy (0,3);
		leerarchivo("generala_avanzada_titulo.txt", verde);
		
		
		cout << "\n\n";
		dormir(300);
		colorear("amarillo",s('¡')+"Presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!\n");
		dormir(200);
		centrar("1."+s('¡')+"A jugar!");
		dormir(200);
		centrar("2."+s('¿')+"C"+s('ó')+"mo se juega?");
		dormir(200);
		colorear("rojo","9. Volver al men"+s('ú')+" de juegos");
		
		gotoxy(62,31);
		cin >> selector;
		
		while (selector != '1' and selector != '2' and selector != '9'){
			gotoxy(0,26);
			colorear("amarillo",s('¡')+"PSSS, presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!");
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

//Función que determina quien comienza la partida.
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
	cout  <<s('¡')<<"Se lanzan los dado para ver quien comienza!";
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
		cout <<s('¡')<< "Empez"+s('á')+"s vos!";
		color(blanco);
	} else {
		centrar(25,21,2);
		color(rojo);
		cout <<s('¡')<< "Empieza la computadora!";
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
		cout << "Tirada N"<<s('°')<<" " << (numeroTirada+1) << " del ";
		color(verde);
		cout << "Jugador";;
		color(blanco);
		cout << ":" << endl;
		centrar(15,3,2);
		cout << "Primer intento:";
	} else {
		centrar(30,1,2);
		cout << "Tirada N"<<s('°') << " " << (numeroTirada+1) << " de la ";
		color(rojo);
		cout << "Computadora:";
		color(blanco);
		cout << ":" << endl;
		centrar(14,3,2);
		cout << s('Ú')+"nico intento:";
	}
	
	//Estructura iterativa que inicializa el arreglo de dados con valores aleatorios entre 1 y 6
	for (int dado=0; dado<DADOS; dado++){
		tirada[dado]=((rand()%6)+1);
	}
	
	//Procedimientos que muestran los cinco dados arrojados
	centrar(10,4,1);
	cout << "Dado N"<<s('°')<<" 1:";
	animacionDado(tirada[0], 5, 1);
	centrar(10,4,3);
	cout << "Dado N"<<s('°')<<" 2:";
	animacionDado(tirada[1], 5, 3);
	centrar(10,11,1);
	cout << "Dado N"<<s('°')<<" 3:";
	animacionDado(tirada[2], 12, 1);
	centrar(10,11,3);
	cout << "Dado N"<<s('°')<<" 4:";
	animacionDado(tirada[3], 12, 3);
	centrar(10,18,2);
	cout << "Dado N"<<s('°')<<" 5:";
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
			cout << "El n"+s('ú')+"mero de dados a descartar tiene que estar entre 0 y 5. Prueba otra vez:          ";
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
						cout << "El n"+s('ú')+"mero del dado a descartar tiene que estar entre 1 y 5. Prueba otra vez:          ";
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
						cout << "Dado N"<<s('°')<<" 1:";
						animacionDado(tirada[i], 5, 1);
						break;
					case 1:
						centrar(10,4,3);
						cout << "Dado N"<<s('°')<<" 2:";
						animacionDado(tirada[i], 5, 3);
						break;
					case 2:
						centrar(10,11,1);
						cout << "Dado N"<<s('°')<<" 3:";
						animacionDado(tirada[i], 12, 1);
						break;
					case 3:
						centrar(10,11,3);
						cout << "Dado N"<<s('°')<<" 4:";
						animacionDado(tirada[i], 12, 3);
						break;
					case 4:
						centrar(10,18,2);
						cout << "Dado N"<<s('°')<<" 5:";
						animacionDado(tirada[i], 19, 2);
						break;
					}
					color(blanco);
				} else {
					switch (i){
					case 0:
						centrar(10,4,1);
						cout << "Dado N"<<s('°')<<" 1:";
						imagenDado(tirada[i], 5, 1);
						break;
					case 1:
						centrar(10,4,3);
						cout << "Dado N"<<s('°')<<" 2:";
						imagenDado(tirada[i], 5, 3);
						break;
					case 2:
						centrar(10,11,1);
						cout << "Dado N"<<s('°')<<" 3:";
						imagenDado(tirada[i], 12, 1);
						break;
					case 3:
						centrar(10,11,3);
						cout << "Dado N"<<s('°')<<" 4:";
						imagenDado(tirada[i], 12, 3);
						break;
					case 4:
						centrar(10,18,2);
						cout << "Dado N"<<s('°')<<" 5:";
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
	bool generala = 0; //variable que determina si se formo el juego generala
	bool poker = 0; //variable que determina si se formo el juego poker
	bool full = 0; //variable que determina si se formo el juego full
	bool escalera = 1; //variable que determina si se formo el juego escalera
	bool valorNumerico = 1; //variable que determina si se formo el juego valor numerico
	bool finalizar = 0; //variable que determina si se debe finalizar el ciclo de busqueda de valores numericos posibles
	int jugador; //variable que determina en que columna debe almacenarse los puntos obtenidos
	int puntajeTotal = 0; //variable que almacena el puntaje parcial hasta dicha tirada
	
	//Estructura de seleccion que determina donde debe almacenarse el puntaje obtenido
	if (comienzaUsuario == 1){
		jugador = 0;
	} else {
		jugador = 1;
	}
	
	//Estructura que determina si existe el juego "generala" y el juego "poker"
	for (int numero = 1; numero < 7; numero++){
		int cantidadDados = 0;
		for (int dado = 0; dado < DADOS; dado++){
			if (numero == tirada[dado]){
				cantidadDados++;
			}
		}
		if (cantidadDados >= 4){
			poker=1;
			if (cantidadDados==5){
				generala=1;
			}
			
		}
	}
	
	centrar(42,27,2);
	cout << "Juego formado: ";
	
	//Estructura de seleccion que determina si debe asignarse puntos al juego generala o a otro
	if (generala == 1 and puntos [9][jugador] == 99) {
		
		puntos[9][jugador] = 55;
		cout << "generala ";
		
		if (segundaTirada == 0){
			cout << "servida - " << puntos[9][jugador] << " puntos." << endl;	
		} else {
			puntos[9][jugador] -= 5;
			cout << "armada - " << puntos[9][jugador] << " puntos." << endl;	
		}
		
	} else {
		
		//Estructura de seleccion que determina si debe asignarse puntos al juego poker o a otro
		if (poker == 1 and puntos[8][jugador] == 99){
			
			puntos[8][jugador] = 45;
			cout << "poker ";
			
			if (segundaTirada == 0){
				cout << "servido - " << puntos[8][jugador] << " puntos." << endl;	
			} else {
				puntos[8][jugador] -= 5;
				cout << "armado - " << puntos[8][jugador] << " puntos." << endl;	
			}
			
		} else {
			
			//Estructura que determina si existe el juego "full"
			for (int numeroA = 1; numeroA <= 6; numeroA++){
				int cantidadDadosA = 0;
				for (int dadoA = 0; dadoA < DADOS; dadoA++){
					if (numeroA == tirada[dadoA]){
						cantidadDadosA++;
					}
				}
				if (cantidadDadosA == 3){
					for (int numeroB = 1; numeroB <= 6; numeroB++){
						int cantidadDadosB = 0;
						if (numeroB != numeroA) {
							for (int dadoB = 0; dadoB < DADOS; dadoB++){
								if (numeroB == tirada[dadoB]){
									cantidadDadosB++;
								}
							}
							if (cantidadDadosB == 2){
								full = 1;
							}
						}
					}
				}
			}
			
			//Estructura de seleccion que determina si debe asignarse puntos al juego full o a otro
			if (full == 1 and puntos [7][jugador] == 99){
				
				puntos[7][jugador] = 35;
				cout << "full ";
				
				if (segundaTirada == 0){
					cout << "servido - " << puntos[7][jugador] << " puntos." << endl;	
				} else {
					puntos[7][jugador] -= 5;
					cout << "armado - " << puntos[7][jugador] << " puntos." << endl;	
				}
				
			} else {
				
				//Estructura que determina si existe el juego "escalera".
				for (int dadoA = 0; dadoA < DADOS; dadoA++) {
					for (int dadoB = 0; dadoB < (DADOS-1); dadoB++) {
						int temporal = tirada[dadoB];
						
						if (tirada[dadoB] > tirada [dadoB+1]){
							tirada [dadoB] = tirada [dadoB+1];
							tirada [dadoB+1] = temporal; 
						} 
					}
				}
				for (int dado=0; dado < (DADOS-1); dado++){
					if ((tirada[dado]+1) != tirada[dado+1]){
						escalera = 0;
					}
				}
				
				//Estructura de seleccion que determina si debe asignarse puntos al juego escalera o a otro
				if (escalera == 1 and puntos [6][jugador] == 99){
					
					puntos[6][jugador] = 25;
					cout << "escalera ";
					
					if (segundaTirada == 0){
						cout << "servida - " << puntos[6][jugador] << " puntos." << endl;	
					} else {
						puntos[6][jugador] -= 5;
						cout << "armada - " << puntos[6][jugador] << " puntos." << endl;
					}
					
				} else {
					
					//Estructura que determina si existe el juego "valor numérico".
					for (int valorA = 1; valorA <= 6 and finalizar == 0; valorA++){
						int cantidadDadosA = 0;
						valorNumerico = 1;
						for (int dadoA = 0; dadoA<DADOS and finalizar == 0; dadoA++){
							if (valorA == tirada[dadoA]){
								cantidadDadosA++;
							}
							if (dadoA == (DADOS-1)){
								
								for (int valorB = 1; valorB <= 6 and valorNumerico == 1; valorB++){
									int cantidadDadosB = 0;
									for (int dadoB = 0; dadoB<DADOS and valorNumerico == 1; dadoB++){
										if (valorB == tirada[dadoB]){
											cantidadDadosB++;
										}
										if(dadoB == (DADOS-1) and (((cantidadDadosA < cantidadDadosB or (cantidadDadosA == cantidadDadosB and valorA > valorB)) and puntos[valorB-1][jugador] == 99) or cantidadDadosA == 0)){
											valorNumerico = 0;
										}
									}
								}
								
								if (valorNumerico == 1 and puntos[valorA-1][jugador] == 99){
									puntos[valorA-1][jugador] = (cantidadDadosA*valorA);
									cout << "valor num"<<s('é')<<"rico " << valorA << " - " << puntos[valorA-1][jugador] << " puntos" << endl;
									finalizar = 1;
								} else {
									valorNumerico = 0;
								}
								
							}
							
						}
					}
					
					//Estructura de seleccion que determina si debe tacharse algun juego
					if (valorNumerico == 0) {
						
						for (int filas = (JUEGOS-1); filas >= 0; filas--){
							if (puntos[filas][jugador] == 99) {
								puntos[filas][jugador] = 0;
								cout << "se tacha el juego ";
								switch (filas){
								case 0:
									cout << "valor num"<<s('é')<<"rico 1";
									break;
								case 1:
									cout << "valor num"<<s('é')<<"rico 2";
									break;
								case 2:
									cout << "valor num"<<s('é')<<"rico 3";
									break;
								case 3:
									cout << "valor num"<<s('é')<<"rico 4";
									break;
								case 4:
									cout << "valor num"<<s('é')<<"rico 5";
									break;
								case 5:
									cout << "valor num"<<s('é')<<"rico 6";
									break;
								case 6:
									cout << "escalera";
									break;
								case 7:
									cout << "full";
									break;
								case 8:
									cout << "p"<<s('ó')<<"ker";
									break;	
								case 9:
									cout << "generala";
									break;
								};
								filas = -1;
							}
						}
						
					}
				}
			}
		}
	}
	
	//Estructura iterativa que suma los puntos obtenidos por el jugador o computadora hasta el momento
	for (int filas = 0; filas < JUEGOS; filas++){
		if (puntos[filas][jugador] != 99) {
			puntajeTotal += puntos[filas][jugador];
		}
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
	cout << "Valor num"<<s('é')<<"rico 1";
	centrar(16,10,1);
	cout << "Valor num"<<s('é')<<"rico 2";
	centrar(16,12,1);
	cout << "Valor num"<<s('é')<<"rico 3";
	centrar(16,14,1);
	cout << "Valor num"<<s('é')<<"rico 4";
	centrar(16,16,1);
	cout << "Valor num"<<s('é')<<"rico 5";
	centrar(16,18,1);
	cout << "Valor num"<<s('é')<<"rico 6";
	centrar(8,20,1);
	cout << "Escalera";
	centrar(4,22,1);
	cout << "Full";
	centrar(5,24,1);
	cout << "P"<<s('ó')<<"ker";
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
		cout <<s('¡')<<"GANASTE!" << endl;
		guardar_partida(4,puntajeTotalJugador,puntajeTotalComputadora,1,duracion);
	} else {
		if (puntajeTotalComputadora == puntajeTotalJugador){
			cout <<s('¡')<<"EMPATE!" << endl;
			guardar_partida(4,puntajeTotalJugador,puntajeTotalComputadora,3,duracion);
		} else {
			color(rojo);
			cout <<s('¡')<<"PERDISTE!" << endl;
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


