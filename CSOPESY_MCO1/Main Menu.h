#pragma once 
#include"Console.h"
class MainMenu : public Console {
public:
	MainMenu();
	~MainMenu();
	 void execute() override;
	 void display() override;
	 void process() override;

private:
	void header();
	void commands(string command);

};