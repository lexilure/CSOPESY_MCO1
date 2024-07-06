#include "ConsoleName.h"

ConsoleName::ConsoleName(std::string name)
{
	this->name = name;
}

ConsoleName::~ConsoleName()
{
}

std::string ConsoleName::getName()
{
	return this->name;
}

