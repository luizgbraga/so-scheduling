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

    if (!this->q0.isEmpty() || !this->q1.isEmpty())
    {
        return false;
    }
    if (!this->io.line.empty())
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
            Process &p = q0.q.front();
            p.burstLeft--;
            p.queueTime++;
            if (p.executingTime() == p.burst)
            {
                if (p.numberOfIO > 0)
                {
                    p.numberOfIO--;
                    p.burstLeft = p.burst;
                    p.queueTime = 0;
                    p.ioTime = this->io.time + this->io.line.size() ? this->io.line.back().ioTime : currentTime;
                    this->io.line.push(p);
                }
                this->q0.q.pop();
            }
            else
            {
                if (p.queueTime == q0.quantum)
                {
                    p.queueTime = -1;
                    q1.q.push(p);
                    q0.q.pop();
                }
            }
        }

        if (!this->q1.isEmpty())
        {
            Process &p = q1.q.front();
            p.burstLeft--;
            p.queueTime++;
            if (p.executingTime() == p.burst)
            {
                if (p.numberOfIO > 0)
                {
                    p.numberOfIO--;
                    p.burstLeft = p.burst;
                    p.queueTime = 0;
                    p.ioTime = this->io.time + this->io.line.size() ? this->io.line.back().ioTime : currentTime;
                    this->io.line.push(p);
                }
                this->q1.q.pop();
            }
        }

        if (!this->io.line.empty() && currentTime == io.line.front().ioTime)
        {
            Process p = this->io.line.front();
            p.ioTime = -1;
            q0.q.push(p);
            this->io.line.pop();
        }

        //ver se algum ta com tempo lim de q1
        this->currentTime++;
    }
}

OperatingSystem::OperatingSystem(IO io)
{
    this->io = io;
}
