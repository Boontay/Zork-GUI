#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "zorkul.h"
#include <string>
#include <vector>
using std::vector;
using namespace std;

class Character {
    friend class MainWindow;

private:
    string description;
    vector<Item> itemsInCharacter;
    float carriedWeight;
    int stamina;
    int health;

public:
    Character();
    Character(string description);
    string shortDescription();
    string longDescription();
    vector<Item> viewItems();
    Item findItem(Item item);
    int findItemPos(Item item);
    void removeItem(Item item);
    bool isOverencumbered(float maxWeight);
    string viewCharacterInfo();
    void addItem(string itemDescription);
    void addItem(Item *item);
    void addItem(Item &item);
    int getStamina();
    void setStamina(int stamina);
    void decrementStamina();
    int getHealth();
    void setHealth(int health);
    void decrementHealth();
};

#endif
