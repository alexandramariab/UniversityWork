//
// Created by Alexandra on 5/18/2026.
//
#include "Robot.h"
Robot::Robot(int id, int pret, int damage, int nivel, int viata) : Item(id, pret), damage(damage), nivel(nivel), viata(viata) {}
Robot::~Robot() {}

int Robot::getNivel() const { return nivel; }
int Robot::getViata() const { return viata; }
int Robot::getDamage() const { return damage; }

RobotAerian::RobotAerian(int id) : Robot(id, 100,100, 1, 100), autonomieZbor(10){}
RobotAerian::~RobotAerian() {}

void RobotAerian::doUpgrade() {
    autonomieZbor+=1;
    nivel+=1;
    damage+=25;
}

int RobotAerian::getCostUpgrade() const {
    return 50*autonomieZbor;
}

int RobotAerian::getAutonomieZbor() const {
    return autonomieZbor;
}

void RobotAerian::print(std::ostream &os) const {
    Item::print(os); // Va afișa mai întâi "Item: "
    os << "Robot Aerian [ID: " << getId()
       << ", Nivel: " << nivel
       << ", Viata: " << viata
       << ", Damage: " << damage
       << ", Autonomie: " << autonomieZbor << " ore"
       << ", Cost Upgrade urmator: " << getCostUpgrade() << " puncte]";
}


RobotTerestru::RobotTerestru(int id) : Robot(id, 50,100, 1, 100), nrGloante(500), areScut(false){}
RobotTerestru::~RobotTerestru() {}
void RobotTerestru::doUpgrade() {
    nrGloante += 100;
    nivel +=1;
    damage +=50;
    if (nivel==5) {
        areScut=true;
        viata+=50;
    }
}

int RobotTerestru::getCostUpgrade() const {
    return 10*nrGloante;
}
int RobotTerestru::getNrGloante() const {
    return nrGloante;
}
int RobotTerestru::getAreScut() const {
    return areScut;
}
void RobotTerestru::print(std::ostream &os) const {

    Item::print(os);
    os << "Robot Terestru [ID: " << getId()
    << ", Nivel: " << nivel
    << ", Viata: " << viata
    << ", Damage: " << damage
    << ", Nr Gloante: " << getNrGloante()
    << ", Are Scut: " << getAreScut()
    << ", Cost Upgrade urmator: " << getCostUpgrade() << " puncte]";

}