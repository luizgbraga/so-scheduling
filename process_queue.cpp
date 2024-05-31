#include "process_queue.h"

ProcessQueue::ProcessQueue()
{
    this->q = std::queue<Process>();
    this->maxTime = -1;
}

void ProcessQueue::setMaxTime(int maxTime)
{
    this->maxTime = maxTime;
}

void ProcessQueue::appendProcess(Process process)
{
    this->q.push(process);
}

bool ProcessQueue::isEmpty()
{
    return this->q.empty();
}

Process ProcessQueue::run(IO &io)
{
    Process p = this->q.front();
    p.burstLeft -= STEP;

    std::queue<Process> aux = std::queue<Process>();
    aux.push(p);
    this->q.pop();
    while (!this->q.empty())
    {
        Process p = this->q.front();
        this->q.pop();
        aux.push(p);
    }

    while (!aux.empty())
    {
        Process p = aux.front();
        aux.pop();
        this->q.push(p);
    }

    if (p.burst == 0)
    {
        this->q.pop();
    }

    if (p.burst == 0 && p.numberOfIO > 0)
    {
        p.numberOfIO--;
        io.line.push(p);
    }

    return p;
}

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

FCFSQueue::FCFSQueue()
{
    // Implementation of constructor
}
