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

    if (this->quantum) {} 
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
