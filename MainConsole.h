#pragma once
#include <memory>
#include <unordered_map>
#include <string>

#include "ConsoleName.h"
#include "Configuration.h"
#include "Scheduler.h"

class MainConsole
{
public:
    MainConsole();
    ~MainConsole();

    void run();
    void switchScreen(const std::string& consoleName);

    bool isLaunched() const;
    void setLaunched();
    Configuration& getConfiguration();

    const std::unordered_map<std::string, std::shared_ptr<ConsoleName>>& getConsoles() const;
    void addConsole(const std::shared_ptr<ConsoleName>& console);
    void returnToPreviousScreen();

    void createProcessScreen(const std::string& processName);

private:
    Configuration config;

    std::unordered_map<std::string, std::shared_ptr<ConsoleName>> consoles;
    std::shared_ptr<ConsoleName> previousConsole;
    std::shared_ptr<ConsoleName> currentConsole;

    int processID = 0;

    void initializeConsoles();
    int getRandomInstruction();
};
