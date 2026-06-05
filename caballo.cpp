#include "caballo.hpp"

using namespace std;

string simboloCaballo(int dx, int dy, int numero) {
    if (dx > 0) return "-" + to_string(numero) + ">"; 
    if (dx < 0) return "<" + to_string(numero) + "-"; 
    if (dy > 0) return "\\" + to_string(numero) + "/"; 
    if (dy < 0) return "/" + to_string(numero) + "\\"; 
    
    return (numero < 10) ? "0" + to_string(numero) : to_string(numero);
}
// Funcion para modificar la probabilidad, cambiando el parametro de la derecha del rand
int calcularProbabilidadAvance() {
    if ((rand() % 100) < 50) {
        return 1;
    }
    return 0;
}