#include "item.h"

Item::Item(string description, int weightGrams, float value)
{
    this->description = description;
    this->weightGrams = weightGrams;
    this->value = value;
}

Item::Item(string description)
{
    this->description = description;
    this->weightGrams = 1;
    this->value = 1;
}

bool Item::operator==(Item &i)
{
    int test = 0;

    if (this->getShortDescription() == i.getShortDescription())
    {
        test = 1;
    }

    return test;
}

void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
    {
       cout << "Weight invalid, must be 0 < Weight < 9999." ;
    } else {
        weightGrams = inWeightGrams;
    }
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       cout << "Value invalid, must be 0 < Value < 9999." ;
    else
       value = inValue;
}

int Item::getWeight()
{
    return weightGrams;
}

string Item::getShortDescription()
{
    return description;
}

string Item::getLongDescription()
{
    return " item(s), " + description + ".\n";
}
