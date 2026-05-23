//
// Created by Alexandra on 5/19/2026.
//

#ifndef ANGAJAT_H
#define ANGAJAT_H
#include <iostream>
class Angajat {
protected:
    int puncteEnergie;
public:
    Angajat()=default;
    virtual ~Angajat()=default;
    virtual void preluare()=0;
    virtual void preparare()=0;
    virtual void livrare()=0;

    int getPct() const;
};
#endif //ANGAJAT_H
