#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item{
private:
    string description;
    string longDescription;
    int weightGrams;
    float value;

public:
    Item();
    Item(string description, int weightGrams, float value);
    Item(string description);
    //Item operator==(const Item& i);
    string getShortDescription();
    bool operator==(Item &i);
    string getLongDescription();
    int getWeight();
    void setWeight(int inWeightGrams);
    float getValue();
    void setValue(float inValue);
};

#endif /*ITEM_H_*/
