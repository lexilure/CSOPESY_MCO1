#pragma once
#include "ConsoleName.h"
#include "MainConsole.h"

class MainMenu:public ConsoleName {
public:
	MainMenu();
	~MainMenu();
	void execute() override;
	void display() override;
	void process() override;


private:
	void menuHeader();
	void inputCommand(string command);
};
