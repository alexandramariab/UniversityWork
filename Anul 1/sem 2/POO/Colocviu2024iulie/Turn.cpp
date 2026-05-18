//
// Created by Alexandra on 5/17/2026.
//
#include "Turn.h"
Turn::Turn(int id):Item(id, 500),putereLaser(1000) {}
Turn::~Turn() {}
void Turn::doUpgrade() {
    putereLaser = putereLaser +500;
}

int Turn::getCostUpgrade() const {
    return 500*putereLaser;
}

void Turn::print(std::ostream& os) const {
    Item::print(os); // Va afișa mai întâi "Item: "
    os << "Turn [ID: " << getId()
       << ", Puterea laser: " << putereLaser<< "kw"
       << ", Cost Upgrade urmator: " << getCostUpgrade() << " puncte]";
}

int Turn::getPutereLaser() const {
    return putereLaser;
}
