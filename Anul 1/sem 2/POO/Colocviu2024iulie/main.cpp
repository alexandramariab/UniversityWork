#include <iostream>
#include "Item.h"
#include <vector>
#include <algorithm>
#include <memory>

#include "Zid.h"
#include "Turn.h"
#include "Robot.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main() {
    int puncteJucator=50000;
    int idCurent=1;
    std::vector<std::shared_ptr<Item>> inventar;
    int optiune=-1;
    while(optiune!=0) {
        std::cout << "\n=== BATALIA INTERGALACTICA ===\n";
        std::cout << "Puncte disponibile: " << puncteJucator << "\n";
        std::cout << "1. Adaugare element (Zid/Turn/Robot)\n";
        std::cout << "2. Upgrade element dupa ID\n";
        std::cout << "3. Afisare inventar crescator dupa cost upgrade\n";
        std::cout << "4. Afisare doar elemente de tip Robot\n";
        std::cout << "5. Vinde un element (Sell)\n";
        std::cout << "0. Iesire program\n";
        std::cout << "Alege optiunea: ";
        std::cin >> optiune;

        if(optiune==1) {
            std::cout << "Ce doresti sa adaugi?\n1. Zid (300p)\n2. Turn (500p)\n3. Robot Aerian (100p)\n4. Robot Terestru (50p)\n"; // [cite: 12, 13, 14, 15, 16]
            int tip;
            std::cin >> tip;
            if(tip==1 && puncteJucator>=300) {
                inventar.push_back(std::make_shared<Zid>(idCurent++));
                puncteJucator -= 300;
                std::cout << "Zid adaugat cu succes cu id-ul: "<<idCurent-1<<"\n";
            }
            else if(tip==2 && puncteJucator>=500) {
                inventar.push_back(std::make_shared<Turn>(idCurent++));
                puncteJucator -= 500;
                std::cout << "Turn adaugat cu succes cu id-ul: "<<idCurent-1<<"\n";
            }
            else if(tip==3 && puncteJucator>=100) {
                inventar.push_back(std::make_shared<RobotAerian>(idCurent++));
                puncteJucator -= 100;
                std::cout << "Robot Aerian adaugat cu succes cu id-ul: "<<idCurent-1<<"\n";
            }
            else if(tip==4 && puncteJucator>=50) {
                inventar.push_back(std::make_shared<RobotTerestru>(idCurent++));
                puncteJucator -= 50;
                std::cout << "Robot Terestru adaugat cu succes cu id-ul: "<<idCurent-1<<"\n";
            }
            else{
                std::cout << "Puncte insuficiente sau optiune invalida!\n";
            }
        }

        else if(optiune==2) {
            int idCautat;
            std::cout << "Introdu ID-ul elementului pentru upgrade: ";
            std::cin >> idCautat;
            std::shared_ptr<Item> gasit = nullptr;
            for (const auto& item : inventar) {
                if(item->getId()==idCautat) {
                    gasit = item;
                    break;
                }
            }

            if(gasit!=nullptr) {
                int cost=gasit->getCostUpgrade();
                if (cost<=puncteJucator) {
                    gasit->upgrade();
                    puncteJucator -= cost;
                    std::cout << "Upgrade realizat! S-au consumat " << cost << " puncte.\n";
                } else {
                    std::cout << "Nu ai suficiente puncte! Necesar: " << cost << "\n"; // [cite: 18]
                }
            } else
                std::cout << "Elementul cu ID-ul " << idCautat << " nu exista in inventar.\n";
            }
        else if (optiune == 4) {
            std::cout << "\n--- Elemente de tip Robot ---\n";
            bool areRoboti = false;
            for (const auto& item : inventar) {
                // RTTI cu shared_ptr: folosim .get() ca sa extragem pointerul brut (Raw Pointer) necesar lui dynamic_cast
                if (dynamic_cast<Robot*>(item.get()) != nullptr) {
                    std::cout << *item << "\n";
                    areRoboti = true;
                }
            }
            if (!areRoboti) {
                std::cout << "Nu exista niciun robot in inventar.\n";
            }
        }
        else if (optiune == 5) {
            int idVanzare;
            std::cout << "Introdu ID-ul elementului pe care vrei sa-l vinzi: ";
            std::cin >> idVanzare;

            bool sters = false;
            for (auto it = inventar.begin(); it != inventar.end(); ++it) {
                if ((*it)->getId() == idVanzare) {
                    // Aici strălucește shared_ptr! Nu mai scriem "delete".
                    // Prin erase, shared_ptr-ul este scos din vector, contorul lui de referințe scade la 0,
                    // iar memoria se eliberează automat în fundal.
                    inventar.erase(it);
                    puncteJucator += 500; // Primește fix 500 de puncte [cite: 26]
                    std::cout << "Element vandut cu succes! Ai primit 500 de puncte.\n";
                    sters = true;
                    break;
                }
            }
            if (!sters) {
                std::cout << "Elementul cu ID-ul specificat nu a fost gasit.\n";
            }
        }

    }
    
    return 0;
}