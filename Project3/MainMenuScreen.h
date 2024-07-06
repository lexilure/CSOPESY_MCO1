#pragma once
#pragma once


#include "ConsoleName.h"

class MainMenuScreen : public ConsoleName
{
public:
	MainMenuScreen();
	~MainMenuScreen();

	void onExecute() override;
	void display() override;
	void process() override;

private:
	void displayHeader();
	void handleCommand(string command);
	void ltrim(std::string& s);
	void rtrim(std::string& s);
	void trim(std::string& s);
};
