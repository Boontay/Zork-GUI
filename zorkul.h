#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "command.h"
//#include "parser.h"
#include "room.h"
#include "item.h"
#include "weapon.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ZorkUL {
private:
    Room *currentRoom;
    vector<Room> rooms;
    void createRooms();
    bool processCommand(Command command);
    void goRoom(Command command);
    void createItems();
    void displayItems();

public:
    ZorkUL();
    void play();
    string printWelcome();
    string printHelp();
    string printEnd();
    string go(string direction);
    string teleport();
    string map();
    string viewCharacterInfo();
    string viewItems();
    Room getCurrentRoom();
};

#endif
