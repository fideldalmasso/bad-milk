#include <string>
#include <ctime>
using namespace std;

void centrar(string cadena, int salto=1);
void color(string color);
void colorear(string color1,string texto,int centrado=1, int salto=1);
void resize(int anchura, int altura);
void gotoxy(int x, int y);
void pausa(bool centrado=0);
void limpiar_pantalla();
void dormir(int milisegundos);
char getchx();
string s(char letra);
void leerarchivo(string nombre, const string & color = "ninguno", int velocidad=1);
void bienvenida();
int contar_lineas(string nombre);


extern const string blanco, rojo, amarillo, verde, violeta, verde2, azul, celeste, gris;
extern int ANCHOGLOBAL;
