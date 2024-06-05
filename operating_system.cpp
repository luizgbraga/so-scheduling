#include <iostream>
#include "operating_system.h"

OperatingSystem OperatingSystem::init(IO io)
{
    return OperatingSystem(io);
}

void OperatingSystem::askForProccessesInput()
{
    int n;
    std::cout << "Number of processes:" << std::endl;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        int burst;
        int io;

        std::cout << "Burst: ";
        std::cin >> burst;

        std::cout << "Number of I/O: ";
        std::cin >> io;

        std::string name = "P" + std::to_string(i + 1);

        this->q0.appendProcess(Process(name, burst, io));
    };
};

bool OperatingSystem::allEmpty()
{

    if (!this->q0.isEmpty() || !this->q1.isEmpty() || !this->io.line.empty())
    {
        return false;
    }

    return true;
}

void OperatingSystem::execute()
{
    while (!this->allEmpty())
    {
        if (!this->q0.isEmpty())
        {
            Process &p = this->q0.q.front();
            p.burstLeft--;
            p.queueTime++;
            if (p.done())
            {
                if (p.numberOfIO > 0)
                {
                    this->io.appendProcess(p);
                }
                this->q0.pop();
            }
            else
            {
                if (p.queueTime == q0.quantum)
                {
                    p.queueTime = -1;
                    q1.push(p);
                    q0.pop();
                }
            }
        }

        else if (!this->q1.isEmpty())
        {
            Process &p = q1.q.front();
            p.burstLeft--;
            if (p.executingTime() == p.burst)
            {
                if (p.numberOfIO > 0)
                {
                    this->io.appendProcess(p);
                }
                this->q1.q.pop();
            }
        }

        if (!this->io.line.empty() && currentTime == io.line.front().whenToLeaveIO)
        {
            Process &p = this->io.line.front();
            p.whenToLeaveIO = -1;
            q0.q.push(p);
            this->io.line.pop();
        }

        std::queue<Process> toRemove = this->q1.removeOldProcesses();

        while (!toRemove.empty())
        {
            Process p = toRemove.front();
            q0.q.push(p);
            toRemove.pop();
        }

        this->currentTime++;
    }
}

OperatingSystem::OperatingSystem(IO io)
{
    this->io = io;
}
