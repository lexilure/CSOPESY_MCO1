#include "ConsoleName.h"
#include <iostream>

ConsoleName::ConsoleName(string name) : name(name) {
}

ConsoleName::~ConsoleName() {
}

string ConsoleName::getName() {
    return this->name;
}

void ConsoleName::execute() {
    cout << "Executing: " << getName() << endl;
}

void ConsoleName::display() {
    cout << "Displaying: " << getName() << endl;
}

void ConsoleName::process() {
    cout << "Processing: " << getName() << endl;
}
