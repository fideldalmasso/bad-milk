
#include <string>
using namespace std;


struct RegistroDeRank{
	string nickname;
	int score;
};

void guardar_partida(int id, int score, int pc_score, int result, int time);
RegistroDeRank * cargar_rank(int id);
void mostrar_rank(int id);
void menu_ranking();
