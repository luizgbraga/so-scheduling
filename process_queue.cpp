#include "process_queue.h"

ProcessQueue::ProcessQueue()
{
    this->q = std::queue<Process>();
}

void ProcessQueue::appendProcess(Process process)
{
    this->q.push(process);
}

bool ProcessQueue::isEmpty()
{
    return this->q.empty();
}

void ProcessQueue::push(Process process)
{
    this->q.push(process);
}

Process ProcessQueue::pop()
{
    Process p = this->q.front();
    this->q.pop();
    return p;
}

RoundRobinQueue::RoundRobinQueue(){};

RoundRobinQueue::RoundRobinQueue(int quantum)
{
    this->quantum = quantum;
}

bool RoundRobinQueue::mustPreempt()
{
    return !this->isEmpty() and this->q.front().executingTime() >= this->quantum;
}

void RoundRobinQueue::preempt(std::queue<Process> &q1)
{
    Process p = this->q.front();
    this->q.pop();
    q1.push(p);
}

FCFSQueue::FCFSQueue(){};

FCFSQueue::FCFSQueue(int maxTime)
{
    this->maxTime = maxTime;
}

std::queue<Process> FCFSQueue::removeOldProcesses()
{
    std::queue<Process> toRemove;
    std::queue<Process> toMantain;
    while (!this->q.empty())
    {
        Process p = this->q.front();
        p.queueTime++;
        if (p.queueTime == this->maxTime)
        {
            toRemove.push(p);
        }
        else
        {
            toMantain.push(p);
        }
        this->q.pop();
    }
    this->q = toMantain;
    return toRemove;
}