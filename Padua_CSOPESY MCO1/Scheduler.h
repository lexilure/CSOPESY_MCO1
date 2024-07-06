#pragma once

#include <vector>
#include <memory>
#include <queue>

#include "ProcessName.h"
#include "Configuration.h"

class Scheduler {
public:
    Scheduler();
    ~Scheduler();

    void addProcess(const std::string& processName, int processID, int instructions);
    std::shared_ptr<ProcessName> getProcessName(const std::string& name);

    bool initialize(Configuration* newConfig);
    void run();
    void stop();
    void displayStatus() const;
    void saveReport() const;

private:
    Configuration* config;

    std::vector<std::shared_ptr<ProcessName>> processes; // Use ProcessName instead of Process
    std::queue<std::shared_ptr<ProcessName>> readyQueue; // Use ProcessName instead of Process

    void scheduleFCFS();
    void scheduleSJF();
    void scheduleRR();

    bool running;
};
