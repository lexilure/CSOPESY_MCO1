#include "Scheduler.h"
#include <algorithm> // for std::sort
#include <chrono>    // for std::this_thread::sleep_for
#include <iostream>
#include <fstream>

Scheduler::Scheduler() : config(nullptr), running(false) {}

Scheduler::~Scheduler() {}

void Scheduler::addProcess(const std::string& processName, int processID, int instructions) {
    processes.push_back(std::make_shared<ProcessName>(processName, processID, instructions));
    readyQueue.push(processes.back());
}

std::shared_ptr<ProcessName> Scheduler::getProcessName(const std::string& name) {
    for (auto& process : processes) {
        if (process->getName() == name) {
            return process;
        }
    }
    return nullptr;
}

bool Scheduler::initialize(Configuration* newConfig) {
    try {
        config = newConfig;
        running = true;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing scheduler: " << e.what() << std::endl;
        return false;
    }
}

void Scheduler::run() {
    while (running) {
        if (config->getScheduler() == "fcfs") {
            scheduleFCFS();
        }
        else if (config->getScheduler() == "sjf") {
            scheduleSJF();
        }
        else if (config->getScheduler() == "rr") {
            scheduleRR();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(config->getDelayPerExec() * 1000));
    }
}

void Scheduler::stop() {
    running = false;
}

void Scheduler::displayStatus() const {
    std::cout << "Scheduler Status:\n";
    std::cout << "Current Scheduler Algorithm: " << config->getScheduler() << "\n";
    std::cout << "Processes in Ready Queue: " << readyQueue.size() << "\n";
    std::cout << "Processes in Execution:\n";
    for (const auto& process : processes) {
        if (!process->isFinished()) {
            std::cout << "  - " << process->getName() << "\n";
        }
    }
}

void Scheduler::saveReport() const {
    std::cout << "Saving report..." << std::endl;

    std::ofstream file("scheduler-report.txt");
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    file << "Scheduler Report\n";
    file << "Scheduler Algorithm: " << config->getScheduler() << "\n";
    file << "Processes:\n";
    for (const auto& process : processes) {
        file << "  - Name: " << process->getName() << ", Instructions: " << process->getTotalInstructions() << "\n";
    }

    std::cout << "Report saved to scheduler-report.txt" << std::endl;
}

void Scheduler::scheduleFCFS() {
    if (!readyQueue.empty()) {
        auto process = readyQueue.front();
        readyQueue.pop();
        std::cout << "Executing process (FCFS): " << process->getName() << "\n";
        process->execute();
    }
}

void Scheduler::scheduleSJF() {
    if (!readyQueue.empty()) {
        std::sort(processes.begin(), processes.end(), [](const std::shared_ptr<ProcessName>& a, const std::shared_ptr<ProcessName>& b) {
            return a->getTotalInstructions() < b->getTotalInstructions();
            });
        auto process = processes.front();
        processes.erase(processes.begin()); // Remove from the list for SJF scheduling
        std::cout << "Executing process (SJF): " << process->getName() << "\n";
        process->execute();
    }
}

void Scheduler::scheduleRR() {
    if (!readyQueue.empty()) {
        auto process = readyQueue.front();
        readyQueue.pop();
        std::cout << "Executing process (RR): " << process->getName() << " for " << config->getQuantumCycles() << " cycles\n";
        process->execute();
        if (!process->isFinished()) {
            readyQueue.push(process);
        }
    }
}
