#include "hipodromo.hpp"
#include "caballo.hpp"

using namespace std;

// ====================================================================
// generarCamino: Calcula por dónde pisan los caballos
// ====================================================================
vector<pair<int, int>> generarCamino(int ancho, int alto, int metaX) {
    vector<pair<int, int>> camino;
    
    int numCaballos = (alto - 8) / 2;
    
    // Calculamos la altura del carril inferior.
    // Dejamos espacio para que el primer caballo (i=0) no choque 
    // con el muro interior central.
    int offsetInferior = alto - numCaballos - 1; 

    // 1. TRAMO SUPERIOR: La ruta base inicia en Y = 2
    for (int x = metaX; x < ancho - 10; x++) camino.push_back({x, 2});
    
    // 2. TRAMO DERECHO
    for (int y = 3; y < offsetInferior; y++) camino.push_back({ancho - 10, y});
    
    // 3. TRAMO INFERIOR
    for (int x = ancho - 10; x >= 10; x--) camino.push_back({x, offsetInferior});
    
    // 4. TRAMO IZQUIERDO: Sube de regreso a la meta
    for (int y = offsetInferior - 1; y >= 3; y--) camino.push_back({10, y});
    
    // 5. Cierra el ciclo
    for (int x = 10; x < metaX; x++) camino.push_back({x, 2});
    
    return camino;
}

// ====================================================================
// dibujarPista: Dibuja los muros fijos
// ====================================================================
void dibujarPista(int ancho, int alto) {
    // --- LIMITES EXTERIORES ---
    for (int i = 5; i < ancho - 4; i++) {
        mvprintw(1, i, "=");          // Pared exterior superior
        mvprintw(alto - 1, i, "=");   // Pared exterior inferior
    }
    for (int j = 2; j < alto - 1; j++) {
        mvprintw(j, 5, "||");         // Pared exterior izquierda
        mvprintw(j, ancho - 3, "||"); // Pared exterior derecha
    }
    
    // --- LIMITES INTERIORES (Cálculo previo para usar margenV) ---
    int numCaballos = (alto - 8) / 2;
    int margenH = 18; 
    int margenV = numCaballos + 2; 

    // --- LETRERO DE META ---
    // Si hay pocos caballos, el letrero "META" no cabe entre los muros.
    // Usamos una línea simple '|' si alto < 16 (2-3 caballos)
    int metaX = ancho / 2;
    if (alto < 16) {
        for (int j = 2; j < margenV; j++) {
            mvprintw(j, metaX, "|");
        }
    } else {
        mvprintw(2, metaX, "M");
        mvprintw(3, metaX, "E");
        mvprintw(4, metaX, "T");
        mvprintw(5, metaX, "A");
        // Rellenamos el resto del carril superior con |
        for (int j = 6; j < margenV; j++) {
            mvprintw(j, metaX, "|");
        }
    }

    for (int i = margenH; i < ancho - margenH; i++) {
        mvprintw(margenV, i, "=");            
        mvprintw(alto - margenV, i, "="); 
    }
    for (int j = margenV + 1; j < alto - margenV; j++) {
        mvprintw(j, margenH, "||");             
        mvprintw(j, ancho - margenH + 1, "||"); 
    }
}

// ====================================================================
// dibujarCaballos
// ====================================================================
void dibujarCaballos(const vector<pair<int, int>> &camino, const vector<Caballo> &caballos) {
    for (size_t i = 0; i < caballos.size(); i++) {
        int idx = caballos[i].pos;
        int next = (idx + 1) % camino.size();
        int dx = camino[next].first - camino[idx].first;
        int dy = camino[next].second - camino[idx].second;
        
        // Sumar 'i' es lo que hace que cada caballo tenga su propio carril
        mvprintw(camino[idx].second + (int)i, camino[idx].first,
                 "%s", simboloCaballo(dx, dy, caballos[i].numero).c_str());
    }
}