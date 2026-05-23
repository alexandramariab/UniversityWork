//
// Created by Alexandra on 5/23/2026.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include <vector>
#include <memory>
#include "Angajat.h"
#include "Comanda.h"
#include "Produs.h"
class Simulator {
private:
    Simulator();
    ~Simulator() = default;
    Simulator(const Simulator &simulator)=delete;
    Simulator &operator=(const Simulator &simulator)=delete;
    vector<shared_ptr<Angajat>>angajati;
    vector<shared_ptr<Comanda>>comenzi;
    std::vector<std::shared_ptr<Produs>> meniuProduse;

public:
    static Simulator& getInstance();
    void ruleaza();
    void comanda();
    void adaugareAngajati();
    void afisareAngajati();

};
#endif //SIMULATOR_H
