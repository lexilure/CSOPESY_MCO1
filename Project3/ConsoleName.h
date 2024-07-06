#pragma once
#pragma once
#include <string>

using namespace std;

class ConsoleName
{
public: 
	ConsoleName(string name);
	~ConsoleName(); 

	string getName(); 

	virtual void onExecute() = 0; 
	virtual void display() = 0; 
	virtual void process() = 0; 

private:
	std::string name; 
};
