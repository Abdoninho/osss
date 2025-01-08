#include "commands.h"
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

// Constructor
Commands::Commands(Directory** currentDirPtr)
    : currentDirectoryPtr(currentDirPtr) {
    // Populate the help dictionary
    commandHelp["help"] = {
        "Provides help information for commands.",
        "Usage:\n"
        "  help\n"
        "  help [command]\n\n"
        "Description:\n"
        "  Displays help for all commands or detailed help for a specific command."
    };
    commandHelp["pwd"] = {
        "Prints the current working directory.",
        "Usage:\n  pwd\n\nDescription:\n  Shows the absolute path of the current directory."
    };
    commandHelp["quit"] = {
        "Quit the shell",
        "Usage:\n  quit\n\nDescription:\n  Quit the shell "
    };
    commandHelp["cls"] = {
        "clear the screen",
        "Usage:\n  cls\n\nDescription:\n" "clear the screan"
            
    };

    commandHelp["copy"] = {
    "copy one or more files to another location",
    "Usage:\n  copy [source]\nor\ncopy[source] [destination]  \n\nDescription:\n copy one or more files to another location"

    };


    commandHelp["dir"] = {
       "List the content of the directory",
       "Usage:\n"
       "  dir\n"
       "  dir [directory]\n\n"
       "Description:\n"
       "  List the content of the directory."
    };



    // Add more commands as needed
}

// Show general help for all commands
void Commands::showGeneralHelp() {
    cout << "Available Commands:\n";
    for (const auto& cmd : commandHelp) {
        cout << "  " << cmd.first << " - " << cmd.second.first << "\n";
    }
}

// Show detailed help for a specific command
void Commands::showCommandHelp(const string& command) {
    auto it = commandHelp.find(command);
    if (it != commandHelp.end()) {
        cout << it->second.second << "\n";
    }
    else {
        cout << "Error: Command '" << command << "' is not supported.\n";
    }
}

// Process commands
void Commands::processCommand(const string& input, bool& isRunning) {
    // Add command to history
    if (!input.empty()) {
        commandHistory.push_back(input);
    }

    // Tokenize the input
    vector<string> tokens = Tokenizer::tokenize(input);

    if (tokens.empty()) {
        return; // No command entered
    }

    // Parse tokens into command and arguments
    Command cmd = Parser::parse(tokens);

    // Convert command name to lowercase for case-insensitive comparison
    transform(cmd.name.begin(), cmd.name.end(), cmd.name.begin(), ::tolower);

    // Handle the commands
    if (cmd.name == "help") {
        if (cmd.arguments.empty()) {
            showGeneralHelp();
        }
        else if (cmd.arguments.size() == 1) {
            showCommandHelp(cmd.arguments[0]);
        }
        else {
            cout << "Error: Invalid syntax for help command.\n";
            cout << "Usage:\n  help\n  help [command]\n";
        }
    }
   
    else if (cmd.name == "pwd") {
        // Example for handling 'pwd' command
        cout << "Current Directory: " << (*currentDirectoryPtr)->getFullPath() << "\n";
    }
    else if (cmd.name == "ls") {
        // Example for handling 'ls' command
        cout << "Contents of " << (*currentDirectoryPtr)->getFullPath() << ":\n";
        for (const auto& entry : (*currentDirectoryPtr)->DirOrFiles) {
            if (entry.dir_attr == 0x10) {
                cout << "<DIR> " << entry.getName() << "\n";
            }
            else {
                cout << "      " << entry.getName() << "\n";
            }
        }
    }
    else if (cmd.name == "quit") {
        // Exit the shell
        isRunning = false;
    }



    else {
        cout << "Error: Command '" << cmd.name << "' is not supported.\n";
    }
}
