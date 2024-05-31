#include "io.h"

const int STEP = 1;

IO::IO()
{
}

IO::IO(int time)
{
    this->line = std::queue<Process>();
    this->timeLeft = time;
    this->time = time;
}

void IO::checkProcessReady(std::queue<Process> &q0)
{
    if (this->line.empty())
    {
        return;
    }
    if (this->timeLeft == 0)
    {
        Process first = this->line.front();
        this->line.pop();
        this->timeLeft = this->time;
        first.burstLeft = first.burst;
        q0.push(first);
    }
}

void IO::decrementTime()
{
    if (!this->line.empty())
    {
        this->time -= STEP;
    }
}
