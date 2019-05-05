GPP=g++
CXXFLAGS=  -fshow-column -fno-diagnostics-show-caret  -Wall -O0 -Iinclude  -m32 -D_DEBUG -std=c++14
LDFLAGS=  -Llib -lahorcado -lbatallanaval  -m32
OBJS=temp/Debug/main.o temp/Debug/pipati.o temp/Debug/generala_avanzada.o temp/Debug/funciones_utiles.o temp/Debug/generala.o temp/Debug/pares.o temp/Debug/frical.o temp/Debug/ahorcado.o temp/Debug/batalla_naval.o temp/Debug/ingreso_usuarios.o temp/Debug/encriptacion.o temp/Debug/ranking.o temp/Debug/estadisticas.o 

all: temp/Debug Bad_Milk
	@echo [100%] Built target Bad_Milk

clean:
	rm -rf ${OBJS} Bad_Milk

Bad_Milk: ${OBJS}
	@echo "[ 92%]" Linking executable Bad_Milk
	@${GPP} ${OBJS} ${LDFLAGS} -o $@

temp/Debug:
	mkdir temp/Debug

temp/Debug/main.o: src/main.cpp include/funciones_utiles.h include/ingreso_usuarios.h include/encriptacion.h include/ranking.h include/estadisticas.h include/frical.h include/generala.h include/generala_avanzada.h include/pares.h include/pipati.h include/ahorcado.h include/batalla_naval.h
	@echo "[  0%]" Building C++ object temp/Debug/main.o
	@${GPP} ${CXXFLAGS} -c src/main.cpp -o $@

temp/Debug/pipati.o: src/games/pipati.cpp include/pipati.h include/funciones_utiles.h include/ranking.h include/ingreso_usuarios.h
	@echo "[  7%]" Building C++ object temp/Debug/pipati.o
	@${GPP} ${CXXFLAGS} -c src/games/pipati.cpp -o $@

temp/Debug/generala_avanzada.o: src/games/generala_avanzada.cpp include/generala_avanzada.h include/funciones_utiles.h include/ranking.h
	@echo "[ 14%]" Building C++ object temp/Debug/generala_avanzada.o
	@${GPP} ${CXXFLAGS} -c src/games/generala_avanzada.cpp -o $@

temp/Debug/funciones_utiles.o: src/funciones_utiles.cpp include/funciones_utiles.h
	@echo "[ 21%]" Building C++ object temp/Debug/funciones_utiles.o
	@${GPP} ${CXXFLAGS} -c src/funciones_utiles.cpp -o $@

temp/Debug/generala.o: src/games/generala.cpp include/generala.h include/funciones_utiles.h include/ranking.h
	@echo "[ 28%]" Building C++ object temp/Debug/generala.o
	@${GPP} ${CXXFLAGS} -c src/games/generala.cpp -o $@

temp/Debug/pares.o: src/games/pares.cpp include/pares.h include/funciones_utiles.h include/ranking.h
	@echo "[ 35%]" Building C++ object temp/Debug/pares.o
	@${GPP} ${CXXFLAGS} -c src/games/pares.cpp -o $@

temp/Debug/frical.o: src/games/frical.cpp include/frical.h include/funciones_utiles.h include/ranking.h
	@echo "[ 42%]" Building C++ object temp/Debug/frical.o
	@${GPP} ${CXXFLAGS} -c src/games/frical.cpp -o $@

temp/Debug/ahorcado.o: src/games/ahorcado.cpp include/ahorcado.h include/funciones_utiles.h include/ranking.h
	@echo "[ 50%]" Building C++ object temp/Debug/ahorcado.o
	@${GPP} ${CXXFLAGS} -c src/games/ahorcado.cpp -o $@

temp/Debug/batalla_naval.o: src/games/batalla_naval.cpp include/batalla_naval.h include/funciones_utiles.h include/ranking.h
	@echo "[ 57%]" Building C++ object temp/Debug/batalla_naval.o
	@${GPP} ${CXXFLAGS} -c src/games/batalla_naval.cpp -o $@

temp/Debug/ingreso_usuarios.o: src/ingreso_usuarios.cpp include/ingreso_usuarios.h include/funciones_utiles.h include/encriptacion.h include/ranking.h
	@echo "[ 64%]" Building C++ object temp/Debug/ingreso_usuarios.o
	@${GPP} ${CXXFLAGS} -c src/ingreso_usuarios.cpp -o $@

temp/Debug/encriptacion.o: src/encriptacion.cpp include/funciones_utiles.h include/encriptacion.h include/ingreso_usuarios.h
	@echo "[ 71%]" Building C++ object temp/Debug/encriptacion.o
	@${GPP} ${CXXFLAGS} -c src/encriptacion.cpp -o $@

temp/Debug/ranking.o: src/ranking.cpp include/ranking.h include/ingreso_usuarios.h include/funciones_utiles.h include/encriptacion.h
	@echo "[ 78%]" Building C++ object temp/Debug/ranking.o
	@${GPP} ${CXXFLAGS} -c src/ranking.cpp -o $@

temp/Debug/estadisticas.o: src/estadisticas.cpp include/estadisticas.h include/funciones_utiles.h include/ranking.h include/ingreso_usuarios.h include/encriptacion.h
	@echo "[ 85%]" Building C++ object temp/Debug/estadisticas.o
	@${GPP} ${CXXFLAGS} -c src/estadisticas.cpp -o $@

