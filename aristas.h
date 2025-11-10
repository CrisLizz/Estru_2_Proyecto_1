#ifndef ARISTA_H
#define ARISTA_H

#include "nodo.h"

class Arista {
public:
    Nodo* origen = nullptr;
    Nodo* destino = nullptr;
    int peso = 1;
    bool desbloqueada = false; // se ilumina solo si se sigue esa ruta

    Arista(Nodo* o = nullptr, Nodo* d = nullptr, int p = 1)
        : origen(o), destino(d), peso(p) {}
};

#endif // ARISTA_H
