#include <iostream>

#include "MainMenuScreen.h"
#include "ConsoleManager.h"

extern ConsoleManager consoleManager;

MainMenuScreen::MainMenuScreen()
	: AConsole("MAIN_MENU"){

}

MainMenuScreen::~MainMenuScreen(){

}

void MainMenuScreen::onExecute(){
	display(); 
	process();
}

void MainMenuScreen::display(){
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

void MainMenuScreen::displayHeader(){
    cout << "_____  _____  ____  _____  ______  ______ _     __ \n";
    cout << "/ ____|/ ____|/ __ \\ | __ \\ | ____|/ ____ \\ \\   / / \n";
    cout << "| |    | (___ | |  | | |__) | |__ | (___   \\ \\_/ /  \n";
    cout << "| |     \\___ \\| |  | |  ___/|  __| \\___ \\   \\   / \n";
    cout << "| |____ ____) | |__| | |    | |____ ____) |  | | \n";
    cout << "\\_____ | _____/ \\____/|_| |______ | _____/  |_| \n";
    cout << "Welcome to the emulator!\n";
}

void MainMenuScreen::handleCommand(string command) {
    if (command == "exit") {
        std::cout << "Exiting the program..." << std::endl;
        exit(0);

    } else if (command == "initialize" && !consoleManager.isInitialized()) {
        consoleManager.setInitialized();

	} else if (consoleManager.isInitialized()) {
        if (command == "clear" || command == "cls") {
            system("cls");

        } else if (command == "marquee") {
            consoleManager.switchScreen("MARQUEE_SCREEN");

        } else if (command.substr(0,6) == "screen") {
            if (command == "screen -ls") {
                consoleManager.displayStatus();
            }

            else if (command.substr(0,9) == "screen -s") { 
                std::string processName = command.substr(10);
                trim(processName);
                if (processName.empty()){
                    std::cout << "Command not recognized! Please provide a process name." << std::endl;
                }
                else {
                    if (!consoleManager.ifProcessExists(processName)) {
                        consoleManager.createProcessScreen(processName);
                    }
                    else {
                        std::cout << "Process already exists or has existed. Please provide a differen name." << std::endl;
                    }
                   
                }
            }

            else if (command.substr(0,9) == "screen -r") {
                std::string processName = command.substr(10);
                trim(processName);
                if (processName.empty()) {
                    std::cout << "Command not recognized! Please provide a process name." << std::endl;
                }
                else {
                    if (consoleManager.isProcessFinished(processName)) {
                        std::cout << "Process " << processName << " not found." << std::endl;
                    }
                    else {
                        consoleManager.switchScreen("PROCESS_SCREEN_" + processName);
                    }
                }
            }

        } else if (command.substr(0, 9) == "scheduler") {
            if (command.substr(10) == "test") {
                consoleManager.startSchedulerTest();
            }
            else if (command.substr(10) == "stop") {
                consoleManager.stopSchedulerTest();
            } else {
                std::cout << "Invalid command.Please try again." << std::endl;
            }
        } else if (command == "report-util") {
            consoleManager.getScheduler().saveReport();

		} else if (command == "help") {
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

    } else {
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