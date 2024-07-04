
#include "Configuration.h"
#include "MainConsole.h"
#include <iostream>
#include <random>

MainConsole::MainConsole() : processID(0)
{
    initializeConsoles();
}

MainConsole::~MainConsole() {}

void MainConsole::run()
{
    if (currentConsole)
    {
        currentConsole->execute();
    }
    else
    {
        std::cerr << "No console to run." << std::endl;
    }
}

void MainConsole::switchScreen(const std::string& consoleName)
{
    auto it = consoles.find(consoleName);
    if (it != consoles.end())
    {
        previousConsole = currentConsole;
        currentConsole = it->second;
    }
    else
    {
        std::cerr << "Console not found: " << consoleName << std::endl;
    }
}

bool MainConsole::isLaunched() const{
	return config.configIsLaunched();
}

void MainConsole::setLaunched() {
	if (config.launcher() ) {
		std::cout << "Initialization successful..." << std::endl;
	}
}

Configuration& MainConsole::getConfiguration()
{
    return config;
}

const std::unordered_map<std::string, std::shared_ptr<ConsoleName>>& MainConsole::getConsoles() const
{
    return consoles;
}

void MainConsole::addConsole(const std::shared_ptr<ConsoleName>& console)
{
    if (console)
    {
        consoles[console->getName()] = console;
    }
}

void MainConsole::returnToPreviousScreen()
{
    if (previousConsole)
    {
        currentConsole = previousConsole;
        previousConsole.reset();
    }
}


void MainConsole::createProcessScreen(const std::string& processName)
{
    std::string screenName = processName + "_" + std::to_string(processID++);
    auto newConsole = std::make_shared<ConsoleName>(screenName);
    addConsole(newConsole);
    switchScreen(screenName);
}

void MainConsole::initializeConsoles()
{
    // Initialize your default consoles here
}

int MainConsole::getRandomInstruction()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    return dist(gen);
}
