#pragma once
#include <atomic>
#include <string>
#include <thread>

class Marquee
{
public:
    Marquee();
    ~Marquee();
    
    void start();
    void stop();

private:
    void animate();
    void checkInput();
    void gotoxy(int x, int y);

    std::atomic<bool> running; // Atomic flag to control the running state
    std::string userInput; // Variable to store user input
    std::thread animThread; // Thread for animation
    std::thread inputThread; // Thread for input checking
};
