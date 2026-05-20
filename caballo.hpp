#ifndef CABALLO_HPP
#define CABALLO_HPP

#include <string>  
#include <vector>  

struct Caballo {
    std::string nombre; 
    int pos;     
    int numero;  
    int vueltas; 
    int lugar_llegada; // <-- NUEVO: Guarda el orden en que llegó (1º, 2º, etc.)
};

std::string simboloCaballo(int dx, int dy, int numero);

// Modificamos la función: ahora procesa quiénes cruzan en cada ciclo
void registrarLlegadas(std::vector<Caballo> &caballos, int &contadorLugares, int vueltasMeta);

#endif