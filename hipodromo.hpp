#ifndef HIPODROMO_HPP
#define HIPODROMO_HPP

#include <vector>
#include <ncurses.h>
#include "caballo.hpp"

using namespace std; 

vector<pair<int, int>> generarCamino(int ancho, int alto, int metaX);
void dibujarPista(int ancho, int alto);
void dibujarCaballos(const vector<pair<int, int>> &camino, const vector<Caballo> &caballos);

#endif