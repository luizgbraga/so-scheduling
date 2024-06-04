#include "process.h"

Process::Process(std::string name, int burst, int numberOfIO)
{
    this->name = name;
    this->burst = burst;
    this->burstLeft = burst;
    this->numberOfIO = numberOfIO;
    this->timeToLeaveIO = -1;
    this->queueTime = 0;
}

int Process::executingTime()
{
    return this->burst - this->burstLeft;
}
