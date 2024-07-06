

#include "ConsoleName.h"
#include "Configuration.h"
#include "Scheduler.h"
#include "Process.h"
#include <unordered_map>
#include <memory>

class MainConsole {
public:
    MainConsole();
    ~MainConsole();

    void run();
    void switchScreen(const std::string& consoleName);
    bool isLaunched() const;
    void setLaunched();
    Configuration & getConfiguration();
    const std::unordered_map<std::string, std::shared_ptr<ConsoleName>>& getConsoles() const;
    void addConsole(const std::shared_ptr<ConsoleName>& console);
    void returnToPreviousScreen();
    Scheduler& getScheduler();
    void createProcessScreen(const std::string& processName);
    int getRandomInstruction();

private:
    void launchScreens();

    std::unordered_map<std::string, std::shared_ptr<ConsoleName>> consoles;
    std::shared_ptr<ConsoleName> currentConsole;
    std::shared_ptr<ConsoleName> previousConsole;
    Configuration config;
    Scheduler scheduler;
    int processID = 0;
};


