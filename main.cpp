#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm> // Para ordenar la lista al final
#include "interfaz.hpp"
#include "hipodromo.hpp"
#include "caballo.hpp"

using namespace std;

// Función auxiliar para ordenar los caballos por su orden de llegada
bool ordenarPorLugar(const Caballo &a, const Caballo &b) {
    return a.lugar_llegada < b.lugar_llegada;
}

int main() {
    srand(time(0));
    inicializarNcurses();

    bool ejecutando = true;
    while(ejecutando) {
        if(menuPrincipal() == 1) break; 

        int numCaballos = solicitarNumeroCaballos();
        int ancho = 80;
        int alto = 10 + 2 * numCaballos;
        int metaX = ancho / 2;
        
        vector<pair<int, int>> camino = generarCamino(ancho, alto, metaX, numCaballos);

        // Inicializamos los caballos dinámicamente
        vector<Caballo> caballos;
        for (int i = 1; i <= numCaballos; i++) {
            caballos.push_back({"Caballo " + to_string(i), 0, i, 0, 0});
        }

        int contadorLugares = 1; // Controla el podio (1 = Primer lugar, 2 = Segundo...)
        int totalCaballos = caballos.size();

        // El juego sigue corriendo MIENTRAS queden caballos por cruzar la meta
        while (contadorLugares <= totalCaballos) {
            clear();
            dibujarPista(ancho, alto, numCaballos);
            
            for (auto &c : caballos) {
                // Solo avanzan los caballos que NO han terminado la carrera
                if (c.lugar_llegada == 0) {
                    int avance = (rand() % 2 + 1);
                    int nuevaPos = c.pos + avance;
                    if (nuevaPos >= (int)camino.size()) {
                        c.vueltas++;
                        c.pos = nuevaPos % camino.size(); 
                    } else {
                        c.pos = nuevaPos;
                    }
                }
            }
            
            dibujarCaballos(camino, caballos);
            
            // Revisa y registra si alguien cruzó en este turno
            registrarLlegadas(caballos, contadorLugares, 1); 
            
            refresh(); 
            napms(80); 
        }

        // --- PANTALLA DE RESULTADOS ---
        // Ordenamos el vector para que los que tienen lugar_llegada 1, 2, 3 salgan hacia abajo
        sort(caballos.begin(), caballos.end(), ordenarPorLugar);

        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        
        // Imprimir la tabla de posiciones debajo de la pista
        mvprintw(alto + 3, (xMax / 2) - 12, "=== TABLA DE POSICIONES ===");
        for (int i = 0; i < totalCaballos; i++) {
            mvprintw(alto + 5 + i, (xMax / 2) - 10, "%dº Lugar: %s", 
                     caballos[i].lugar_llegada, caballos[i].nombre.c_str());
        }
        
        // Lanzamos el menú final un poco más abajo para no tapar la tabla
        if(menuFinal(alto + 6 + totalCaballos) == 1) {
            ejecutando = false;
        }
    }

    endwin();
    return 0;
}