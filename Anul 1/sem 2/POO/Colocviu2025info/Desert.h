//
// Created by Alexandra on 5/19/2026.
//

#ifndef DESERT_H
#define DESERT_H
#include <string>
#include <iostream>
#include "Produs.h"
class Desert : public Produs {
    private:
    std::string format;
    public:
    Desert(const std::string& nume, float gramaj, const std::string& format);
    virtual ~Desert() override;
    virtual float getValoareEnergie() const override;
    std::string getFormat() const;
};
#endif //DESERT_H
