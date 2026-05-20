#ifndef INTERFAZ_HPP
#define INTERFAZ_HPP

#include <ncurses.h>
#include <string>

using namespace std;

void inicializarNcurses();
int menuPrincipal();
int menuFinal(int yBase);

#endif