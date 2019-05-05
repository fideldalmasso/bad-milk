GPP=g++
CXXFLAGS=  -fshow-column -fno-diagnostics-show-caret  -Wall -O0 -Iinclude  -m32 -D_DEBUG -std=c++14
LDFLAGS=  -Llib -lahorcado -lbatallanaval  -m32
OBJS=data/main.o data/pipati.o data/generala_avanzada.o data/funciones_utiles.o data/generala.o data/pares.o data/frical.o data/ahorcado.o data/batalla_naval.o data/ingreso_usuarios.o data/encriptacion.o data/ranking.o data/estadisticas.o 

all: data/ Bad_Milk
	@echo [100%] Built target Bad_Milk

clean:
	rm -rf ${OBJS} Bad_Milk

Bad_Milk: ${OBJS}
	@echo "[ 92%]" Linking executable Bad_Milk
	@${GPP} ${OBJS} ${LDFLAGS} -o $@

data/:
	mkdir data/

data/main.o: src/main.cpp include/funciones_utiles.h include/ingreso_usuarios.h include/encriptacion.h include/ranking.h include/estadisticas.h include/frical.h include/generala.h include/generala_avanzada.h include/pares.h include/pipati.h include/ahorcado.h include/batalla_naval.h
	@echo "[  0%]" Building C++ object data/main.o
	@${GPP} ${CXXFLAGS} -c src/main.cpp -o $@

data/pipati.o: src/games/pipati.cpp include/pipati.h include/funciones_utiles.h include/ranking.h include/ingreso_usuarios.h
	@echo "[  7%]" Building C++ object data/pipati.o
	@${GPP} ${CXXFLAGS} -c src/games/pipati.cpp -o $@

data/generala_avanzada.o: src/games/generala_avanzada.cpp include/generala_avanzada.h include/funciones_utiles.h include/ranking.h
	@echo "[ 14%]" Building C++ object data/generala_avanzada.o
	@${GPP} ${CXXFLAGS} -c src/games/generala_avanzada.cpp -o $@

data/funciones_utiles.o: src/funciones_utiles.cpp include/funciones_utiles.h
	@echo "[ 21%]" Building C++ object data/funciones_utiles.o
	@${GPP} ${CXXFLAGS} -c src/funciones_utiles.cpp -o $@

data/generala.o: src/games/generala.cpp include/generala.h include/funciones_utiles.h include/ranking.h
	@echo "[ 28%]" Building C++ object data/generala.o
	@${GPP} ${CXXFLAGS} -c src/games/generala.cpp -o $@

data/pares.o: src/games/pares.cpp include/pares.h include/funciones_utiles.h include/ranking.h
	@echo "[ 35%]" Building C++ object data/pares.o
	@${GPP} ${CXXFLAGS} -c src/games/pares.cpp -o $@

data/frical.o: src/games/frical.cpp include/frical.h include/funciones_utiles.h include/ranking.h
	@echo "[ 42%]" Building C++ object data/frical.o
	@${GPP} ${CXXFLAGS} -c src/games/frical.cpp -o $@

data/ahorcado.o: src/games/ahorcado.cpp include/ahorcado.h include/funciones_utiles.h include/ranking.h
	@echo "[ 50%]" Building C++ object data/ahorcado.o
	@${GPP} ${CXXFLAGS} -c src/games/ahorcado.cpp -o $@

data/batalla_naval.o: src/games/batalla_naval.cpp include/batalla_naval.h include/funciones_utiles.h include/ranking.h
	@echo "[ 57%]" Building C++ object data/batalla_naval.o
	@${GPP} ${CXXFLAGS} -c src/games/batalla_naval.cpp -o $@

data/ingreso_usuarios.o: src/ingreso_usuarios.cpp include/ingreso_usuarios.h include/funciones_utiles.h include/encriptacion.h include/ranking.h
	@echo "[ 64%]" Building C++ object data/ingreso_usuarios.o
	@${GPP} ${CXXFLAGS} -c src/ingreso_usuarios.cpp -o $@

data/encriptacion.o: src/encriptacion.cpp include/funciones_utiles.h include/encriptacion.h include/ingreso_usuarios.h
	@echo "[ 71%]" Building C++ object data/encriptacion.o
	@${GPP} ${CXXFLAGS} -c src/encriptacion.cpp -o $@

data/ranking.o: src/ranking.cpp include/ranking.h include/ingreso_usuarios.h include/funciones_utiles.h include/encriptacion.h
	@echo "[ 78%]" Building C++ object data/ranking.o
	@${GPP} ${CXXFLAGS} -c src/ranking.cpp -o $@

data/estadisticas.o: src/estadisticas.cpp include/estadisticas.h include/funciones_utiles.h include/ranking.h include/ingreso_usuarios.h include/encriptacion.h
	@echo "[ 85%]" Building C++ object data/estadisticas.o
	@${GPP} ${CXXFLAGS} -c src/estadisticas.cpp -o $@

