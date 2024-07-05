#include <iostream>

#include "Process.h"
#include "MainConsole.h"

extern MainConsole mainConsole;

Process::Process(ProcessName myProcess)
    : ConsoleName("PROCESS_SCREEN_" + myProcess.getName()), thisProcess(myProcess) {
}

void Process::execute() {
    display();
    process();
}

void Process::display() {
    displayHeader();
}

void Process::process() {
    string command;
    bool running = true;

    while (running) {
        std::cout << "> ";
        getline(cin, command);
        running = handleCommand(command);
        std::cout << endl;
    }
}

void Process::displayHeader() {
    // Displays process name and ID
    std::cout << "Process: " << thisProcess.getName() << endl;
    std::cout << "ID: " << thisProcess.getID() << endl << endl;

    // Prints finished if process is done else print current line and total lines
    if (!thisProcess.isFinished()) {
        std::cout << "Current instruction line: " << thisProcess.getCurrentInstruction() << endl;
        std::cout << "Lines of code: " << thisProcess.getTotalInstructions() << endl << endl;
    }
    else {
        std::cout << "Finished!" << endl;
    }
}

bool Process::handleCommand(string command) {
    if (command == "exit") {
        mainConsole.returnToPreviousScreen();
        return false;
    }
    else if (command == "process-smi") {
        execute();
        return true;
    }
    else {
        std::cout << "Invalid command. Please try again." << endl;
        return true;
    }
}


