//
// Created by Alexandra on 5/19/2026.
//

#ifndef BAUTURA_H
#define BAUTURA_H
#include <string>
#include <iostream>
#include "Produs.h"
class Bautura : public Produs {
    private:
    bool estePet;
    public:
    Bautura(const std::string& nume, float gramaj, bool estePet);
    virtual ~Bautura();
    virtual float getValoareEnergie() const override;
    bool getEstePet() const;
};
#endif //BAUTURA_H
