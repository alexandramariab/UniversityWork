//
// Created by Alexandra on 5/17/2026.
//

#ifndef ZID_H
#define ZID_H
#include "Item.h"
#include <iostream>

class Zid : public Item {
private:
    float inaltime;
    float lungime;
    float grosime;
public:
    Zid(int id);
    virtual ~Zid();
    virtual void doUpgrade();
    virtual int getCostUpgrade() const override;
    float getGrosime() const;
    float getLungime() const;
    float getInaltime() const;

    virtual void print(std::ostream& os) const override;

};
#endif //ZID_H
