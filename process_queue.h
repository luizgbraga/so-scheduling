#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include <queue>
#include "process.h"
#include "io.h"

const int STEP = 1;

class ProcessQueue
{
protected:
    std::queue<Process> q;
    int maxTime;
    int quantum;

public:
    ProcessQueue();
    void setMaxTime(int maxTime);
    void appendProcess(Process process);
    bool isEmpty();
    Process run(IO &io);
};

class RoundRobinQueue : public ProcessQueue
{

public:
    RoundRobinQueue(int quantum);
    bool mustPreempt();
    void preempt(std::queue<Process> &q1);
};

class FCFSQueue : public ProcessQueue
{
public:
    FCFSQueue();
};

#endif