#ifndef IO_H
#define IO_H

#include <queue>
#include "process.h"

class IO
{
public:
    std::queue<Process> line;
    int time;

    IO();
    IO(int time);
};

#endif
