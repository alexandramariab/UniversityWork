#include <iostream>
#include <vector>     // Bifează 0.25p - STL containers [cite: 88, 89]
#include <memory>     // Pentru std::shared_ptr
#include <algorithm>  // Pentru std::sort și std::partition (0.25p - alte elemente STL) [cite: 90, 91]
#include <typeinfo>   // Pentru RTTI [cite: 100, 101]
#include "Simulator.h"
#include "Comanda.h"
#include "Casier.h"
#include "Bucatar.h"
#include "Livrator.h"

// Includem headerele produselor tale (presupunem denumirile lor)
#include "Bautura.h"
#include "Desert.h"
#include "Burger.h"
using namespace std;



// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main() {

    Simulator& sim = Simulator::getInstance();
    sim.ruleaza();
    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}