//
// Created by Alexandra on 5/22/2026.
//

#ifndef LIVRATOR_H
#define LIVRATOR_H
#include "Angajat.h"
#include <iostream>
class Livrator: public Angajat {
    public:
    Livrator() = default;
    virtual ~Livrator() override = default;
    virtual void preluare() override;
    virtual void preparare() override;
    virtual void livrare() override;
};
#endif //LIVRATOR_H
