//
// Created by Alexandra on 5/23/2026.
//
#include "Simulator.h"
#include "Casier.h"
#include "Bucatar.h"
#include "Livrator.h"
#include <iostream>
#include "Bautura.h"
#include "Desert.h"
#include "Burger.h"
#include <algorithm>

Simulator::Simulator() {
    // Adaugi produsele predefinite direct în vectorul clasei
    meniuProduse.push_back(make_shared<Bautura>("Coca-Cola", 500, true));
    meniuProduse.push_back(make_shared<Bautura>("Apa Minerala", 500, false));
    meniuProduse.push_back(make_shared<Desert>("Cheesecake", 150, "felie"));

    std::vector<std::string> ingr = {"carne", "branza", "sos"};
    meniuProduse.push_back(make_shared<Burger>("Cheeseburger", 350, ingr));
}

Simulator &Simulator::getInstance() {
    static Simulator s;
    return s;
}

void Simulator::afisareAngajati() {
    int nrCasieri = 0;
    int nrBucatari = 0;
    int nrLivratori = 0;
    for (auto const&a: angajati) {
        if (dynamic_pointer_cast<Casier>(a))
            nrCasieri++;
        else
            if (dynamic_pointer_cast<Bucatar>(a))
                nrBucatari++;
            else
                if (dynamic_pointer_cast<Livrator>(a))
                    nrLivratori++;
    }
    cout << "\n--- ECHIPA RESTAURANTULUI ---\n";
    cout << "Casieri: " << nrCasieri << "\n";
    cout << "Bucatari: " << nrBucatari << "\n";
    cout << "Livratori: " << nrLivratori << "\n\n";
}

void Simulator::adaugareAngajati() {
    int optiune;
    cout<<"ce angajat adaugi? 1. Casier, 2. Bucatar, 3. Livrator: ";
    cin>>optiune;
    if (optiune==1)
        angajati.push_back(make_shared<Casier>());
    else if (optiune==2)
        angajati.push_back(make_shared<Bucatar>());
    else if (optiune==3)
        angajati.push_back(make_shared<Livrator>());
    else
        throw runtime_error("Tip gresit");
}

void Simulator::comanda() {
    int op;
    do {
        cout << "Adaugare comanda? (1 = Da / 0 = Nu): ";
        cin >> op;

        if (op == 1) {
            auto nouaComanda = make_shared<Comanda>(); // Creează comanda cu ID automat
            comenzi.push_back(nouaComanda); // O SALVĂM în vectorul clasei!
            cout << "-> Comanda cu ID " << nouaComanda->getId() << " a fost inregistrata.\n";
        }
    } while (op == 1);

    if (comenzi.empty()) {
        cout << "Nu exista comenzi de procesat.\n";
        return;
    }
}

void Simulator::ruleaza() {
    int optiune = -1;
    do {
        try {
            cout << "\n1.Adauga angajat\n";
            cout << "2.Vezi numarul de angajati\n";
            cout << "3.Simuleaza ciclu comenzi\n";
            cout << "0.Exit\n";
            cout << "Alege: ";
            cin >> optiune;

            switch (optiune) {
                case 1: adaugareAngajati(); break;
                case 2: afisareAngajati(); break;
                case 3: comanda(); break;
                case 0: break;
            }
        }
        catch (const exception &e) {
            cout << "Eroare prinsa: " << e.what() << "\n";
        }
    } while (optiune != 0);
}