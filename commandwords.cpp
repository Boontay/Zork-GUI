#include "commandwords.h"

vector<string> CommandWords::validCommands;

CommandWords::CommandWords() {
    validCommands.push_back("go");
    validCommands.push_back("quit");
    validCommands.push_back("info");
    validCommands.push_back("map");
    validCommands.push_back("take");
    validCommands.push_back("put");
    validCommands.push_back("teleport");
}

bool CommandWords::isCommand(string aString) {
    for (unsigned int i = 0; i < validCommands.size(); i++)
    {
        if (validCommands[i].compare(aString) == 0)
            return true;
    }
    // if we get here, the string was not found in the commands
    return false;
}

string CommandWords::showAll() {
    //Loops through validCommands and prints each to the screen.
    string output = "";

    for (unsigned int i = 0; i < validCommands.size(); i++)
    {
        //cout << validCommands[i]<< "  ";
        output += validCommands[i] + " ";
    }
    //cout << endl;

    return output;
}
