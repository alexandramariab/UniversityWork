//
// Created by Alexandra on 5/19/2026.
//

#ifndef BURGER_H
#define BURGER_H
#include <string>
#include "Produs.h"
#include <iostream>
#include <vector>

class Burger : public Produs {
    private:
    std::vector<std::string> ingrediente;
    public:
    Burger(const std::string& nume, float gramaj, const std::vector<std::string>& ingrediente);
    virtual ~Burger();
    virtual float getValoareEnergie() const override;
    const virtual std::vector<std::string>& getIngrediente() const;

};
#endif //BURGER_H
