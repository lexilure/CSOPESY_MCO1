#include "Console.h"
#include "MainMenuScreen.h"
#include "MarqueeScreen.h"
#include "Configuration.h"
#include "Scheduler.h"
#include "Process.h"
#include "ProcessScreen.h"

#include <random>

Console::Console() {
	auto MAIN_MENU = std::make_shared<MainMenuScreen>();
	consoles[MAIN_MENU->getName()] = MAIN_MENU;

	auto MARQUEE_SCREEN = std::make_shared<MarqueeScreen>();
	consoles[MARQUEE_SCREEN->getName()] = MARQUEE_SCREEN;

	currentConsole = MAIN_MENU;
}

Console::~Console()
{
}

void Console::run()
{
	if (currentConsole) {
		currentConsole->onExecute();
	}
}

void Console::switchScreen(const std::string consoleName) {
	if (consoleName.substr(0, 15) == "PROCESS_SCREEN_") {
		std::string processName = consoleName.substr(15);
		std::shared_ptr<Process> process = scheduler.getProcessByName(processName);

		if (process) {
			if (!process->isFinished()) {
				previousConsole = currentConsole;
				currentConsole = consoles[consoleName];
				system("cls");
				currentConsole->onExecute();
			}
			else {
				std::cerr << "Process " << processName << " has already finished." << std::endl;
			}
		}
		else {
			std::cerr << "Process " << processName << " not found." << std::endl;
		}
	}
	else {
		if (consoles.find(consoleName) != consoles.end()) {
			previousConsole = currentConsole;
			currentConsole = consoles[consoleName];
			system("cls");
			currentConsole->onExecute();
		}
		else {
			std::cerr << "Console " << consoleName << " not found." << std::endl;
		}
	}
}

bool Console::isInitialized() {
	return config.isInitialized();
}

void Console::setInitialized() {
	if (config.initialize() && scheduler.initialize(&config)) {
		std::cout << "Initialization successful..." << std::endl;
		std::thread schedulerThread(&Scheduler::run, &scheduler);
		schedulerThread.detach();
	}
}

Configuration& Console::getConfiguration() {
	return config;
}

const std::unordered_map<std::string, std::shared_ptr<ConsoleName>>& Console::getConsoles() const {
	return consoles;
}

void Console::addConsole(std::shared_ptr<ConsoleName> console) {
	consoles[console->getName()] = console;
}

void Console::returnToPreviousScreen() {
	if (previousConsole) {
		currentConsole = previousConsole;
		previousConsole = nullptr;
		system("cls");
		currentConsole->onExecute();
	}
	else {
		std::cerr << "No previous screen to return to." << std::endl;
	}
}

Scheduler& Console::getScheduler() {
	return scheduler;
}


void Console::createProcessScreen(const std::string processName) {
	processID++;

	// Create new process
	Process newProcess(processName, processID, getRandomInstruction());

	std::shared_ptr<Process> processPointer = scheduler.addProcess(newProcess);

	// Create new process screen
	auto processScreen = std::make_shared<ProcessScreen>(processPointer);

	// Add process screen to console manager
	addConsole(processScreen);

	// Switch to process screen
	switchScreen(processScreen->getName());
}

void Console::createProcess(const std::string processName) {
	processID++;

	// Create new process
	Process newProcess(processName, processID, getRandomInstruction());

	std::shared_ptr<Process> processPointer = scheduler.addProcess(newProcess);

	// Create new process screen
	auto processScreen = std::make_shared<ProcessScreen>(processPointer);

	// Add process screen to console manager
	addConsole(processScreen);
}

int Console::getRandomInstruction() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(config.getMinInstructions(), config.getMaxInstructions());

	return distr(gen);
}

void Console::startSchedulerTest() {
	std::lock_guard<std::mutex> lock(mtx);
	if (!schedulerTest) {
		schedulerTest = true;
		testThread = std::thread(&Console::schedulerTestLoop, this);
	}
}

void Console::stopSchedulerTest() {
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (schedulerTest) {
			schedulerTest = false;
		}
	}
	if (testThread.joinable()) {
		testThread.join();  // Ensure the thread is properly joined
	}
}

void Console::schedulerTestLoop() {
	while (schedulerTest) {
		createProcess("process_" + std::to_string(processID));
		std::this_thread::sleep_for(std::chrono::duration<double>(config.getBatchProcessFrequency()));
	}
}

void Console::displayStatus() {
	scheduler.displayStatus();
}

bool Console::ifProcessExists(std::string name) {
	bool flag;
	if (scheduler.getProcessByName(name) == nullptr) return false;
	return true;
}
bool Console::isProcessFinished(std::string name) {
	if (ifProcessExists(name)) {
		std::shared_ptr<Process> foundProcess = scheduler.getProcessByName(name);
		return foundProcess->isFinished();
	}
	return false;
}