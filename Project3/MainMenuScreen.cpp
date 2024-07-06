#include <iostream>

#include "MainMenuScreen.h"
#include "Console.h"

extern Console console;

MainMenuScreen::MainMenuScreen()
    : ConsoleName("MAIN_MENU") {

}

MainMenuScreen::~MainMenuScreen() {

}

void MainMenuScreen::onExecute() {
    display();
    process();
}

void MainMenuScreen::display() {
    displayHeader();
}

void MainMenuScreen::process() {
    string command;
    while (true) {
        std::cout << "root:\\> ";
        getline(cin, command);
        handleCommand(command);
        std::cout << endl;
    }
}

void MainMenuScreen::displayHeader() {
    std::cout << R"(
         ____  ____  ____  ____  _____ ____ ___  _
        /   _\/ ___\/  _ \/  __\/  __// ___\\  \//
        |  /  |    \| / \||  \/||  \  |    \ \  / 
        |  \__\___ || \_/||  __/|  /_ \___ | / /  
        \____/\____/\____/\_/   \____\\____//_/   
    )" << endl;

    std::cout << "Hello. Welcome to CSOPESY command line interface." << endl << endl;
}

void MainMenuScreen::handleCommand(string command) {
    if (command == "exit") {
        std::cout << "Exiting the program..." << std::endl;
        exit(0);

    }
    else if (command == "initialize" && !console.isInitialized()) {
        console.setInitialized();

    }
    else if (console.isInitialized()) {
        if (command == "clear" || command == "cls") {
            system("cls");

        }
        else if (command == "marquee") {
            console.switchScreen("MARQUEE_SCREEN");

        }
        else if (command.substr(0, 6) == "screen") {
            if (command == "screen -ls") {
                console.displayStatus();
            }

            else if (command.substr(0, 9) == "screen -s") {
                std::string processName = command.substr(10);
                trim(processName);
                if (processName.empty()) {
                    std::cout << "Command not recognized! Please provide a process name." << std::endl;
                }
                else {
                    if (!console.ifProcessExists(processName)) {
                        console.createProcessScreen(processName);
                    }
                    else {
                        std::cout << "Process already exists or has existed. Please provide a differen name." << std::endl;
                    }

                }
            }

            else if (command.substr(0, 9) == "screen -r") {
                std::string processName = command.substr(10);
                trim(processName);
                if (processName.empty()) {
                    std::cout << "Command not recognized! Please provide a process name." << std::endl;
                }
                else {
                    if (console.isProcessFinished(processName)) {
                        std::cout << "Process " << processName << " not found." << std::endl;
                    }
                    else {
                        console.switchScreen("PROCESS_SCREEN_" + processName);
                    }
                }
            }

        }
        else if (command.substr(0, 9) == "scheduler") {
            if (command.substr(10) == "test") {
                console.startSchedulerTest();
            }
            else if (command.substr(10) == "stop") {
                console.stopSchedulerTest();
            }
            else {
                std::cout << "Invalid command.Please try again." << std::endl;
            }
        }
        else if (command == "report-util") {
            console.getScheduler().saveReport();

        }
        else if (command == "help") {
            std::cout << "\nCommands:" << std::endl;
            std::cout << "clear/cls - Clear the screen" << std::endl;
            std::cout << "marquee - Switch to marquee screen" << std::endl;
            std::cout << "screen -ls - List all screens" << std::endl;
            std::cout << "screen -s [processName] - Create a new process screen" << std::endl;
            std::cout << "scheduler-test - Start the scheduler test" << std::endl;
            std::cout << "scheduler-stop - Stop the scheduler test" << std::endl;
            std::cout << "report-util - Save the report" << std::endl;
            std::cout << "exit - Exit the program" << std::endl;
        }

        else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }

    }
    else {
        std::cout << "You must initialize the program first." << std::endl;
    }
}

void MainMenuScreen::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
        }));
}

// Function to trim whitespace from the end (in place)
void MainMenuScreen::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// Function to trim whitespace from both ends (in place)
void MainMenuScreen::trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}