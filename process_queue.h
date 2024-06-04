#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include <queue>
#include "process.h"
#include "io.h"

const int STEP = 1;

class ProcessQueue
{
public:
    std::queue<Process> q;
    ProcessQueue();
    void appendProcess(Process process);
    bool isEmpty();
};

class RoundRobinQueue : public ProcessQueue
{

public:
    RoundRobinQueue();
    RoundRobinQueue(int quantum);
    bool mustPreempt();
    void preempt(std::queue<Process> &q1);
    int quantum;

private:
};

class FCFSQueue : public ProcessQueue
{
public:
    FCFSQueue();
    FCFSQueue(int maxTime);
    int maxTime;

private:
};

#endif