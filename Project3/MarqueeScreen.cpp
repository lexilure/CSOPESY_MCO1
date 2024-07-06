#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <conio.h>
#include <algorithm>
#include <windows.h> // Include Windows specific header

#include "MarqueeScreen.h"
#include "Console.h"

extern Console console;

MarqueeScreen::MarqueeScreen()
    : ConsoleName("MARQUEE_SCREEN") {
}

MarqueeScreen::~MarqueeScreen() {
}

void MarqueeScreen::onExecute() {
    getConsoleSize();
    process();
}

void MarqueeScreen::display() {
}

void MarqueeScreen::process() {
    int x = (screenWidth - marqueeText.length()) / 2;
    int y = screenHeight / 2;
    int dx = 1;
    int dy = 1;
    int frameDelay = 1000 / refresh_rate; // Calculate delay in milliseconds based on refresh rate
    std::string marqueeText = userInput;
    WORD colors[] = { 0x0C, 0x0E, 0x0A, 0x0B, 0x0D, 0x0F }; // Array of colors
    int colorIndex = 0; // Start with the first color

    while (true) {
        clearConsole();
        displayHeader();
        displayFooter();
        drawOnBuffer(x, y, marqueeText, colors[colorIndex]); // Draw text with current color

        // Update position
        x += dx;
        y += dy;

        // Change color for next frame
        colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));

        // Check for collisions and change direction if necessary
        if (x <= 0 || x + marqueeText.length() >= screenWidth) {
            dx = -dx;
        }
        if (y <= 3 || y >= screenHeight - 3) {
            dy = -dy;
        }

        // Check for user input
        if (_kbhit()) { // Check if a key has been pressed
            char c = _getch(); // Get the character

            if (c == '\b') { // Handle backspace
                if (!userInput.empty()) {
                    userInput.pop_back();
                    marqueeText = userInput;
                }
            }
            else if (c == '\r') { // Handle enter key
                std::string userInputCopy = userInput;
                std::transform(userInputCopy.begin(), userInputCopy.end(), userInputCopy.begin(), ::tolower);

                if (userInputCopy == "exit") {
                    console.returnToPreviousScreen();
                    return;
                }
            }
            else {
                userInput += c;
                marqueeText = userInput;
            }
        }

        // Slow down the loop based on refresh rate
        std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay));

        // Polling delay (optional, if additional logic is needed at polling intervals)
        std::this_thread::sleep_for(std::chrono::milliseconds(polling_rate));
    }
}

void MarqueeScreen::getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else {
        screenWidth = 80;
        screenHeight = 25;
    }
}

void MarqueeScreen::drawOnBuffer(int x, int y, const std::string text, WORD attributes) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    DWORD written;
    std::wstring wideText = std::wstring(text.begin(), text.end()); // Convert to wide string
    WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), wideText.c_str(), static_cast<DWORD>(wideText.length()), coord, &written); // Write text
    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes, static_cast<DWORD>(text.length()), coord, &written); // Set text color
}

void MarqueeScreen::displayHeader() {
    drawOnBuffer(0, 1, "Displaying a Marquee console", 0x0F);
}

void MarqueeScreen::displayFooter() {
    drawOnBuffer(0, screenHeight - 1, "Type your text here: " + userInput, 0x0F);
}

void MarqueeScreen::clearConsole() {
    COORD topLeft = { 0, 0 };
    DWORD written;
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', screenWidth * screenHeight, topLeft, &written);
    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07, screenWidth * screenHeight, topLeft, &written);
}
