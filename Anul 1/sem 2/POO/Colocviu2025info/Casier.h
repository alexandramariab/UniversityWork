//
// Created by Alexandra on 5/22/2026.
//

#ifndef CASIER_H
#define CASIER_H
#include "Angajat.h"
#include <iostream>

class Casier: public Angajat {
public:
    Casier() = default;
    virtual ~Casier() override = default;
    virtual void preluare() override;
    virtual void preparare() override;
    virtual void livrare() override;
};
#endif //CASIER_H
