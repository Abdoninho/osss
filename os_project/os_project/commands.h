#pragma once
#include "Directory.h"
#include "Mini_FAT.h"
#include "File_Entry.h"
#include "tokenizer.h"
#include "parser.h"
#include "commands.h"
#include <string>
#include <vector>
#include <map>


class Commands {
private:
    Directory** currentDirectoryPtr; // Pointer to current directory
    std::vector<std::string> commandHistory; // History of executed commands

    // Command help dictionary
    std::map<std::string, std::pair<std::string, std::string>> commandHelp;

    // Helper methods
    void showGeneralHelp();
    void showCommandHelp(const std::string& command);


public:
    // Constructor
    Commands(Directory** currentDirPtr);

    // Process a command
    void processCommand(const std::string& input, bool& isRunning);
};