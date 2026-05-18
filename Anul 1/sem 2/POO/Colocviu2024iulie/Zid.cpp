//
// Created by Alexandra on 5/17/2026.
//
#include "Zid.h"
Zid::Zid(int id)
    : Item(id, 300), inaltime(2.0f), lungime(1.0f), grosime(0.5f) {}
Zid::~Zid(){}

void Zid::doUpgrade() {
        inaltime=inaltime+1.0f;
        lungime=lungime+1.0f;
        grosime=grosime+1.0f;
}

int Zid::getCostUpgrade() const {
    return static_cast<int>(100*lungime*grosime*inaltime);
}
void Zid::print(std::ostream& os) const {
    Item::print(os); // Va afișa mai întâi "Item: "
    os << "Zid [ID: " << getId()
       << ", Lungime: " << lungime << "m"
       << ", Grosime: " << grosime << "m"
       << ", Inaltime: " << inaltime << "m"
       << ", Cost Upgrade urmator: " << getCostUpgrade() << " puncte]";
}
float Zid::getGrosime() const { return grosime; }
float Zid::getLungime() const { return lungime; }
float Zid::getInaltime() const { return inaltime; }
