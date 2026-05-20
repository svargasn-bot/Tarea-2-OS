#include "caballo.hpp"

using namespace std;

string simboloCaballo(int dx, int dy, int numero) {
    if (dx > 0) return "-" + to_string(numero) + ">"; 
    if (dx < 0) return "<" + to_string(numero) + "-"; 
    if (dy > 0) return "\\" + to_string(numero) + "/"; 
    if (dy < 0) return "/" + to_string(numero) + "\\"; 
    
    return (numero < 10) ? "0" + to_string(numero) : to_string(numero);
}

void registrarLlegadas(vector<Caballo> &caballos, int &contadorLugares, int vueltasMeta) {
    for (auto &c : caballos) {
        // Si el caballo completó las vueltas y aún no se le ha asignado puesto
        if (c.vueltas >= vueltasMeta && c.lugar_llegada == 0) {
            c.lugar_llegada = contadorLugares;
            contadorLugares++; // El siguiente que cruce tendrá el puesto posterior
        }
    }
}