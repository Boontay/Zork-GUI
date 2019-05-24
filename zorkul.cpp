#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
#include "zorkul.h"

ZorkUL::ZorkUL() {
    createRooms();
    srand(time(0));
}
void ZorkUL::createRooms() {
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;

    a = new Room("a");
        a->addItem(new Item("x", 1, 11));
        a->addItem(new Item("y", 2, 22));
    b = new Room("b");
        b->addItem(new Item("xx", 3, 33));
        b->addItem(new Item("yy", 4, 44));
    c = new Room("c");
        c->addItem(new Weapon("sword", 340, 20.0, 5.0, 3));
    d = new Room("d");
    e = new Room("e");
    f = new Room("f");
    g = new Room("g");
    h = new Room("h");
    i = new Room("i");
    j = new Room("j");

//             (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a, NULL, j);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
    j->setExits(NULL, j, NULL, NULL);

    rooms.push_back(*a);
    rooms.push_back(*b);
    rooms.push_back(*c);
    rooms.push_back(*d);
    rooms.push_back(*e);
    rooms.push_back(*f);
    rooms.push_back(*g);
    rooms.push_back(*h);
    rooms.push_back(*i);
    rooms.push_back(*j);

    currentRoom = a;
}
string ZorkUL::printWelcome() {
    return "start \ninfo for help\n" + currentRoom->longDescription();
}
string ZorkUL::printEnd() {
    return "end";
}
string ZorkUL::printHelp() {
    return "Valid inputs are the buttons in this window. Click on the button corresponding to the action you would like to take.";
}
string ZorkUL::teleport() {
    currentRoom = &rooms.at((int) rand() % rooms.size());

    if (currentRoom == nullptr) {
        return "error teleporting";
    } else {
        return currentRoom->longDescription();
    }
}
string ZorkUL::map() {
    string output;
    output += "\n          [h] --- [f] --- [g]";
    output += "\n                      |         ";
    output += "\n                      |         ";
    output += "\n[j] --- [c] --- [a] --- [b]";
    output += "\n                      |         ";
    output += "\n                      |         ";
    output += "\n            [i] --- [d] --- [e]";
    return output;
}
string ZorkUL::go(string direction) {
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL) {
        return "You can't go that way.";
    } else {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}
string ZorkUL::viewItems() {
    return currentRoom->displayItems();
}
Room ZorkUL::getCurrentRoom() {
    return *currentRoom;
}
