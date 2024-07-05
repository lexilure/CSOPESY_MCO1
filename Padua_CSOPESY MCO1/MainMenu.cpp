#include "MainMenu.h"
#include"MainConsole.h"

using namespace std;
#include<iostream>
#include <string>

extern MainConsole mainConsole;

MainMenu::MainMenu() :ConsoleName("MainMenu") {}
MainMenu::~MainMenu() {
}

void  MainMenu::execute() {
	display();
	process();
}
void MainMenu::display() {
	menuHeader();
}

void MainMenu::process() {
    string command;
    while (true) {
        std::cout << "> ";
        getline(cin, command);
        inputCommand(command);
        std::cout << endl;
    }
}

void menuHeader() {
    cout << "_____  _____  ____  _____  ______  ______ _     __ \n";
    cout << "/ ____|/ ____|/ __ \\ | __ \\ | ____|/ ____ \\ \\   / / \n";
    cout << "| |    | (___ | |  | | |__) | |__ | (___   \\ \\_/ /  \n";
    cout << "| |     \\___ \\| |  | |  ___/|  __| \\___ \\   \\   / \n";
    cout << "| |____ ____) | |__| | |    | |____ ____) |  | | \n";
    cout << "\\_____ | _____/ \\____/|_| |______ | _____/  |_| \n";
    cout << "Welcome to the emulator!\n";
}


