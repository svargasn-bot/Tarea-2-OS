#ifndef HIPODROMO_HPP
#define HIPODROMO_HPP

#include <vector>
#include <ncurses.h>
#include "caballo.hpp"

using namespace std; 

vector<pair<int, int>> generarCamino(int ancho, int alto, int metaX, int numCaballos);
void dibujarPista(int ancho, int alto, int numCaballos);
void dibujarCaballos(const vector<pair<int, int>> &camino, const vector<Caballo> &caballos);

#endif