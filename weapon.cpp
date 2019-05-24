#include "weapon.h"

Weapon::Weapon(string description, int weightGrams, float value, float damage, int durability) : Item(description, weightGrams, value)
{
    this->damage = damage;
    this->durability = durability;
}
