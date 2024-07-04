

#include <string>

class Configuration {
public:
    Configuration();
    ~Configuration();

    bool initialize();
    void inputConfigFile();
    void printConfig();

    bool configIsLaunched() const;
    int getNumCPU() const;
    std::string getScheduler() const;
    int getQuantumCycles() const;
    bool isPreemptive() const;
    int getBatchProcessFreq() const;
    int getMinIns() const;
    int getMaxIns() const;
    int getDelayPerExec() const;

private:
    int numCPU;
    std::string scheduler;
    int quantumCycles;
    bool preemptive;
    int batchProcessFrequency;
    int minInstructions;
    int maxInstructions;
    int delayPerExec;
    bool launch;
};


