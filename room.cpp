#include "room.h"
#include "command.h"
#include <algorithm>

Room::Room(string description)
{
    this->description = description;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    if (north != nullptr)
    {
        exits["north"] = north;
    }

    if (east != nullptr)
    {
        exits["east"] = east;
    }

    if (south != nullptr)
    {
        exits["south"] = south;
    }

    if (west != nullptr)
    {
        exits["west"] = west;
    }
}

string Room::shortDescription()
{
    return description;
}

string Room::longDescription()
{
    return "room = " + description + "." + exitString();
}

string Room::exitString()
{
    string returnString = "\nexits = ";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;
    return returnString;
}

Room* Room::nextRoom(string direction)
{
    map<string, Room*>::iterator next = exits.find(direction);

    if (next == exits.end())
    {
        return nullptr;
    }

    return next->second;
}

void Room::addItem(Item *inItem)
{
    itemsInRoom.push_back(*inItem);
}

string Room::displayItems()
{
    string tempString = "Items in Room: ";
    int itemAmount = itemsInRoom.size();

    if (itemAmount < 1)
    {
        tempString = "No items in room.";
    }
    else if (itemAmount > 0)
    {
        int x = 0;

        for (int n = itemAmount; n > 0; n--)
        {
            tempString += itemsInRoom[x].getShortDescription() + " ";
            x++;
        }
    }

    return tempString;
}

int Room::numberOfItems()
{
    return itemsInRoom.size();
}

void Room::removeItem(Item item)
{
    int pos = 0;

    for (unsigned int i = 0; i < (unsigned int)itemsInRoom.size(); i++)
    {
        if (itemsInRoom[i] == item)
        {
            pos = (int)i;
            break;
        }
    }

    itemsInRoom.erase(itemsInRoom.begin() + pos);
}

Item Room::findItem(Item item)
{
    for (unsigned int i = 0; i < itemsInRoom.size(); i++)
    {
        if (itemsInRoom[i] == item)
        {
            return itemsInRoom[i];
        }
    }
}

vector<Item> Room::viewItems()
{
    return itemsInRoom;
}

bool Room::allItemsCollected()
{
    if (itemsInRoom.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Room::containsExit(string exit)
{
    return exits.find(exit) != exits.end();
}
