#include "ProcessName.h"

ProcessName::ProcessName(std::string name, int id, int numInstructions)
    : processName(name), id(id), currentInstruction(0), totalInstructions(numInstructions), finished(false) {}

std::string ProcessName::getName() const {
    return processName;
}

int ProcessName::getID() const {
    return id;
}

int ProcessName::getCurrentInstruction() const {
    return currentInstruction;
}

int ProcessName::getTotalInstructions() const {
    return totalInstructions;
}

bool ProcessName::isFinished() const {
    return finished;
}

void ProcessName::execute() {
    if (currentInstruction < totalInstructions) {
        currentInstruction++;
    }
    else {
        finished = true;
    }
}
