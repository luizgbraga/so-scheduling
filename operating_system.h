#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include <vector>
#include "process_queue.h"

class OperatingSystem
{
    std::vector<Process> processes;
    std::vector<ProcessQueue> queues;
    IO io;

public:
    static OperatingSystem init(IO io);
    void askForProccessesInput();
    void appendQueue(ProcessQueue queue);
    void execute();

private:
    OperatingSystem(IO io);
    void appendProcess(Process process);
};

#endif
