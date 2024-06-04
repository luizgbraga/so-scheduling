#include "process.h"

Process::Process(std::string name, int burst, int numberOfIO)
{
    this->name = name;
    this->burst = burst;
    this->burstLeft = burst;
    this->numberOfIO = numberOfIO;
}

int Process::executingTime()
{
    return this->burst - this->burstLeft;
}
