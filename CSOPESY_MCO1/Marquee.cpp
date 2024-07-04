#include "Marquee.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

Marquee::Marquee() : running(true), userInput("")
{
}

Marquee::~Marquee()
{
    stop(); // Ensure threads are stopped and joined
}

void Marquee::start()
{
    animThread = std::thread(&Marquee::animate, this);
    inputThread = std::thread(&Marquee::checkInput, this);

    std::cout << "Press 'q' to quit." << std::endl;
    while (true)
    {
        if (_kbhit() && _getch() == 'q') // Check if the user pressed 'q'
        {
            running = false; // Stop the threads
            break;
        }
    }

    animThread.join(); // Wait for the animation thread to finish
    inputThread.join(); // Wait for the input thread to finish
}

void Marquee::stop()
{
    running = false;
    if (animThread.joinable())
    {
        animThread.join();
    }
    if (inputThread.joinable())
    {
        inputThread.join();
    }
}

void Marquee::animate()
{
    char arr[9];
    int x = 0;
    int y = 0;
    int ydirection = 1;  // Initial vertical direction (1: down, -1: up)
    int xdirection = 1;  // Initial horizontal direction (1: right, -1: left)

    strcpy_s(arr, sizeof(arr), "test");

    while (running) // Run the loop while the program is running
    {
        // Update position
        x += xdirection;
        y += ydirection;

        // Check for boundaries and change direction if needed
        if (x >= 72) xdirection = -1;
        if (x <= 0) xdirection = 1;
        if (y >= 24) ydirection = -1; // Adjust for console height
        if (y <= 0) ydirection = 1;

        // Clear the previous position by printing spaces
        gotoxy(x - xdirection, y - ydirection);
        std::cout << "    "; // Clear the length of the text

        // Move to the new position and print the text
        gotoxy(x, y);
        std::cout << arr;

        // Display user input prompt and clear the area
        gotoxy(0, 25);
        std::cout << "Enter command: " << userInput << "          ";
        gotoxy(0, 26);
        std::cout << "                                          "; // Clear the input line

        Sleep(100); // Add a delay to simulate animation speed
    }
}

void Marquee::checkInput()
{
    while (running) // Run the loop while the program is running
    {
        if (_kbhit()) // Check if a key has been pressed
        {
            char ch = _getch(); // Read the character (without echoing to the console)
            if (ch == '\r') // If Enter is pressed
            {
                if (!userInput.empty())
                {
                    gotoxy(0, 26); // Move to a fixed position to clear the input prompt
                    std::cout << "                                          "; // Clear the input line
                    gotoxy(0, 25); // Move back to the input line position
                    std::cout << "Input recognized: " << userInput << "          ";
                    userInput.clear(); // Clear the input string
                }
            }
            else if (ch == '\b') // If Backspace is pressed
            {
                if (!userInput.empty())
                {
                    userInput.pop_back();
                }
            }
            else
            {
                userInput += ch; // Append the character to the input string
            }

            // Update the console display for the user input
            gotoxy(0, 25);
            std::cout << "Enter command: " << userInput << "          ";
            gotoxy(0, 25 + userInput.size() + 15); // Move cursor back to correct position
        }
    }
}

void Marquee::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
