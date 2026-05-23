//
// Created by Alexandra on 5/22/2026.
//
#include "Comanda.h"
int Comanda::contorID = 1;
Comanda::Comanda(): energieNecesara(0) {
    id=contorID;
    contorID++;
}

Comanda::~Comanda() {}

void Comanda::adaugaProdus(std::shared_ptr<Produs> p) {
    produse.push_back(p);
    // Adăugăm energia produsului la energia totală a comenzii [cite: 88]
    energieNecesara += p->getValoareEnergie();
}

float Comanda::calculeazaEnergieTotala() const {
    float total = 0;
    for (const auto&p: produse) {
        total += p->getValoareEnergie();
    }
    return total;

}
int Comanda::getId() const {
    return id;
}

float Comanda::getEnergieNecesara() const {
    return energieNecesara;
}
