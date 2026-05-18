//
// Created by Alexandra on 5/17/2026.
//
#include "Item.h"

Item::Item(int id, int pret) : id(id), pret(pret) {}
Item::~Item() {}

void Item::upgrade() {
    doUpgrade();
}

int Item::getId() const {
    return id;
}