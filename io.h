#ifndef IO_H
#define IO_H

#include <queue>
#include "process.h"

class IO
{
public:
    std::queue<Process> line;
    int timeLeft;
    int time;

    IO();
    IO(int time);
    void checkProcessReady(std::queue<Process> &q0);
    void decrementTime();
};

#endif
