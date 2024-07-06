#pragma once
#include "ConsoleName.h"
#include "ProcessName.h"
#include <iostream>
#include <vector>
#include <sstream>

class Process : public ConsoleName {
public:
	Process(ProcessName myProcess);


	void execute() override;
	void display() override;
	void process() override;

private:
	void displayHeader();
	bool handleCommand(string command);

	ProcessName thisProcess;
};