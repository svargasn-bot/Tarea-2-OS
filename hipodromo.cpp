#include "hipodromo.hpp"
#include "caballo.hpp"

using namespace std;

vector<pair<int, int>> generarCamino(int ancho, int alto, int metaX, int numCaballos) {
    vector<pair<int, int>> camino;
    int yBottom = alto - numCaballos + 1;
    
    for (int x = metaX; x < ancho - 10; x++) camino.push_back({x, 2});
    for (int y = 3; y < yBottom; y++) camino.push_back({ancho - 10, y});
    for (int x = ancho - 10; x >= 10; x--) camino.push_back({x, yBottom});
    for (int y = yBottom - 1; y >= 3; y--) camino.push_back({10, y});
    for (int x = 10; x < metaX; x++) camino.push_back({x, 2});
    
    return camino;
}

void dibujarPista(int ancho, int alto, int numCaballos) {
    for (int i = 5; i < ancho - 4; i++) {
        mvprintw(1, i, "="); 
        mvprintw(alto + 1, i, "=");
    }
    for (int j = 2; j < alto + 2; j++) {
        mvprintw(j, 5, "||");
        mvprintw(j, ancho - 3, "||");
    }
    
    mvprintw(2, ancho / 2, "M");
    mvprintw(3, ancho / 2, "E");
    mvprintw(4, ancho / 2, "T");
    mvprintw(5, ancho / 2, "A");

    int margenH = 15;
    int margenV = numCaballos + 2;
    for (int i = margenH; i < ancho - margenH; i++) {
        mvprintw(margenV, i, "=");
        mvprintw(alto - margenV + 2, i, "=");
    }
    for (int j = margenV + 1; j < alto - margenV + 2; j++) {
        mvprintw(j, margenH, "||");
        mvprintw(j, ancho - margenH + 1, "||");
    }
}

void dibujarCaballos(const vector<pair<int, int>> &camino, const vector<Caballo> &caballos) {
    for (size_t i = 0; i < caballos.size(); i++) {
        int idx = caballos[i].pos;
        int next = (idx + 1) % camino.size();
        int dx = camino[next].first - camino[idx].first;
        int dy = camino[next].second - camino[idx].second;
        
        mvprintw(camino[idx].second + (int)i, camino[idx].first,
                 "%s", simboloCaballo(dx, dy, caballos[i].numero).c_str());
    }
}