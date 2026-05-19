//
// Created by Alexandra on 5/17/2026.
//

#ifndef TURN_H
#define TURN_H
#include "Item.h"
#include <iostream>

class Turn : public Item {
    private:
    int putereLaser;
    public:
    Turn(int id);
    virtual ~Turn();
    virtual void doUpgrade();
    int getCostUpgrade() const override;
    void print(std::ostream& os) const override;
    int getPutereLaser() const;

};
#endif //TURN_H
