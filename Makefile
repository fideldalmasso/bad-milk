GPP=g++
CXXFLAGS=  -fshow-column -fno-diagnostics-show-caret  -Wall -O0 -Iinclude  -m32 -D_DEBUG -std=c++14
LDFLAGS=  -Llib -lahorcado -lbatallanaval  -m32
OBJS=temp/main.o temp/pipati.o temp/generala_avanzada.o temp/funciones_utiles.o temp/generala.o temp/pares.o temp/frical.o temp/ahorcado.o temp/batalla_naval.o temp/ingreso_usuarios.o temp/encriptacion.o temp/ranking.o temp/estadisticas.o 

all: temp/ bad-milk
	@echo [100%] Built target bad-milk

clean:
	rm -rf ${OBJS} bad-milk

bad-milk: ${OBJS}
	@echo "[ 92%]" Linking executable bad-milk
	@${GPP} ${OBJS} ${LDFLAGS} -o $@

temp/:
	mkdir temp/

temp/main.o: src/main.cpp include/funciones_utiles.h include/ingreso_usuarios.h include/encriptacion.h include/ranking.h include/estadisticas.h include/frical.h include/generala.h include/generala_avanzada.h include/pares.h include/pipati.h include/ahorcado.h include/batalla_naval.h
	@echo "[  0%]" Building C++ object temp/main.o
	@${GPP} ${CXXFLAGS} -c src/main.cpp -o $@

temp/pipati.o: src/games/pipati.cpp include/pipati.h include/funciones_utiles.h include/ranking.h include/ingreso_usuarios.h
	@echo "[  7%]" Building C++ object temp/pipati.o
	@${GPP} ${CXXFLAGS} -c src/games/pipati.cpp -o $@

temp/generala_avanzada.o: src/games/generala_avanzada.cpp include/generala_avanzada.h include/funciones_utiles.h include/ranking.h
	@echo "[ 14%]" Building C++ object temp/generala_avanzada.o
	@${GPP} ${CXXFLAGS} -c src/games/generala_avanzada.cpp -o $@

temp/funciones_utiles.o: src/funciones_utiles.cpp include/funciones_utiles.h
	@echo "[ 21%]" Building C++ object temp/funciones_utiles.o
	@${GPP} ${CXXFLAGS} -c src/funciones_utiles.cpp -o $@

temp/generala.o: src/games/generala.cpp include/generala.h include/funciones_utiles.h include/ranking.h
	@echo "[ 28%]" Building C++ object temp/generala.o
	@${GPP} ${CXXFLAGS} -c src/games/generala.cpp -o $@

temp/pares.o: src/games/pares.cpp include/pares.h include/funciones_utiles.h include/ranking.h
	@echo "[ 35%]" Building C++ object temp/pares.o
	@${GPP} ${CXXFLAGS} -c src/games/pares.cpp -o $@

temp/frical.o: src/games/frical.cpp include/frical.h include/funciones_utiles.h include/ranking.h
	@echo "[ 42%]" Building C++ object temp/frical.o
	@${GPP} ${CXXFLAGS} -c src/games/frical.cpp -o $@

temp/ahorcado.o: src/games/ahorcado.cpp include/ahorcado.h include/funciones_utiles.h include/ranking.h
	@echo "[ 50%]" Building C++ object temp/ahorcado.o
	@${GPP} ${CXXFLAGS} -c src/games/ahorcado.cpp -o $@

temp/batalla_naval.o: src/games/batalla_naval.cpp include/batalla_naval.h include/funciones_utiles.h include/ranking.h
	@echo "[ 57%]" Building C++ object temp/batalla_naval.o
	@${GPP} ${CXXFLAGS} -c src/games/batalla_naval.cpp -o $@

temp/ingreso_usuarios.o: src/ingreso_usuarios.cpp include/ingreso_usuarios.h include/funciones_utiles.h include/encriptacion.h include/ranking.h
	@echo "[ 64%]" Building C++ object temp/ingreso_usuarios.o
	@${GPP} ${CXXFLAGS} -c src/ingreso_usuarios.cpp -o $@

temp/encriptacion.o: src/encriptacion.cpp include/funciones_utiles.h include/encriptacion.h include/ingreso_usuarios.h
	@echo "[ 71%]" Building C++ object temp/encriptacion.o
	@${GPP} ${CXXFLAGS} -c src/encriptacion.cpp -o $@

temp/ranking.o: src/ranking.cpp include/ranking.h include/ingreso_usuarios.h include/funciones_utiles.h include/encriptacion.h
	@echo "[ 78%]" Building C++ object temp/ranking.o
	@${GPP} ${CXXFLAGS} -c src/ranking.cpp -o $@

temp/estadisticas.o: src/estadisticas.cpp include/estadisticas.h include/funciones_utiles.h include/ranking.h include/ingreso_usuarios.h include/encriptacion.h
	@echo "[ 85%]" Building C++ object temp/estadisticas.o
	@${GPP} ${CXXFLAGS} -c src/estadisticas.cpp -o $@

