//
// Created by Alexandra on 5/17/2026.
//

#ifndef ITEM_H
#define ITEM_H
#include <iostream>
class Item {
private:
    virtual void doUpgrade() = 0;
protected:
    const int id;
    int pret;
public:
    Item(int id, int pret);
    virtual ~Item();
    void upgrade();
    virtual int getCostUpgrade() const = 0;
    virtual void print(std::ostream& os) const {
        os << "Item: ";
    }
    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        item.print(os);
        return os;
    };
    int getId() const;

};
#endif //ITEM_H
