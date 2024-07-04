#pragma once
#include <string>

using namespace std;

class ConsoleName {
public:
    ConsoleName(string name);
    virtual ~ConsoleName();
    string getName();
    virtual void execute();
    virtual void display();
    virtual void process();

private:
    std::string name;
};
