#include "Configuration.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

Configuration::Configuration()
    : numCPU(0), quantumCycles(0), preemptive(false), batchProcessFrequency(0), minInstructions(0), maxInstructions(0), delayPerExec(0) {
}

Configuration::~Configuration() {};

    bool Configuration::launcher() {
        bool launch = false;
        try {
            inputConfigFile();
            printConfig();
            launch = true;

        }
        catch (const std::exception& e) {
            std::cerr << "Error initializing configuration: " << e.what() << std::endl;
            return launch;
        }
    }


    void Configuration::inputConfigFile() {
        std::ifstream configFile("config.txt");
        if (!configFile.is_open()) {
            throw std::runtime_error("Could not open config file");
        }

        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key;
            if (!(iss >> key)) {
                continue; // Skip empty lines
            }

            if (key == "num-cpu") {
                iss >> numCPU;
            }
            else if (key == "scheduler") {
                iss >> scheduler;
            }
            else if (key == "quantum-cycles") {
                iss >> quantumCycles;
            }
            else if (key == "preemptive") {
                int preemptiveFlag;
                iss >> preemptiveFlag;
                preemptive = (preemptiveFlag == 1);
            }
            else if (key == "batch-process-freq") {
                iss >> batchProcessFrequency;
            }
            else if (key == "min-ins") {
                iss >> minInstructions;
            }
            else if (key == "max-ins") {
                iss >> maxInstructions;
            }
            else if (key == "delay-per-exec") {
                iss >> delayPerExec;
            }
        }
        configFile.close();
    }

    void Configuration::printConfig() {
        std::cout << "--------------------------" << std::endl;
        std::cout << "Configuration Settings:" << std::endl;
        std::cout << "num-cpu: " << numCPU << std::endl;
        std::cout << "scheduler: " << scheduler << std::endl;
        std::cout << "quantum-cycles: " << quantumCycles << std::endl;
        std::cout << "preemptive: " << (preemptive ? "true" : "false") << std::endl;
        std::cout << "batch-process-freq: " << batchProcessFrequency << std::endl;
        std::cout << "min-ins: " << minInstructions << std::endl;
        std::cout << "max-ins: " << maxInstructions << std::endl;
        std::cout << "delay-per-exec: " << delayPerExec << std::endl;
        std::cout << "--------------------------" << std::endl;
    }

    bool Configuration::configIsLaunched() const { return launch; }

    int Configuration::getNumCPU() const { return numCPU; }

    std::string Configuration::getScheduler() const { return scheduler; }

    int Configuration::getQuantumCycles() const {
        return quantumCycles;
    }

    bool Configuration::isPreemptive() const {
        return preemptive;
    }

    int Configuration::getBatchProcessFreq() const {
        return batchProcessFrequency;
    }

    int Configuration::getMinIns() const {
        return minInstructions;
    }

    int Configuration::getMaxIns() const {
        return maxInstructions;
    }

    int Configuration::getDelayPerExec() const {
        return delayPerExec;
    }
