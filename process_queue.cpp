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

Process ProcessQueue::run(IO &io, ProcessQueue &nextQueue)
{
    Process p = this->q.front();
    p.burstLeft -= STEP;
    p.queueTime++;

    if (p.executingTime() == p.burst)
    {
        if (p.numberOfIO != 0)
        {
            p.numberOfIO--;
            p.burstLeft = p.burst;
            p.queueTime = 0;
            p.ioTime = io.time + io.line.size() ? io.line.back().ioTime : 1923;
            io.line.push(p);
        }
        this->q.pop();
        return p;
    }

    if (this->quantum)
    {
        p.queueTime = 0;
        nextQueue.q.push(p);
        this->q.pop();
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
