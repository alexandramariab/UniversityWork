//
// Created by Alexandra on 5/19/2026.
//
#include "Desert.h"
Desert::Desert(const std::string& nume, float gramaj, const std::string& format): Produs(nume,gramaj), format(format){}
Desert::~Desert(){}
std::string Desert::getFormat() const {
    return format;
}
float Desert::getValoareEnergie() const {
    if (format == "felie")
        return 25;
    else if (format == "portie")
        return 0.5*gramaj;
    else if (format == "cupa")
        return 2*gramaj;
    throw std::invalid_argument("Format de servire invalid pentru desert: " + format +
                                ". Trebuie sa fie: felie, portie sau cupa.");
}