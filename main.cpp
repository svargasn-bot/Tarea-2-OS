#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <pthread.h> // Biblioteca estricta de C para hebras
#include <unistd.h>  // Para usar usleep()
#include "interfaz.hpp"
#include "hipodromo.hpp"
#include "caballo.hpp"

using namespace std;

// Mutex global para sincronizar a los caballos
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

// Variables compartidas
int contadorLugares = 1;
int caminoSize = 0;
int vueltasMeta = 0;
int posicionDatos = 20;

// Estructura para pasarle los datos a cada hebra
struct DatosHebra {
    Caballo* c;
    int largoPistaMetros; // Aquí guardaremos si la pista es de 30, 40, 50 o 60 metros
};

// Ordenar podio al final
bool ordenarPorLugar(const Caballo &a, const Caballo &b) {
    if (a.lugar_llegada == 0) return false;
    if (b.lugar_llegada == 0) return true;
    return a.lugar_llegada < b.lugar_llegada;
}

// =========================================================
// FUNCIÓN DE LA HEBRA (Se ejecuta 1 vez por cada caballo)
// =========================================================
void* funcionCaballo(void* arg) {
    DatosHebra* datos = (DatosHebra*)arg;
    Caballo* c = datos->c;
    
    // Extraemos la medida oficial elegida (ej: 40 metros)
    int metrosTotalesPista = datos->largoPistaMetros; 

    while (true) {
        pthread_mutex_lock(&mtx);
        if (c->lugar_llegada > 0) {
            pthread_mutex_unlock(&mtx);
            break; 
        }
        pthread_mutex_unlock(&mtx);

        int avance = calcularProbabilidadAvance(); 

        if (avance > 0) {
            pthread_mutex_lock(&mtx); 
            
            // 1. Movemos al caballo visualmente
            int nuevaPos = c->pos + avance;
            if (nuevaPos >= caminoSize) {
                c->vueltas++;
                c->pos = nuevaPos % caminoSize; 
            } else {
                c->pos = nuevaPos;
            }

            // ====================================================================
            // 2. AQUI SE CALCULAN LOS METROS (La fórmula matemática)
            // ====================================================================
            // Calculamos qué porcentaje de la pista dibujada ha recorrido el caballo.
            // Ej: Si la pista visual tiene 200 pasos (caminoSize) y lleva 100 pasos, va al 50%.
            // Luego, le sacamos ese 50% a los metros reales (Ej: 50% de 40 metros = 20 metros).
            // A eso le sumamos las vueltas completas que ya haya dado.
            
            int metrosPorVueltas = c->vueltas * metrosTotalesPista;
            int metrosEnEstaVuelta = (c->pos * metrosTotalesPista) / caminoSize;
            
            c->distancia_recorrida = metrosPorVueltas + metrosEnEstaVuelta;
            // ====================================================================

            // 3. Validar si cruzó la meta
            if (c->vueltas >= vueltasMeta && c->lugar_llegada == 0) {
                c->lugar_llegada = contadorLugares;
                contadorLugares++;
                
                // Aseguramos que al cruzar la meta tenga los metros exactos
                c->distancia_recorrida = vueltasMeta * metrosTotalesPista; 
            }
            
            pthread_mutex_unlock(&mtx); 
        }
        usleep((10 + (rand() % 20)) * 1000);//usleep((30 + (rand() % 50)) * 1000);
    }
    return NULL;
}

// =========================================================
// FUNCIÓN PRINCIPAL
// =========================================================
int main() {
    srand(time(NULL));
    inicializarNcurses();

    // Variables por defecto para arrancar el menú
    int largoPistaMetros = 40;  
    int numCaballos = 4; 
    vueltasMeta = 1; 
    int numeroCarrera = 1; // Contador de carreras
        
    bool ejecutando = true;
    while(ejecutando) {
        contadorLugares = 1; 
        
        // Abrimos el menú y el usuario modifica largoPistaMetros, numCaballos y vueltasMeta
        if(menuPrincipal(vueltasMeta, largoPistaMetros, numCaballos) == 2) break; 

        // ==============================================================
        // NUEVO: ESCALADO VISUAL DINÁMICO OPTIMIZADO
        // Aumentamos ligeramente el alto (+8 en vez de +6) para que no se salgan
        // ==============================================================
        int anchoVisual = (largoPistaMetros * 2) + 20; 
        int alto = (numCaballos * 2) + 8; 
        int metaX = anchoVisual / 2;
        
        vector<pair<int, int>> camino = generarCamino(anchoVisual, alto, metaX);
        caminoSize = camino.size();

        vector<Caballo> caballos;
        for(int i = 1; i <= numCaballos; i++) {
            string nom = "Caballo " + string(1, '1' + (i - 1)); 
            caballos.push_back({nom, 0, i, 0, 0, 0});
        }

        vector<pthread_t> hebras(numCaballos);
        vector<DatosHebra> datosHebra(numCaballos);

        for (int i = 0; i < numCaballos; i++) {
            datosHebra[i].c = &caballos[i];
            datosHebra[i].largoPistaMetros = largoPistaMetros; 
            pthread_create(&hebras[i], NULL, funcionCaballo, (void*)&datosHebra[i]);
        }

        while (true) {
            pthread_mutex_lock(&mtx);
            bool terminada = (contadorLugares > numCaballos);
            
            clear();
            dibujarPista(anchoVisual, alto);
            dibujarCaballos(camino, caballos);
            
            int sumVueltas = 0;
            int sumMetros = 0;
            
            // --- MARCADOR FUERA DE LA PISTA (LADO A LADO) ---
            int yMarcador = alto + 1;
            int xCol1 = 10;

            mvprintw(yMarcador, xCol1, "=== DISTANCIA RECORRIDA ===");
            for (int i = 0; i < numCaballos; i++) {
                sumVueltas += caballos[i].vueltas;
                sumMetros += caballos[i].distancia_recorrida;
                
                mvprintw(yMarcador + 2 + i, xCol1, "Caballo %d: %d m | V: %d/%d", 
                         i + 1, caballos[i].distancia_recorrida, caballos[i].vueltas, vueltasMeta);
            }
            mvprintw(yMarcador + 3 + numCaballos, xCol1, "TOTALES: %d vueltas - %d metros", sumVueltas, sumMetros);
            // ------------------------------------------------
            
            refresh();
            pthread_mutex_unlock(&mtx);

            if (terminada) break;
            usleep(20000);
        }

        for (int i = 0; i < numCaballos; i++) {
            pthread_join(hebras[i], NULL);
        }

        sort(caballos.begin(), caballos.end(), ordenarPorLugar);

        // --- PODIO FINAL FUERA DE LA PISTA ---
        int yMarcador = alto + 1;
        int xCol2 = (anchoVisual / 2) + 5;
        mvprintw(yMarcador, xCol2, "=== TABLA DE POSICIONES ===");
        for (int i = 0; i < numCaballos; i++) {
            mvprintw(yMarcador + 2 + i, xCol2, "%d Lugar: %s", 
                     caballos[i].lugar_llegada, caballos[i].nombre.c_str());
        }

        // --- MENSAJES POST CARRERA ---
        int yFinal = yMarcador + 2 + numCaballos; 
        mvprintw(yFinal, 10, "Carrera Nro: %d", numeroCarrera);
        mvprintw(yFinal + 1, 10, "El caballo ganador fue: %s", caballos[0].nombre.c_str());
        
        numeroCarrera++; // Incrementamos para la siguiente vuelta

        if(menuFinal(yFinal + 3) == 1) { 
            ejecutando = false;
        }
    }

    pthread_mutex_destroy(&mtx);
    endwin();
    return 0;
}