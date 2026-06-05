#ifndef CABALLO_HPP
#define CABALLO_HPP

#include <string>  
#include <vector>  

struct Caballo {
    std::string nombre; 
    int pos;     
    int numero;  
    int vueltas; 
    int lugar_llegada; 
    int distancia_recorrida; 
};

std::string simboloCaballo(int dx, int dy, int numero);
int calcularProbabilidadAvance(); 

#endif