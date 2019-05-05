#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <stdlib.h>

#include "generala.h"
#include "funciones_utiles.h"
#include "ranking.h"

#define ANCHO 125

using namespace std;

void generala();
void menu();
void jugargenerala();                       // el juego en sí
void instruccionesgenerala();                  // muestra los posibles juegos durante una partida de Generala
void pintardado(int num);                // dibuja en pantalla un único dado
void animaciondado(int numero, int posiciony);      // crea el efecto de que se lanzan los dados
void ordenardados(int &dado1, int &dado2, int &dado3);  //ordena los dados de menor a mayor

void generala() {
	char opcion='0'; 
	limpiar_pantalla();
	
	do{
		resize(ANCHO,33);  
		menu();
		cin >> opcion;
		
		while (opcion!='1' && opcion!='2' && opcion!='9'){      //en caso de una entrada inválida
			gotoxy(0,20);
			colorear(amarillo," El n"+s('ú')+"mero ingresado es incorrecto, por favor, intente nuevamente\n");
			cin >> opcion;
		}
		
		limpiar_pantalla();
		
		switch(opcion){
		case '1':
			jugargenerala();
			gotoxy(0,34);
			pausa();
			mostrar_rank(3);
			break;
			
		case '2':
			instruccionesgenerala();
			gotoxy(0,34);
			break;
		}
		
	} while(opcion!='9');
	
	
}
void menu(){
	limpiar_pantalla();
	cout << "\n";
	centrar("- Categor"+s('í')+"a juegos num"+s('é')+"ricos -");
	gotoxy(0,3);
	leerarchivo("generala_basica_titulo.txt",azul);
	cout << "\n\n";
	dormir(300);
	colorear("amarillo",s('¡')+"Presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!\n");
	dormir(200);
	centrar("1."+s('¡')+"A jugar!");
	dormir(200);
	centrar("2."+s('¿')+"C"+s('ó')+"mo se juega?");
	dormir(200);
	colorear("rojo","9. Volver al men"+s('ú')+" de juegos");
}

void jugargenerala(){
	auto comienzo = chrono::steady_clock::now();
	
	int dado1, dado2, dado3;                        //dado1, dado2 y dado3 representan cada uno de los 3 dados
	bool turno;                         //si turno = true, entonces es el turno del jugador
	int suma, puntajejugador, puntajepc;
	suma = puntajejugador = puntajepc = 0;
//	srand(time(0));                     // generación de seed para número aleatorio
	
	do{
		limpiar_pantalla();
		cout << "Se arrojan los dados para ver qui"<<s('é')<<"n empieza" << endl;
		
		dado1 = (rand()%6)+1;
		dado2 = (rand()%6)+1;
		
		dormir (300);
		animaciondado(dado1,3);
		gotoxy(8,5);
		cout << "Jugador: " << dado1 << endl;
		animaciondado(dado2,8);
		gotoxy(8,10);
		cout << "Computadora: " << dado2 << endl;
		
		dormir(300);
		
		gotoxy(0,14);
		if (dado1==dado2){
			cout << "Empate! Los dados vuelven a lanzarse\n" << endl;
			dado1 = dado2 =  0;
			gotoxy(0,33);
			pausa();
		}
		else if(dado1>dado2){
			gotoxy(0,15);
			cout << "Empez"<<s('á')<<"s vos!\n" << endl;
			turno = true;
		}
		else{
			gotoxy(0,15);
			cout << "La computadora empieza\n" << endl;
			turno = false; 
		}
	}while(dado1==dado2);
	
	gotoxy(0,33);
	pausa();
	
	
	for (int y=1; y<=20; y++){                     // Son 10 intentos por cada jugador, 20 en total
		limpiar_pantalla();
		
		dado1 = (rand()%6)+1;
		dado2 = (rand()%6)+1;
		dado3 = (rand()%6)+1;
		
		
		cout << "Intento n"<<s('°')<<" " << (y/2)+(y%2) << endl;                
		if (turno){
			cout << "Es tu turno. Lanz"<<s('á')<<" los dados" << endl;
		}
		else {
			cout << "Es el turno de la computadora. Se lanzan los dados" << endl;
		}
		dormir (300);
		cout << endl;
		animaciondado(dado1,3);
		animaciondado(dado2,8);
		animaciondado(dado3,13);
		
		cout << "\n\nSe obtuvo: " << dado1 << " " << dado2 << " " << dado3 << endl;
		dormir(300);
		
		if (dado1==dado2&&dado2==dado3){
			suma=50;
			cout << "Generala! Se suman 50 puntos\n\n" << endl;
		}
		else if (dado1==dado2||dado2==dado3||dado1==dado3){
			if (dado1==dado2||dado1==dado3){
				suma=2*dado1;
				cout << "El " << dado1 << " sali"<<s('ó')<<" dos veces. Se suman " << suma << " puntos\n\n" << endl;
				
			}
			else if (dado2==dado3){
				suma=2*dado2;
				cout << "El " << dado2 << " sali"<<s('ó')<<" dos veces. Se suman " << suma << " puntos\n\n" << endl;
			}
		}
		else {        
			ordenardados(dado1, dado2, dado3);
			
			if (dado1==(dado2-1)&&dado3==(dado2+1)){
				suma=25;
				cout << "Escalera! Se suman 25 puntos\n\n" << endl;
			}
			else {
				cout << "No se forma ninguna jugada. No se suman puntos\n\n" << endl;
			}
		}
		
		if(turno){
			puntajejugador+=suma;
			turno=false;
		}
		else{
			puntajepc+=suma;
			turno=true;
		}
		suma=0;
		dormir(300);
		colorear(verde,"Tus puntos: "+to_string(puntajejugador)+"\n",0);
		dormir(300);
		colorear(verde,"Puntaje computadora: "+to_string(puntajepc)+"\n",0);
		dormir(300);
		gotoxy(0,33);
		pausa();
	}
	limpiar_pantalla();
	gotoxy(0,15);
	int duracion = (chrono::steady_clock::now() - comienzo)/chrono::seconds(1);
	
	if(puntajejugador==puntajepc){
		colorear(azul,"Empate! "+s('¿')+"Quer"+('é')+"s volver a intentar?");
		guardar_partida(3,puntajejugador,puntajepc,3,duracion);
	}
	else if (puntajejugador>puntajepc){
		colorear(verde,"Ganaste! Muy bien hecho. "+s('¿')+"Jugamos otra vez?");
		guardar_partida(3,puntajejugador,puntajepc,1,duracion);
	}
	else{ 
		colorear(rojo,"Perdiste! Pero pod"+s('é')+"s volver a intentarlo...");
		guardar_partida(3,puntajejugador,puntajepc,2,duracion);
	}
}

void instruccionesgenerala(){
	limpiar_pantalla();
	cout << "\n";
	centrar("INSTRUCCIONES\n");
	leerarchivo("generala_basica_instrucciones.txt");
	cout << "\n";
	pausa(1);
	limpiar_pantalla();
	
}

void pintardado(int num){ // imprime en pantalla un único dado
	centrar(" ----- ");
	switch(num){
	case 1:
		centrar("|     |");
		centrar("|  o  |");
		centrar("|     |");
		break;
	case 2:
		centrar("|o    |");
		centrar("|     |");
		centrar("|    o|");
		break;
	case 3:
		centrar("|o    |");
		centrar("|  o  |");
		centrar("|    o|");
		break;
	case 4:
		centrar("|o   o|");
		centrar("|     |");
		centrar("|o   o|");
		break;
	case 5:
		centrar("|o   o|");
		centrar("|  o  |");
		centrar("|o   o|");
		break;
	case 6:
		centrar("|o   o|");
		centrar("|o   o|");
		centrar("|o   o|");
	}
	centrar(" ----- ");
}

void animaciondado(int numero, int posiciony){ /* 
	En la variable numero se almacena un valor de dado aleatorio generado previamente.
	La variable posiciony determina justamente, el lugar de la pantalla en donde se mostrará la animación
	*/
	for(int p=0; p<6; p++){ // se muestra aleatoriamente un dado "falso", seis veces seguidas
		gotoxy(0,posiciony);
		int num = (rand()%6)+1;
		pintardado(num);
		dormir(200);
	}
	gotoxy(0,posiciony);
	pintardado(numero);          // finalmente se imprime el dado ya antes generado 
}

void ordenardados(int &dado1, int &dado2, int &dado3){
	if (dado1 > dado2){
		swap(dado1, dado2);
	}
	if (dado2 > dado3){
		swap(dado2, dado3);
	}
	if (dado1 > dado2){
		swap(dado1, dado2);
	}
}
