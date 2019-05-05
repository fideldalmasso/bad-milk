#include <fstream>
#include <iostream>

#include "ranking.h"
#include "ingreso_usuarios.h"
#include "funciones_utiles.h"
#include "encriptacion.h"

using namespace std;

void menu_ranking();
void ordenar_rank(RegistroDeRank A[], int n);
void guardar_partida(int id, int score, int pc_score, int result, int time);
RegistroDeRank * cargar_rank(int id);
void mostrar_rank(int id);

void menu_ranking(){
	char opcion;
	
	do{
		limpiar_pantalla();
		gotoxy(0,8);
		colorear(verde,"  VER RANKING\n\n");
		centrar("1.- FriCal                  ");
		centrar("2.- PiPaTi                  ");
		centrar("3.- Generala b"+s('á')+"sica         ");
		centrar("4.- Generala avanzada       ");
		centrar("5.- Ahorcado                ");
		centrar("6.- ParEs                   ");
		centrar("7.- Batalla Naval           ");
		colorear(rojo,"  9.- Volver al men"+s('ú')+" principal\n\n");
		colorear(amarillo,"Escrib"+s('í')+" un n"+s('ú')+"mero y presion"+s('á')+" Enter");
		
		gotoxy(0,22);
		cin >> opcion;
		while(opcion!='1' and opcion!='2' and opcion!='3' and opcion!='4' and opcion!='5' and opcion!='6' and opcion!='7' and opcion!='9'){
			gotoxy(0,21);
			colorear(amarillo," El n"+s('ú')+"mero ingresado es incorrecto, intent"+s('á')+" de nuevo\n");
			cin>>opcion;
		}
		
		switch(opcion){
		case '1':
			mostrar_rank(1);
			break;
		case '2':
			mostrar_rank(2);
			break;
		case '3':
			mostrar_rank(3);
			break;	
		case '4':
			mostrar_rank(4);
			break;	
		case '5':
			mostrar_rank(5);
			break;	
		case '6':
			mostrar_rank(6);
			break;
		case '7':
			mostrar_rank(7);
			break;	
		}
		
	}while(opcion != '9');
}

void guardar_partida(int id, int score, int pc_score, int result, int time){
	
	encriptar("data/log/rank_"+to_string(id));
	ofstream archivo ("data/log/rank_"+to_string(id)+".dat",ios::out | ios::app);
	
	archivo << actual.nombre << " " << score << "\n";
	
	archivo.close();
	encriptar("data/log/rank_"+to_string(id));
	
	encriptar("data/log/stats_"+actual.nombre);
	ofstream archivo2 ("data/log/stats_"+actual.nombre+".dat",ios::out | ios::app);
	
	archivo2 << id  << " " << score << " ";
	archivo2 << pc_score << " " <<result << " " << time << "\n";
	
	archivo2.close();
	encriptar("data/log/stats_"+actual.nombre);
}


void mostrar_rank(int id){
	
	
	int cant_partidas = contar_lineas("data/log/rank_"+to_string(id)+".dat");
	
	resize(60,30);
	limpiar_pantalla();
	gotoxy(0,5);
	colorear(verde, "MEJORES PUNTACIONES");
	switch(id){
	case 1:
		colorear(verde, "FRICAL");
		break;
	case 2:
		colorear(verde, "PIPATI");
		break;
	case 3:
		colorear(verde, "GENERALA");
		break;
	case 4:
		colorear(verde, "GENERALA AVANZADA");
		break;
	case 5:
		colorear(verde, "AHORCADO");
		break;
	case 6:
		colorear(verde, "PARES");
		break;
	case 7:
		colorear(verde, "BATALLA NAVAL");
		break;
	};
	
	gotoxy(20,9);
	colorear(amarillo,"N"+s('°')+" NOMBRE    PUNTAJE",0);
	
	RegistroDeRank * lista = cargar_rank(id);
	
	ofstream archivo ("data/log/rank_"+to_string(id)+".dat", ios::trunc);
	
	ordenar_rank(lista,cant_partidas);               //ordena de mayor a menor
	
	int mostrar=10;
	if(cant_partidas<10)
		mostrar=cant_partidas;

	
	for(int i=0;i<mostrar;i++){
		gotoxy(20,11+i);
		cout << i+1 << ". ";
		gotoxy(23,11+i);
		cout << lista[i].nickname;
		gotoxy(35,11+i);
		cout << lista[i].score;
		archivo << lista[i].nickname << " " << lista[i].score << "\n";
	}
	
	archivo.close();
	encriptar("data/log/rank_"+to_string(id));
	delete[] lista;

	gotoxy(0,28);
	pausa(1);
	limpiar_pantalla();	
}


//funciones complementarias
void ordenar_rank(RegistroDeRank A[], int n){
	for (int i=1; i<n; i++){
		RegistroDeRank key = A[i];
		int indice = i;
		while(indice>0 and key.score<A[indice-1].score){
			A[indice] = A[indice-1];
			indice--;
		}
		A[indice] = key;
	}
	
	RegistroDeRank * aux = new RegistroDeRank[n];          //los ordeno de mayor a menor
	for(int i=0; i<n; i++){
		aux[i] = A[n-i-1] ;
	}
	
	for(int i=0; i<n; i++){
		A[i] = aux[i];
	}
	
	delete[] aux;
	
}
RegistroDeRank * cargar_rank(int id){
	
	encriptar("data/log/rank_"+to_string(id));
	
	fstream archivo ("data/log/rank_"+to_string(id)+".dat",ios::in | ios::out | ios::app);
	
	int tam = contar_lineas("data/log/rank_"+to_string(id)+".dat");
	
	RegistroDeRank * tabla = new RegistroDeRank[tam];
	
	for(int i=0; i<tam; i++){
		archivo >> tabla[i].nickname >> tabla[i].score;
	}
	
	archivo.close();
	encriptar("data/log/rank_"+to_string(id));
	return tabla;
}
