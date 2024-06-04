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
