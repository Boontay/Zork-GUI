#include "command.h"

Command::Command(string firstWord, string secondWord) {
    this->commandWord = firstWord;
    this->secondWord = secondWord;
}

string Command::getCommandWord() {
    return this->commandWord;
}

string Command::getSecondWord() {
    return this->secondWord;
}

bool Command::isUnknown() {
    return (commandWord.empty());
}

bool Command::hasSecondWord() {
    return (!secondWord.empty());
}
