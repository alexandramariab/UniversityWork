//
// Created by Alexandra on 5/19/2026.
//
#include "Burger.h"

Burger::Burger(const std::string &nume, float gramaj, const std::vector<std::string> &ingrediente) : Produs(nume,gramaj), ingrediente(ingrediente){}

Burger::~Burger() {}

float Burger::getValoareEnergie() const {
    return gramaj*0.25*ingrediente.size();
}

const std::vector<std::string>& Burger::getIngrediente() const {
    return ingrediente;
}
