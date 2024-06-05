#include "io.h"

const int STEP = 1;

IO::IO()
{
}

IO::IO(int time)
{
    this->line = std::queue<Process>();
    this->time = time;
}

int IO::calculateWhenToLeave(int currentTime)
{
    if (this->line.size() > 0)
    {
        return this->time + this->line.back().whenToLeaveIO;
    }
    return this->time + currentTime;
}

void IO::appendProcess(Process &p)
{
    p.numberOfIO--;
    p.burstLeft = p.burst;
    p.queueTime = 0;
    p.whenToLeaveIO = this->calculateWhenToLeave(p.whenToLeaveIO);
    this->line.push(p);
}