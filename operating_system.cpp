#include <iostream>
#include "operating_system.h"
#include "process.h"
#include "io.h"

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
            std::cout << p.name << " - executing in Q0 at " << counter << std::endl;
            p.burstLeft--;
            p.queueTime++;
            if (p.done())
            {
                std::cout << p.name << " - is done at " << counter << std::endl;
                if (p.numberOfIO > 0)
                {
                    std::cout << p.name << " - will enter IO at " << counter << std::endl;
                    this->io.appendProcess(p, counter);
                }
                this->q0.pop();
            }
            else
            {
                if (p.queueTime == q0.quantum)
                {
                    std::cout << p.name << " - preempted to Q1 because of quantum at " << counter << std::endl;
                    p.queueTime = -1;
                    q1.push(p);
                    q0.pop();
                }
            }
        }

        else if (!this->q1.isEmpty())
        {
            Process &p = q1.q.front();
            std::cout << p.name << " - executing in Q1 at " << counter << std::endl;
            p.burstLeft--;
            p.queueTime = -1;
            if (p.done())
            {
                std::cout << p.name << " - is done at " << counter << std::endl;
                if (p.numberOfIO > 0)
                {

                    std::cout << p.name << " - will enter IO at " << counter << std::endl;
                    this->io.appendProcess(p, counter);
                }
                this->q1.q.pop();
            }
        }

        if (!this->io.line.empty() && counter == io.line.front().whenToLeaveIO)
        {
            Process &p = this->io.line.front();
            std::cout << p.name << " - leaving I/O at " << counter << std::endl;
            p.whenToLeaveIO = -1;
            q0.q.push(p);
            this->io.line.pop();
        }

        std::queue<Process> toRemove = this->q1.removeOldProcesses();

        while (!toRemove.empty())
        {
            Process p = toRemove.front();
            std::cout << "Removing " << p.name << " from Q1 at " << counter << std::endl;
            q0.q.push(p);
            toRemove.pop();
        }

        this->counter++;
    }
}

OperatingSystem::OperatingSystem(IO io)
{
    this->io = io;
}
