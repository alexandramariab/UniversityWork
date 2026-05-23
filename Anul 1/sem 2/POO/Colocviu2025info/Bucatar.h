//
// Created by Alexandra on 5/22/2026.
//

#ifndef BUCATAR_H
#define BUCATAR_H
#include "Angajat.h"
#include <iostream>
class Bucatar: public Angajat {
public:
    Bucatar();
    virtual ~Bucatar() override = default;
    virtual void preluare() override;
    virtual void preparare() override;
    virtual void livrare() override;
};
#endif //BUCATAR_H
