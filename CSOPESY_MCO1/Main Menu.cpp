#include <iostream>
#include "Main Menu.h"
#include"Console.h"

extern Console console;
MainMenu::MainMenu() 
	:Console("Main_Menu") {}
	MainMenu::~MainMenu() {}

	void MainMenu::execute() {
		display();
		process();
	}
	void MainMenu::display() {
		header();
	}

	void MainMenu::process() {
		string command;
		while (true) {
			std::cout << "> ";
			getline(cin, command);
			commands(command);
			std::cout << endl;
		}
	}

