#ifndef INTERFAZ_HPP
#define INTERFAZ_HPP

#include <ncurses.h>
#include <string>

using namespace std;

void inicializarNcurses();
// Ahora recibe referencias para configurar la carrera antes de iniciar
int menuPrincipal(int &vueltas, int &ancho, int &numCaballos); 
int menuFinal(int yBase);

#endif