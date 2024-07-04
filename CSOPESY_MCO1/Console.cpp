#include "Console.h"

Console::Console(std::string name)
{
	this->name = name;
}

Console::~Console()
{
}

std::string Console::getName()
{
	return this->name;
}