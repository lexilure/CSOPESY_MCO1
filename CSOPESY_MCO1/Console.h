#pragma once
#include <string>

using namespace std;

class Console {
public:
	Console(string name);
	~Console();
	string getName();
	virtual void execute() = 0;
	virtual void display() = 0;
	virtual void process() = 0;

private:
		std::string name;

};