#include <fstream>
#include <iostream>
#include <cstring>
#include <ctime>
#include <string>

#include "ingreso_usuarios.h"
#include "funciones_utiles.h"
#include "encriptacion.h"
#include "ranking.h"

#define ANCHO 60

using namespace std;

bool menu_ingreso();
bool registrar_usuario();
bool iniciar_sesion();
void guardar_usuario_predeterminado();
bool cargar_usuario_predeterminado();
void cambiar_contrasenia();
bool eliminar_cuenta();
string escribir_contrasenia(int y);
bool tiene_espacios(string x);
usuario * cargar_usuarios();
int buscar_nombre(usuario tabla[], string nombre, int tam);
bool cerrar_sesion();
usuario actual;

//funciones principales
bool menu_ingreso(){							
	//controla registros e inicios de sesión
	
	resize(60,30);
	cargar_key();
	
	if(cargar_usuario_predeterminado())
		return true;
	char opcion;
	do{
		actual = {"",""};
		limpiar_pantalla();
		gotoxy(0,8);
		colorear(verde,"  - Ingreso -\n\n");
		colorear(amarillo,"Eleg"+s('í')+" una opci"+s('ó')+"n:");
		centrar("1. Crear un usuario nuevo");
		centrar("2. Iniciar sesi"+s('ó')+"n        ");
		colorear(rojo,"9. Salir                 ");
		gotoxy(0,15);
		cin >> opcion;
		
		
		while(opcion!='1' and opcion!='2' and opcion!='9'){
			colorear(amarillo,"\n\nEl n"+s('ú')+"mero ingresado es incorrecto, intente de nuevo  ");

			gotoxy(0,15);
			cout << "              \r";
			cin >> opcion;
		}
		cin.ignore();
		switch(opcion){
		case '1':																
			if(registrar_usuario())
				return true;
			break;
		case '2':																
			if(iniciar_sesion())
				return true;
		}
	}while (opcion!= '9');
	return false;

}

bool registrar_usuario(){
	limpiar_pantalla();
	usuario * tabla = cargar_usuarios();
	
	gotoxy(0,27);
	colorear(amarillo,"Ayuda: si quer"+s('é')+"s cancelar la operaci"+s('ó')+"n, escrib"+s('í')+" 9");
	
	gotoxy(0,8);
	colorear(verde,"  - Crear un usuario nuevo -\n\n");
	centrar("Escrib"+s('í')+" tu nombre: ");
	int posicion=-1;
	int tam = contar_lineas("data/opt/users.dat");
	bool invalido;
	do{
		gotoxy(ANCHO/3,12);
		cout << "                         ";
		gotoxy(ANCHO/3,12);
		color("verde");
		
		getline(cin,actual.nombre);
		color("blanco");
	
		if(actual.nombre=="9"){
			delete[] tabla; 
			return false;
		}
		gotoxy(0,13);
		
		invalido = false;
		invalido = tiene_espacios(actual.nombre);
	
		if(actual.nombre.size()>10){
			colorear(amarillo,"      Tu nombre debe tener menos de 10 caracteres      ");
		}
		else if(invalido){
			colorear(amarillo,"   Tu nombre no puede contener espacios o estar vac"+s('í')+"o   ");
		}
		else{
			posicion = buscar_nombre(tabla,actual.nombre,tam);
			if(posicion>=0){
				
				colorear(amarillo,"      El usuario ya est"+s('á')+" en uso, ingres"+s('á')+" otro      ");
			}
		}
	} while(posicion>=0 or invalido);
	
	delete[] tabla;   
	
	gotoxy(0,13);
	centrar("                                                      ");
	
	gotoxy(0,15);
	centrar("Ingres"+s('á')+" la contrase"+s('ñ')+"a\n");
	do{
		actual.contra = escribir_contrasenia(17);
		
		if(actual.contra=="9"){
			return false;
		}
		
		invalido = tiene_espacios(actual.contra);
		
		gotoxy(0,18);
		if(invalido){
			colorear(amarillo, "La contrase"+s('ñ')+"a no puede contener espacios o estar vac"+s('í')+"a");
		}
		
	} while(invalido);
	
	
	encriptar("data/opt/users");
	ofstream archivo ("data/opt/users.dat", ios::app);
	archivo << actual.nombre << " " << actual.contra << "\n";
	archivo.close();
	encriptar("data/opt/users");
	
	ofstream archivo2("data/log/stats_"+actual.nombre+".dat");
	archivo2.close();
	
	limpiar_pantalla();
	gotoxy(0,15);
	colorear(verde,"     Usuario creado correctamente\n\n\n\n\n");

	pausa(1);
	guardar_usuario_predeterminado();
	return true;
}

bool iniciar_sesion(){
	limpiar_pantalla();
	usuario * tabla = cargar_usuarios();
	int tam = contar_lineas("data/opt/users.dat");
	
	if(tam==0){
		gotoxy(0,15);
		colorear(rojo,"  No se cargaron usuarios todav"+s('í')+"a\n\n");
		delete[] tabla;
		pausa(1);
		return false;
	}
	else{
		gotoxy(0,28);
		colorear(amarillo,"Ayuda: si quer"+s('é')+"s cancelar la operaci"+s('ó')+"n, escrib"+s('í')+" 9");
		
		
		gotoxy(0,8);
		colorear(verde,"  - Iniciar sesi"+s('ó')+"n -\n\n");
		centrar("Escrib"+s('í')+" tu nombre: ");
		int posicion;
		do{
			gotoxy(ANCHO/3,12);
			cout << "                         ";
			gotoxy(ANCHO/3,12);
			color("verde");
			cin >> actual.nombre;
			color("blanco");
			
			if(actual.nombre=="9"){
				delete[] tabla;
				return false;
			}
			posicion = buscar_nombre(tabla,actual.nombre,tam);
			if(posicion<0){
				gotoxy(0,13);
				colorear(amarillo,"El usuario no existe, prob"+s('á')+" con otro ");
				
			}
		} while(posicion<0);
		gotoxy(0,13);
		centrar("                                        ");
		
		gotoxy(0,15);
		centrar("Y tu contrase"+s('ñ')+"a\n");
		actual.contra = escribir_contrasenia(17);
		
		int intentos=3;
		while(tabla[posicion].contra!=actual.contra and intentos!=1){
			if(actual.contra=="9"){
				delete[] tabla;
				return false;
			}
			
			color("amarillo");
			centrar("Contrase"+s('ñ')+"a inv"+s('á')+"lida");
			intentos--;
			if(intentos!=1)
				centrar("Te quedan dos intentos m"+s('á')+"s");
			else
				centrar("    Te queda un intento m"+s('á')+"s    ");
		
			color("blanco");
			gotoxy(0,3);
			cout << "                   \r";
			actual.contra = escribir_contrasenia(17);
			
		}
		
		if(intentos==1){
			delete[] tabla;
			limpiar_pantalla();
			gotoxy(0,15);
			
			centrar("Cancelamos el inicio de sesi"+s('ó')+"n por seguridad");
			gotoxy(0,28);
			pausa(1);
			return false;
		}
		gotoxy(0,18);
		centrar("                               ");
		centrar("                             \n");
		colorear(verde,"Iniciaste sesi"+s('ó')+"n correctamente");
		gotoxy(0,28);
		pausa(1);
		guardar_usuario_predeterminado();
		return true;
	}
}




void guardar_usuario_predeterminado(){
	limpiar_pantalla();
	char opcion = '0';
	gotoxy(0,13);
	color("amarillo");
	centrar(s('¿')+"Quer"+s('é')+"s que guardemos tus datos para ");
	centrar(" que accedas r"+s('á')+"pidamente la pr"+s('ó')+"xima vez?\n");
	color("blanco");
	centrar("1.Si");
	centrar("2.No");
	gotoxy(0,19);
	cin>>opcion;
	while(opcion!='1' and opcion!='2'){
		colorear(amarillo,"El n"+s('ú')+"mero ingresado es inv"+s('á')+"lido");
		gotoxy(0,19);
		cin >> opcion;
	}
	if(opcion=='1'){
		ofstream archivo ("data/opt/default.dat", ios::trunc);
		archivo << actual.nombre << " " << actual.contra;
		archivo.close();
		encriptar("data/opt/default");
		limpiar_pantalla();
		gotoxy(0,15);
		colorear(verde,s('¡')+"Listo!");
		gotoxy(0,20);
		pausa(1);
	}
	else{
		remove("data/opt/default.dat");
	}
	limpiar_pantalla();
}
bool cargar_usuario_predeterminado(){
	
	//si no existe el archivo default.dat
	ifstream archivo ("data/opt/default.dat");
	if(!archivo){
		archivo.close();
		return false;
	}
	archivo.close();
	
	//si existe default.dat
	
	encriptar("data/opt/default");
	ifstream archivo2("data/opt/default.dat");
	archivo2 >> actual.nombre >> actual.contra;
	archivo2.close();
	encriptar("data/opt/default");
	
	//si existe default.dat, pero está vacío o está corrupto
	
	usuario * tabla = cargar_usuarios();
	int tam = contar_lineas("data/opt/users.dat");

	
	if(buscar_nombre(tabla,actual.nombre,tam)==-1){
		
		remove("data/opt/default.dat");
		delete[] tabla;
		
		limpiar_pantalla();
		gotoxy(0,15);
		colorear(rojo,"La carga autom"+s('á')+"tica de usuario fall"+s('ó'));
		colorear(rojo,"  Eliminamos data/opt/default.dat porque est"+s('á')+" da"+s('ñ')+"ado\n\n");
		pausa(1);
		
		return false;
	}

	delete[] tabla;
	
	//caso exitoso:
	
	return true;
	
}
void cambiar_contrasenia(){
	
	limpiar_pantalla();
	string aux_contra;
	gotoxy(0,27);
	colorear(amarillo,"Ayuda: si quer"+s('é')+"s cancelar la operaci"+s('ó')+"n, escrib"+s('í')+" 9");
	bool invalido = false;
	
	gotoxy(0,8);
	colorear(rojo, " - Cambiar contrase"+s('ñ')+"a -\n");
	centrar("Ingres"+s('á')+" la contrase"+s('ñ')+"a nueva\n");
	
	do{
		aux_contra = escribir_contrasenia(13);
		
		if(aux_contra=="9"){
			return;
		}
		
		invalido = tiene_espacios(aux_contra);
		
		gotoxy(0,15);
		if(invalido){
			colorear(amarillo, "La contrase"+s('ñ')+"a no puede contener espacios o estar vac"+s('í')+"a");
		}
		
	} while(invalido);
	
	int tam = contar_lineas("data/opt/users.dat");
	usuario * tabla = cargar_usuarios();
	int i=0;
	while(tabla[i].nombre!=actual.nombre){
		i++;
	}
	tabla[i].contra = aux_contra;
	actual.contra = aux_contra;
	
	ofstream archivo ("data/opt/users.dat", ios::trunc);
	for(int i=0; i<tam; i++){
	archivo << tabla[i].nombre << " " << tabla[i].contra << "\n";
	}
	archivo.close();
	encriptar("data/opt/users");
	
	limpiar_pantalla();
	gotoxy(0,15);
	colorear(verde,"     Contrase"+s('ñ')+"a cambiada correctamente\n\n\n\n\n");
	pausa(1);
	delete[] tabla;
	guardar_usuario_predeterminado();
	
}

bool eliminar_cuenta(){
	
	limpiar_pantalla();
	gotoxy(0,8);
	colorear(rojo,"!!!");
	colorear(rojo,"- ELIMINAR CUENTA -\n");
	colorear(rojo, s('¿')+"Est"+s('á')+"s seguro que quer"+s('é')+"s hacer esto?");
	colorear(rojo, "Todos tus datos ser"+s('á')+"n borrados");
	colorear(rojo, " Y no vas a poder iniciar sesi"+s('ó')+"n con tu nombre\n");
	colorear(rojo, "   Esta acci"+s('ó')+"n no puede deshacerse\n\n\n");
	
	colorear(rojo,"Para borrar tu cuenta, escrib"+s('í')+" SI (en may"+s('ú')+"sculas)");
	
	string confirmacion ="";
	gotoxy(0,22);
	cin.ignore();
	getline(cin,confirmacion);
	
	if(confirmacion=="SI"){
		
		//eliminar cuenta predeterminada
		remove("data/opt/default.dat");
		
		//eliminar estadisticas
		string cadena = "data/log/stats_"+actual.nombre+".dat";
		remove(cadena.c_str());				            			
		
		//eliminar registros de ranking
		for(int p=1; p<8;p++){									
			int tam = contar_lineas("data/log/rank_"+to_string(p)+".dat");
			
			RegistroDeRank * lista = cargar_rank(p);
			ofstream archivo ("data/log/rank_"+to_string(p)+".dat", ios::trunc);
			
				for(int x=0; x<tam; x++){
					if(lista[x].nickname!=actual.nombre){
						archivo << lista[x].nickname << " " << lista[x].score << "\n";
					}
				}
				archivo.close();
				encriptar("data/log/rank_"+to_string(p));
				delete[] lista;
		}		
		
		//eliminar usuario y contraseña de users.dat
		int tam = contar_lineas("data/opt/users.dat");
		usuario * tabla = cargar_usuarios();
		int i=0;
		while(tabla[i].nombre!=actual.nombre){
			i++;
		}
		
		ofstream archivo2 ("data/opt/users.dat", ios::trunc);
		for(int j=0; j<tam; j++){
			if(j!=i){
			archivo2 << tabla[j].nombre << " " << tabla[j].contra << "\n";
			}
		}
		archivo2.close();
		encriptar("data/opt/users");
		delete[] tabla;
		
		
		actual = {"",""};
		//borrado finalizado
		
		
		limpiar_pantalla();
		gotoxy(0,15);
		colorear(verde,"Tu cuenta se elimin"+s('ó')+" correctamente");
		gotoxy(0,27);
		pausa(1);
		return true;
		
	}
	else{
		limpiar_pantalla();
		gotoxy(0,15);
		colorear(verde,actual.nombre+"...");
		colorear(verde,"Tu cuenta est"+s('á')+" intacta");
		gotoxy(0,27);
		pausa(1);
		return false;
	}
	return false;
};
bool cerrar_sesion(){
	limpiar_pantalla();
	
	ifstream archivo ("data/opt/default.dat");
	
	if(archivo){
		archivo.close();
		if(remove("data/opt/default.dat")!=0){
			gotoxy(0,10);
			colorear(rojo," Error: no se pudo borrar data/opt/default.dat\n");
			colorear(rojo,"Pod"+s('é')+"s eliminarlo manualmente o ");
			colorear(rojo," probar lo siguiente y volver a intentar:\n");
			colorear(rojo,"1.Cerrar todos los programas abiertos");
			colorear(rojo,"2.Desactivar temporalmente tu antivirus");
			gotoxy(0,27);
			pausa(1);
			return false;
		}
	}
	archivo.close();
	gotoxy(0,15);
	colorear(verde,"Cerraste sesi"+s('ó')+"n correctamente "+actual.nombre);
	actual = {"",""};
	gotoxy(0,27);
	pausa(1);
	return true;
}
//funciones complementarias a continuación
string escribir_contrasenia(int y){		
	//para dar el efecto de que se escribe una contraseña de verdad
	string x;
	int c;
	int i=0;
	gotoxy(ANCHO/3,y);
	cout << "                         ";
	gotoxy(ANCHO/3,y);
	color("verde");
	while ((c = getchx()) != 13 and c!=10){
		
		if(c==8 or c==127){
			if(x.size()!=0){
				x.resize(x.size()-1);
				i--;
			}
		}
		else{
			x +=c;
			i++;
		}
		gotoxy(ANCHO/3,y);
		cout<<"                      ";
		gotoxy(ANCHO/3,y);
		for(int p=0; p<i; p++){
			
			cout<<"*";
		}
	}
	color("blanco");
	cout << endl;
	return x;
}
int buscar_nombre(usuario tabla[], string nombre,int tam){
	
	for(int i=0; i<tam; i++){
		if(tabla[i].nombre == nombre){
			return i;
		}
	}
	return -1;
}
bool tiene_espacios(string x){
	//detecta si un string tiene espacios
	
	if (strchr(x.c_str(),32)!=NULL or (x.size()==0))
		return true;
	else
		return false;
}
usuario * cargar_usuarios(){			
	//retorna un arreglo con la info de cada usuario
	
	encriptar("data/opt/users");
	fstream archivo ("data/opt/users.dat",ios::in | ios::out | ios::app);
	
	int tam = contar_lineas("data/opt/users.dat");
	
	usuario * tabla = new usuario[tam];
	
	for(int i=0; i<tam; i++){
		archivo >> tabla[i].nombre >> tabla[i].contra;
	}
	/*
	for(int i=0; i<tam; i++){
	cout << tabla[i].nombre << " " << tabla[i].contra;
	cout << endl;
	}
	*/
	archivo.close();
	encriptar("data/opt/users");
	return tabla;
	
}
