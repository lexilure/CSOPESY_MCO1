#pragma once 
#include<string>
#include"ConsoleName.h"
class MainMenu : public ConsoleName {
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