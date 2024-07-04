#include <iostream>
#include "MainMenu.h"
#include"ConsoleName.h"

extern ConsoleName Mainmenu;
MainMenu::MainMenu() 
	:ConsoleName("Main_Menu") {}
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

