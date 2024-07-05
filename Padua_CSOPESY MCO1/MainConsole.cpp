#include "MainConsole.h"
#include "ConsoleName.h"
#include "Configuration.h"
#include "Scheduler.h"
#include "Process.h"
#include <iostream>
#include <random>

MainConsole::MainConsole() {
    launchScreens();
}

MainConsole::~MainConsole() {}

void MainConsole::launchScreens() {
    addConsole(std::make_shared<ConsoleName>());
    // Add more consoles as needed
    currentConsole = consoles["MainMenu"]; // Assuming "DefaultConsole" is the default console name
}

void MainConsole::run() {
    if (currentConsole) {
        currentConsole->execute();
    }
}

void MainConsole::switchScreen(const std::string& consoleName) {
    auto it = consoles.find(consoleName);
    if (it != consoles.end()) {
        previousConsole = currentConsole;
        currentConsole = it->second;
        system("cls");
        currentConsole->execute();
    }
    else {
        std::cerr << "Console " << consoleName << " not found." << std::endl;
    }
}

bool MainConsole::isLaunched() const {
    return config.configIsLaunched();
}

void MainConsole::setLaunched() {
    if (config.launcher() && scheduler.initialize(&config)) {
        std::cout << "Initialization successful..." << std::endl;
    }
}

Configuration& MainConsole::getConfiguration() {
    return config;
}

const std::unordered_map<std::string, std::shared_ptr<ConsoleName>>& MainConsole::getConsoles() const {
    return consoles;
}

void MainConsole::addConsole(const std::shared_ptr<ConsoleName>& console) {
    consoles[console->getName()] = console;
}

void MainConsole::returnToPreviousScreen() {
    if (previousConsole) {
        currentConsole = previousConsole;
        previousConsole = nullptr;
        system("cls");
        currentConsole->execute();
    }
    else {
        std::cerr << "No previous screen to return to." << std::endl;
    }
}

Scheduler& MainConsole::getScheduler() {
    return scheduler;
}

void MainConsole::createProcessScreen(const std::string& processName) {
    processID++;

    // Create new process
    ProcessName newProcess(processName, processID, getRandomInstruction());
    scheduler.addProcess(newProcess);

    // Create new process screen
    auto processScreen = std::make_shared<ProcessScreen>(newProcess);

    // Add process screen to main console
    addConsole(processScreen);

    // Switch to process screen
    switchScreen(processScreen->getName());
}

int MainConsole::getRandomInstruction() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(config.getMinIns(), config.getMaxIns());

    return distr(gen);
}
