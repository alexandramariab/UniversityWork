//
// Created by Alexandra on 5/19/2026.
//
#include "Bautura.h"
Bautura::Bautura(const std::string& nume, float gramaj, bool estePet) : Produs(nume,gramaj), estePet(estePet){}
Bautura::~Bautura(){}
float Bautura::getValoareEnergie() const {
    if (estePet)
        return 25;
    else
        return 0.25*gramaj;
}

bool Bautura::getEstePet() const{
    return estePet;
}

