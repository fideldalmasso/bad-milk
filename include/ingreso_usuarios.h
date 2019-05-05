#include <string>
#include <fstream>
using namespace std;

struct usuario{
	string nombre;
	string contra;
};


bool menu_ingreso();
void cambiar_contrasenia();
bool eliminar_cuenta();
bool cerrar_sesion();

extern usuario actual;
