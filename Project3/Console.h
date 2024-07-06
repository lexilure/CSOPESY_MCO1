#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <thread>


#include "ConsoleName.h"
#include "Configuration.h"
#include "Scheduler.h"
#include "ProcessScreen.h"

class Console
{

public:
	Console();
	~Console();

	void run(); // Function to run the console
	void switchScreen(std::string consoleName); // Function to switch the console)

	bool isInitialized(); // Function to check if the console is initialized
	void setInitialized(); // Function to set the console as initialized
	Configuration& getConfiguration(); // Function to get the configuration manager

	const std::unordered_map<std::string, std::shared_ptr<ConsoleName>>& getConsoles() const; // Function to get the consoles
	void addConsole(std::shared_ptr<ConsoleName> console); // Function to add a new console
	void returnToPreviousScreen(); // Function to return to the previous screen

	Scheduler& getScheduler(); // Function to get the scheduler
	void createProcessScreen(const std::string processName); // Function to create a process screen)
	void createProcess(const std::string processName); // Function to create a process screen)


	void startSchedulerTest();
	void stopSchedulerTest();
	void displayStatus();

	bool ifProcessExists(std::string name);
	bool isProcessFinished(std::string name);

private:
	Configuration config; // Configuration manager object
	Scheduler scheduler; // Scheduler object

	std::unordered_map<std::string, std::shared_ptr<ConsoleName>> consoles; // Map of consoles
	std::shared_ptr<ConsoleName> previousConsole; // Pointer to the previous console
	std::shared_ptr<ConsoleName> currentConsole; // Pointer to the current console

	int processID = 0; // Process ID Tracker
	int getRandomInstruction(); // Function to get a random number of instructions

	std::atomic<bool> schedulerTest{ false };
	std::thread testThread;
	std::mutex mtx;
	void schedulerTestLoop();
};
