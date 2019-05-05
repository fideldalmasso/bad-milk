#include <fstream>
#include <iostream>
#include <cstring>
#include <ctime>

#include "funciones_utiles.h"
#include "encriptacion.h"
#include "ingreso_usuarios.h"

#if defined (_WIN32) || defined (WIN32)
	#define windows
#endif


#define ANCHO 60

void encriptar(string nombre);
void cargar_key();

char key[4];


void cargar_key(){	
//carga la key de encriptación o bien la genera por primera vez

	ifstream archivo ("data/opt/key.dat");
	
	if (archivo) {
		
		string cadena;
		archivo >> cadena;
		for(int i=0; i<4; i++){
			cadena[i]--;
		}
		strcpy(key,cadena.c_str());
		
	}
	else{
		
#ifdef windows
		bienvenida();
#endif
		ofstream archivo1 ("data/opt/key.dat");

		for(int i=0; i<4; i++){
			key[i] = (rand()%25)+65;
	
		}
		
		char key2[4];
		strcpy(key2, key);
		for(int i=0; i<4; i++){
			key2[i]++;
		}
		archivo1 << key2;
		
		archivo1.close();
		
		//creo los archivos de rank
		
		for(int i=1; i<8; i++){      							    
			ofstream archivo2 ("data/log/rank_"+to_string(i)+".dat");
			archivo2.close();
		}
		
	}
	archivo.close();
	
}


void encriptar(string nombre){			
	
	//encriptación XOR de archivos
	
	ifstream archivo (nombre+".dat");
	ofstream archivo2 ("data/temp.dat");
	
	archivo2 << archivo.rdbuf();
	
	int tam = contar_lineas(nombre+".dat");
	
	
	archivo.close();
	archivo2.close();
	
	ofstream archivo3 (nombre+".dat", ios::trunc);
	ifstream archivo4 ("data/temp.dat");
	
	string cadena;
	for (int i = 0; i < tam; i++){
		getline(archivo4, cadena);

		for (int i = 0; i < (signed)cadena.size(); i++){
			cadena[i] = cadena[i] ^ key[i % 4];
		}
		archivo3 << cadena << "\n";
		
	}
	
	archivo3.close();
	archivo4.close();
	remove("data/temp.dat");
}
