//
// Created by Alexandra on 5/19/2026.
//

#ifndef PRODUS_H
#define PRODUS_H
#include <iostream>
#include <string>
class Produs {
    protected:
    std::string nume;
    float gramaj;
    public:
    Produs(const std::string& nume, float gramaj);
    virtual ~Produs();
    virtual float getValoareEnergie() const =0;
    std::string getNume() const;
    float getGramaj() const;
};

#endif //PRODUS_H
