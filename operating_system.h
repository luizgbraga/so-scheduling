#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include <vector>
#include "process_queue.h"

class OperatingSystem
{
    int currentTime = 0;
    IO io;

public:
    static OperatingSystem init(IO io);
    RoundRobinQueue q0;
    FCFSQueue q1;
    void askForProccessesInput();
    bool allEmpty();
    void execute();

private:
    OperatingSystem(IO io);
};

#endif
