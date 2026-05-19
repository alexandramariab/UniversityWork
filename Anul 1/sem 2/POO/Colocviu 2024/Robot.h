//
// Created by Alexandra on 5/18/2026.
//

#ifndef ROBOT_H
#define ROBOT_H
#include "Item.h"
#include <iostream>

class Robot : public Item {
protected:
    int damage;
    int nivel;
    int viata;
public:
    Robot(int id, int pret, int damage, int nivel, int viata);
    virtual ~Robot();
    virtual void doUpgrade() = 0;
    virtual int getCostUpgrade() const = 0;
    virtual void print(std::ostream& os) const = 0;
    int getNivel() const;
    int getViata() const;
    int getDamage() const;

};

class RobotAerian: public Robot {
private:
    int autonomieZbor;
    public:
    RobotAerian(int id);
    virtual ~RobotAerian() override;
    virtual void doUpgrade() override;
    virtual int getCostUpgrade() const override;
    virtual void print(std::ostream& os) const override;

    int getAutonomieZbor() const;

};

class RobotTerestru: public Robot {
    private:
    int nrGloante;
    bool areScut;

    public:
    RobotTerestru(int id);
    virtual ~RobotTerestru() override;
    virtual void doUpgrade() override;
    virtual int getCostUpgrade() const override;
    virtual void print(std::ostream& os) const override;
    int getNrGloante() const;
    int getAreScut() const;
};
#endif //ROBOT_H
