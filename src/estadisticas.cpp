#include <iostream>
#include <iomanip>

#include <estadisticas.h>
#include <funciones_utiles.h>
#include <ranking.h>
#include <ingreso_usuarios.h>
#include <encriptacion.h>

using namespace std;

void menu_estadisticas ();
void estadisticasGenerales ();

void estadisticas_frical();
void estadisticas_pipati();
void estadisticas_generala();
void estadisticas_generala_avanzada();
void estadisticas_ahorcado();
void estadisticas_pares();
void estadisticas_batalla_naval();

Partida * cargar_estadisticas();
void tiempo_max_min(int id);
void barra_victorias(int id);
void barra_versus(int id);
void grafico_barras (int cantidad,int x, int y, int porcentajes[]);
int redondear(int numero);
void barra(int porcentaje, int modo=1);

void merge1 (int vector1[], int inicio1, int fin1, int inicio2, int fin2);
void mergeSort (int vector[], int inicio, int fin);

int suma[7];
int victorias[7];
int partidas_jugadas[7];
int tiempos[3][7];
Partida * datos;
int tam;


Partida * cargar_estadisticas(){
	encriptar("data/log/stats_"+actual.nombre);
	fstream archivo ("data/log/stats_"+actual.nombre+".dat",ios::in | ios::out | ios::app);
	
	int tam = contar_lineas("data/log/stats_"+actual.nombre+".dat");
	
	Partida * tabla = new Partida[tam];
	
	for(int i=0; i<tam; i++){
		archivo >> tabla[i].id >> tabla[i].score;
		archivo >> tabla[i].pc_score >> tabla[i].result >> tabla[i].time;
	}
	
	archivo.close();
	encriptar("data/log/stats_"+actual.nombre);
	return tabla;
}

void menu_estadisticas (){
	tam=0;
	
	for(int i=0; i<7; i++){
		tiempos [0][i] = -1;
		tiempos[1][i] = -1;
		suma[i]=0;
		victorias[i]=0;
		partidas_jugadas[i]=0;
	}
	
	for(int i=0; i<7; i++){
		tiempos[2][i] = 0;
	}
	
	datos = cargar_estadisticas();
	tam = contar_lineas("data/log/stats_"+actual.nombre+".dat");
	char selector;
	
	
	for (int pos=0; pos<tam; pos++){
		
		int juego = datos[pos].id-1;
		int tiempo = datos[pos].time;
		tiempos[2][juego]+=tiempo;
		
		if(tiempos[0][juego]==-1 or tiempo<tiempos[0][juego]){
			tiempos[0][juego] = tiempo;
		}
		
		if(tiempos[1][juego]==-1 or tiempo>tiempos[1][juego]){
			tiempos[1][juego] = tiempo;
		}
		
		if(datos[pos].result==1){
			suma[datos[pos].id-1]+=datos[pos].score;
			victorias[datos[pos].id-1]++;
		}
		partidas_jugadas[datos[pos].id-1]++;
	}
	
	do {
		limpiar_pantalla();
		
		gotoxy(0,5);
		colorear(verde,"ESTAD"+s('Í')+"STICAS Y LOGROS\n");
		centrar("0. Estad"+s('í')+"sticas generales   ");
		centrar("1. Frical                   ");
		centrar("2. Pi-Pa-Ti                 ");
		centrar("3. Generala B"+s('á')+"sica          ");
		centrar("4. Generala Avanzada        ");
		centrar("5. Ahorcado                 ");
		centrar("6. ParEs                    ");
		centrar("7. Batalla Naval            ");
		colorear(rojo,"9. Volver al men"+s('ú')+" principal ");
		gotoxy(0,18);
		colorear(amarillo,s('¡')+"Presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!");
		gotoxy(30,19);
		cin >> selector;
		
		while(selector!= '0' and selector!= '1' and selector != '2' and selector != '3' and selector != '4' and selector != '5' and selector != '6' and selector != '7' and selector != '9'){
			gotoxy(0,18);
			colorear(amarillo,s('¡')+"PSSS, presion"+s('á')+" un n"+s('ú')+"mero y enter para elegir!");
			gotoxy(30,19);
			cout << "                                                            ";
			gotoxy(30,19);
			cin >> selector;
		}
		
		switch(selector){
		case '0':
			estadisticasGenerales();
			break;
		case '1':
			estadisticas_frical();
			break;
		case '2':
			estadisticas_pipati();
			break;
		case '3':
			estadisticas_generala();
			break;
		case '4':
			estadisticas_generala_avanzada();
			break;
		case '5':
			estadisticas_ahorcado();
			break;
		case '6':
			estadisticas_pares();
			break;
		case '7':
			estadisticas_batalla_naval();
			break;
		}
		
	} while(selector != '9');
	
}

void estadisticasGenerales (){
	
	limpiar_pantalla();
	if(tam==0){
		gotoxy(0,15);
		colorear(rojo, "Todav"+s('í')+"a no jugaste ninguna partida");
	}
	else{
	int total = 0;
	
	int arreglo[7];
	
	for(int i=0; i<7; i++){
		total+=tiempos[2][i];
		arreglo[i]=tiempos[2][i];
	};
	
	for(int i=0; i<7; i++){
		arreglo[i]=(arreglo[i]*100)/total;
		
	}
	
	cout<< "\n\n";
	colorear(celeste, "  TIEMPO QUE JUGASTE EN CADA JUEGO SOBRE EL TIEMPO TOTAL\n\n");
	cout <<"(1)Frical\n(2)PiPaTi\n(3)Generala\n";
	cout <<"(4)Generala A.\n(5)Ahorcado \n(6)ParEs \n(7)Batalla N.";
	
	grafico_barras(7,19,15,arreglo);
	gotoxy(21,16);
	color(blanco);
	cout << "(1)  (2)  (3)  (4)  (5)  (6)  (7)\n\n";
	
	colorear(celeste,"PROMEDIO DE PUNTAJES DE PARTIDAS GANADAS");
	gotoxy(20,20);
	cout << "Frical: ";
	
	if (victorias[0] != 0){
		cout << setprecision(2) << fixed << ((float)suma[0])/victorias[0];
	} else {
		cout << "---";
	}
	gotoxy(20,21);
	cout << "Pi-Pa-Ti: ";
	if (victorias[1] != 0){
		cout << setprecision(2) << fixed << ((float)suma[1])/victorias[1];
	} else {
		cout << "---";
	}
	gotoxy(20,22);
	cout << "Generala B"+s('á')+"sica: ";
	if (victorias[2] != 0){
		cout << setprecision(2) << fixed <<((float)suma[2])/victorias[2];
	} else {
		cout << "---";
	}
	gotoxy(20,23);
	cout << "Generala Avanzada: ";
	if (victorias[3] != 0){
		cout << setprecision(2) << fixed << ((float)suma[3])/victorias[3];
	} else {
		cout << "---";
	}
	gotoxy(20,24);
	cout << "Ahorcado: ";
	if (victorias[4] != 0){
		cout << setprecision(2) << fixed << ((float)suma[4])/victorias[4];
	} else {
		cout << "---";
	}
	gotoxy(20,25);
	cout << "ParEs: ";
	if (victorias[5] != 0){
		cout << setprecision(2) << fixed << ((float)suma[5])/victorias[5];
	} else {
		cout << "---";
	}
	gotoxy(20,26);
	cout << "Batalla Naval: ";
	if (victorias[6] != 0){
		cout << setprecision(2) << fixed << ((float)suma[6])/victorias[6];
	} else {
		cout << "---";
	}
	}
	gotoxy(0,28);
	pausa();
}


void estadisticas_frical(){
	
	limpiar_pantalla();
	if(partidas_jugadas[0]==0){
		gotoxy(0,15);
		colorear(rojo, "Todav"+s('í')+"a no jugaste ninguna partida");
		colorear(rojo, "de Frical");
	}
	else{
	
	bool logro=false;
	
	
	
	gotoxy(0,1);
	colorear(celeste, "  - ESTAD"+s('Í')+"STICAS FRICAL - \n");
	
	barra_victorias(1);
	
	cout << "\n\n";
	tiempo_max_min(1);
	cout << "\n\n\n\n";
	colorear(celeste, "- LOGROS FRICAL -");
	centrar("En verde, los que desbloqueaste\n");

	for(int i=0; i<tam; i++){
		if (datos[i].id == 1){
			if(datos[i].score == 10){
				logro = true;
			}
		}
	}
	
	if(logro){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar("On fire: adivinaste el n"+s('ú')+"mero en el primer intento");
	}
	gotoxy(0,28);
	pausa(1);
	
}


void estadisticas_pipati(){
	
	
	limpiar_pantalla();
	if(partidas_jugadas[1]==0){
		gotoxy(0,15);
		colorear(rojo, "Todav"+s('í')+"a no jugaste ninguna partida");
		colorear(rojo, "de PiPaTi");
	}
	else{
		
	
	bool logro1=false;
	bool logro2=false;
	
	
	gotoxy(0,1);
	colorear(celeste, "  - ESTAD"+s('Í')+"STICAS PIPATI - \n");
	
	barra_versus(2);
	
	cout << "\n\n";
	tiempo_max_min(2);
	cout << "\n\n\n\n";
	colorear(celeste, "- LOGROS PIPATI -");
	centrar("En verde, los que desbloqueaste\n");

	for(int i=0; i<tam; i++){
		if (datos[i].id == 2){
			if(datos[i].score == 5)
				logro1 = true;
			if(datos[i].result==3)
				logro2 = true;
		}
	}
	
	if(logro1){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar("Animal: Ganaste las cinco rondas de la partida\n");
	
	if(logro2){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar("Rivalidad: Empataste una partida");
	
	}
	gotoxy(0,28);
	pausa(1);
}
void estadisticas_generala(){
	
	limpiar_pantalla();
	if(partidas_jugadas[2]==0){
		gotoxy(0,15);
		colorear(rojo, "Todav"+s('í')+"a no jugaste ninguna partida");
		colorear(rojo, "de Generala");
	}
	else{
	
	
	
	bool logro1=false;
	int pc_victoria=0, partidas_jugadas=0;
	
	for(int i=0; i<tam; i++){
		if (datos[i].id == 3){
			if(datos[i].score > ((datos[i].pc_score)+50)){
				logro1 = true;
			}
			if(datos[i].score<datos[i].pc_score){
				pc_victoria++;
			}
			partidas_jugadas++;
		}
	}

	gotoxy(0,1);
	colorear(celeste, "  - ESTAD"+s('Í')+"STICAS GENERALA BASICA -\n");
	
	barra_versus(3);
	
	cout << "\n\n";
	tiempo_max_min(3);
	cout << "\n";
	
//	centrar("Porcentaje de partidas perdidas:\n");
//	
//	if(partidas_jugadas==0){
//		centrar("- - -",0);
//	}
//	else{
//		barra((pc_victoria*100)/partidas_jugadas);
//	}
	
	cout << "\n\n";
	colorear(celeste, "- LOGROS GENERALA B"+s('Á')+"SICA -");
	centrar("En verde, los que desbloqueaste\n");
	
	if(logro1){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar(s('Í')+"dolo/a: Ganaste con una diferencia de m"+s('á')+"s de 50 puntos\n");
	
}
	gotoxy(0,28);
	pausa(1);	
}

void estadisticas_generala_avanzada (){
	
	limpiar_pantalla();
	if(partidas_jugadas[3]==0){
		gotoxy(0,15);
		colorear(rojo, "Todav"+s('í')+"a no jugaste ninguna partida");
		colorear(rojo, "de Generala Avanzada");
	}
	else{
		
	
	bool logro1 = false;
	bool logro2 = false;
	int pc_victoria=0;
	
	for(int i=0; i<tam; i++){
		if(datos[i].score<datos[i].pc_score and datos[i].id==4){
			pc_victoria++;
		}
	}

	
	gotoxy(0,1);
	colorear(celeste, "  - ESTAD"+s('Í')+"STICAS GENERALA AVANZADA - \n");
	
	barra_versus(4);
	
	cout << "\n\n";
	tiempo_max_min(4);
	cout << "\n";
	centrar("Partidas ganadas por");
	centrar("-La computadora: ",0);
	cout << pc_victoria << "\n";
	centrar("-El jugador:     ",0);
	cout << victorias[3] << "\n\n\n\n";
	colorear(celeste, "- LOGROS GENERALA AVANZADA -");
	centrar("En verde, los que desbloqueaste\n");
	
	
	for(int i=0; i<tam; i++){
		if (datos[i].id == 4){
			if(datos[i].score > 180)
				logro1 = true;
			if((datos[i].pc_score - datos[i].score) >= 100)
				logro2 = true;
		}
	}
	//determinar logro
	
	if(logro1){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar("Hackerman: Gana obteniendo m"+s('á')+"s de 180 puntos\n");
	
	if(logro2){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar("No llores: Pierde por 100 o m"+s('á')+"s puntos\n");
	}
	
	gotoxy(0,28);
	pausa(1);
}

void estadisticas_ahorcado (){
	
	limpiar_pantalla();
	if(partidas_jugadas[4]==0){
		gotoxy(0,15);
		colorear(rojo, "Todav"+s('í')+"a no jugaste ninguna partida");
		colorear(rojo, "de Ahorcado");
	}
	else{
		bool logro1 = false;
		bool logro2 = false;
		int tam1 = partidas_jugadas[4];
		
		int * puntajes = new int [tam1];
		
		int i1=0;
		for (int i=0; i<tam; i++){
			if(datos[i].id==5){
				puntajes[i1]=(datos[i].score);
				i1++;
			}
		}
		mergeSort(puntajes, 0, tam1-1);
		
		gotoxy(0,1);
		colorear(celeste, "  - ESTAD"+s('Í')+"STICAS AHORCADO - \n");
		
		barra_victorias(5);
		
		cout << "\n\n";
		tiempo_max_min(5);
		cout << "\n";
		gotoxy(0,10);
		centrar("Los tres peores puntajes en el Ahorcado son:\n");
		
		for (int i=0; i<tam1 and i<3; i++){
			centrar(to_string(puntajes[i]));
		}
		if(3-tam1>0){
			for (int i=0; i<(3-tam1); i++){
				centrar("---");
			}
		}
		
		cout << "\n\n\n";
		colorear(celeste, "- LOGROS AHORCADO -");
		centrar("En verde, los que desbloqueaste\n");
		
		//determinar logro
		for(int i=0; i<tam; i++){
			if (datos[i].id == 5){
				if(datos[i].score == 32)
					logro1 = true;
				if(datos[i].score == 50)
					logro2 = true;
			}
		}
		
		if(logro1){
			color(verde);
		}else{
			color(gris);
		}
		centrar("Por un pie: Gana en la "+s('ú')+"ltima jugada\n");
		
		if(logro2){
			color(verde);
		}else{
			color(gris);
		}
		centrar("Ileso: Gana sin perder ninguna parte de tu cuerpo\n");
	}
	
	gotoxy(0,28);
	pausa(1);
}

void estadisticas_pares(){
	
	limpiar_pantalla();
	if(partidas_jugadas[5]==0){
		gotoxy(0,15);
		colorear(rojo, "Todav"+s('í')+"a no jugaste ninguna partida");
		colorear(rojo, "de ParEs");
	}
	else{
	
	bool logro=false;
	bool logro2=false;
	int cantidadPuntajes[4]={0,0,0,0};
	
	for(int i=0; i<tam; i++){
		if(datos[i].result==1 and datos[i].id==6){
			if(datos[i].score>0 and datos[i].score < 26) {
				cantidadPuntajes[0]++;
			} else if(datos[i].score<51){
				cantidadPuntajes[1]++;
			} else if(datos[i].score<76){
				cantidadPuntajes[2]++;
			} else if(datos[i].score>75 and datos[i].score<101){
				cantidadPuntajes[3]++;
			}
		}
	}
	

	
	gotoxy(0,1);
	colorear(celeste, "  - ESTAD"+s('Í')+"STICAS PARES - \n");
	
	barra_victorias(6);
	
	cout << "\n\n";
	tiempo_max_min(6);
	cout << "\n";
	centrar("Cantidad de partidas en ParEs en los siguientes rangos:");
	gotoxy(5,13);
	cout << "De [0-25] puntos: "<< cantidadPuntajes[0];
	gotoxy(5,14);
	cout << "De [26-50] puntos: "<< cantidadPuntajes[1];
	gotoxy(32,13);
	cout << "De [51-75] puntos: "<< cantidadPuntajes[2];
	gotoxy(32,14);
	cout << "De [76-100] puntos: "<< cantidadPuntajes[3] << "\n\n\n";
	
	colorear(celeste, "- LOGROS PARES -");
	centrar("En verde, los que desbloqueaste\n");
	
	for(int i=0; i<tam; i++){
		if (datos[i].id == 6){
			if(datos[i].score == 100)
				logro = true;
			if(datos[i].score > 0)
				logro2 = true;
		}
	}
	//determinar logro
	
	if(logro){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar("Cupido: Encuentra todas las parejas sin fallar\n");
	
	if(logro2){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar("Pura suerte: Gana una partida");
	
	}
	gotoxy(0,28);
	pausa(1);
}

void estadisticas_batalla_naval(){
	
	limpiar_pantalla();
	if(partidas_jugadas[6]==0){
		gotoxy(0,15);
		colorear(rojo, "Todav"+s('í')+"a no jugaste ninguna partida");
		colorear(rojo, "de Batalla Naval");
	}
	else{

	bool logro=false;
	
	
	gotoxy(0,1);
	colorear(celeste, "  - ESTAD"+s('Í')+"STICAS BATALLA NAVAL - \n");
	
	barra_victorias(7);
	
	cout << "\n\n";
	tiempo_max_min(7);
	cout << "\n\n\n\n";
	colorear(celeste, "- LOGROS BATALLA NAVAL -");
	centrar("En verde, los que desbloqueaste\n");
	
	for(int i=0; i<tam; i++){
		if (datos[i].id == 7){
			if(datos[i].score == 100)
				logro = true;
		}
	}

	if(logro){
		color(verde);
	}else{
		color(gris);
	}
	
	centrar("Estratega Celestial: Gana con la m"+ s('á')+"xima puntuaci"+s('ó')+"n posible");
	}
	gotoxy(0,28);
	pausa(1);
}
//funciones visuales a continuación
void grafico_barras (int cantidad,int x, int y, int porcentajes[]){
	
	gotoxy(x+1,y);
	for(int i=0;i<cantidad;i++){
		cout << setfill(' ') << setw(3) << porcentajes[i];
		cout <<"% ";
		
	}
	color(blanco);
	
	for(int i=0; i<cantidad; i++)
		porcentajes[i]=redondear(porcentajes[i]);
	
	for(int i=0; i<11; i++){									//lineas laterales
		gotoxy(x,(y-(i+1)));
		cout << char(179);
		gotoxy((x+cantidad*5),(y-(i+1)));
		cout << char(179);
	}
	
	char simbolo;
	
	for(int i=0; i<2; i++){
		
		if(i==0){
			gotoxy(x,y-1);
			simbolo = char(238);
			
		}
		else{
			gotoxy(x,y-12);
			simbolo = char(95);
		}
		cout << simbolo;
		for(int i=0;i<cantidad;i++){
			cout << simbolo << simbolo << simbolo << simbolo;
		}
		for(int i=0;i<cantidad;i++){
			cout << simbolo;
		}
		
	}
	
	color(gris);
	for(int i=1; i<11; i++){
		gotoxy(x+1,((y-1)-i));
		simbolo = char(250);
		for(int j=0; j<(cantidad*2.4); j++){
			
			cout << "__";
			
		}
		
	}
	
	x+=2;
	y-=2;
	int x2 = x;
	int y2 = y;
	
	color(azul);
	for(int i=0; i<11; i++){
		dormir(150);
		for( int j=0; j<cantidad; j++){
			gotoxy(x2,y2);
			if(porcentajes[j]>0){
				if(porcentajes[j]!=5){
					cout << char(219)<<char(219);
					porcentajes[j]-=10;
				}
				else{
					cout << char(220)<<char(220);
					
					porcentajes[j]-=10;
				}
				
			}
			
			x2+=5;
			cout.flush();
		}
		x2= x;
		y2=y-(i+1);
		
	}
}

void barra(int porcentaje, int modo){
	int aux = porcentaje;
	
	if(modo==2){
		for(int i=0; i<(ANCHOGLOBAL-35)/2; i++){
			cout << " ";
		}
		color("verde");
		cout << "Vos";
	}
	else{
		color("blanco");
		for(int i=0; i<(ANCHOGLOBAL-30)/2; i++){
			cout << " ";
		}
	}
	
	cout << setfill(' ') << setw(3) <<porcentaje;
	cout << "% ";
	
	porcentaje = redondear(porcentaje);

	
	for (int i=0; i<porcentaje; i+=5){
		cout << char(219);
	}
	
	if(modo==2)
		color("rojo");
	
	for (int i=0; i<100-porcentaje; i+=5){
		if(modo==2)
			cout << char(219);
		else
			cout <<char(176);

	}
	if(modo ==2){
		cout  << setfill(' ') << setw(3) <<(100-aux);
		cout << "% PC";
	}
	color("blanco");
}

int redondear(int numero){
	int y = numero %10;
	numero-=y;
	
	if(y==0){
		return numero;
	}
	else if(y<8 and y>2){
		numero+=5;
	}
		else{
		numero+=10;
	}
	
	return numero;
}
void barra_victorias(int id){
	
	int porcentaje=0;
	
	if(partidas_jugadas[id-1]!=0){
		porcentaje = (victorias[id-1]*100)/partidas_jugadas[id-1];
	}
	
	centrar("  Porcentaje de partidas ganadas sobre el total\n");
	/*	cout << porcentaje;*/
	if(porcentaje==0){
		centrar("- - -",0);
	}
	else{
		barra(porcentaje);
	}
	
}

void barra_versus(int id){
	
	int victorias_pc = 0;
	int total =0;
	int porcentaje=0;
	
	centrar("Porcentaje de partidas ganadas\n");
	
	for (int pos=0; pos<tam; pos++){
		if(datos[pos].id==id){
			if(datos[pos].result==2)
				victorias_pc++;
		}
	}
	
	total = (victorias_pc + victorias[id-1]);
	
	if(total!=0){
		porcentaje = (victorias[id-1]*100)/total;
		barra(porcentaje,2);
	}
	else{
		centrar ("- - -",0);
	}
}

void tiempo_max_min(int id){
	
	int minutos = tiempos[0][id-1]/60;
	int segundos = tiempos[0][id-1]%60;
	
	if(segundos!=-1){
		centrar(" La partida m"+s('á')+"s r"+s('á')+"pida dur"+s('ó')+" "+to_string(minutos)+" minutos con "+to_string(segundos)+" segundos");
	} else {
		centrar(" La informaci"+s('ó')+"n de la partida m"+s('á')+"s r"+s('á')+"pida");
		centrar("no se encuentra disponible");
	}
	
	minutos = tiempos[1][id-1]/60;
	segundos = tiempos[1][id-1]%60;
	
	if(segundos!=-1){
		centrar("Y la m"+s('á')+"s lenta: "+to_string(minutos)+" minutos con "+to_string(segundos)+" segundos");
	} else {
		centrar(" La informaci"+s('ó')+"n de la partida m"+s('á')+"s lenta");
		centrar("no se encuentra disponible");
	}
	
}

void merge1 (int vector1[], int inicio1, int fin1, int inicio2, int fin2){
	int pos1=inicio1, pos2=inicio2, pos3=0;
	int * vector2;
	vector2= new int [fin2+1]; 
	
	while (pos1<=fin1 and pos2<=fin2)
	{
		if(vector1[pos1]<vector1[pos2])
		{
			vector2[pos3]=vector1[pos1];
			pos1++;
		} 
		else 
		{
			vector2[pos3]=vector1[pos2];
			pos2++;
		}
		pos3++;
	}
	while(pos1<=fin1)
	{
		vector2[pos3]=vector1[pos1];
		pos1++; pos3++;
	}
	while(pos2<=fin2)
	{
		vector2[pos3]=vector1[pos2];
		pos2++; pos3++;
	}
	for(pos3=0; pos3<=fin2-inicio1; pos3++)
	{
		vector1[inicio1+pos3]=vector2[pos3];
	}
	
	delete vector2;
}

void mergeSort (int vector[], int inicio, int fin){
	if(fin-inicio == 0)
	{
		return;
	} 
	else 
	{
		mergeSort (vector, inicio, (inicio+fin)/2);
		mergeSort(vector, (inicio+fin)/2 +1, fin);
		merge1(vector, inicio, (inicio+fin)/2, (inicio+fin)/2+1, fin);
	}
}
