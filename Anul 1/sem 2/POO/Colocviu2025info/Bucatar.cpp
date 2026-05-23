//
// Created by Alexandra on 5/22/2026.
//
//
// Created by Alexandra on 5/22/2026.
//
//
#include "Bucatar.h"
Bucatar::Bucatar() {
    puncteEnergie = puncteEnergie * 2; // Dacă pornea de la 100, acum va avea 200!
}
void Bucatar::preluare() {
    puncteEnergie-=100;
}

void Bucatar::livrare() {
    puncteEnergie-=100;
}

void Bucatar::preparare() {
    puncteEnergie-=100;
}
