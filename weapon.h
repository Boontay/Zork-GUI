#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item {
public:
    Weapon(string description, int weightGrams, float value, float damage, int durability);

private:
    float damage;
    int durability;
};

#endif // WEAPON_H
