//
// Created by Alexandra on 5/19/2026.
//
#include "Produs.h"

Produs::Produs(const std::string& nume, float gramaj): nume(nume), gramaj(gramaj){}
Produs::~Produs(){}
std::string Produs::getNume() const{
    return nume;
}
float Produs::getGramaj() const{
    return gramaj;
}