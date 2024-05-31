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

        this->appendProcess(Process(name, burst, io));
    };
};

void OperatingSystem::appendQueue(ProcessQueue queue)
{
    this->queues.push_back(queue);
}

void OperatingSystem::execute()
{
    // execute
}

OperatingSystem::OperatingSystem(IO io)
{
    this->processes = std::vector<Process>();
    this->queues = std::vector<ProcessQueue>();
    this->io = io;
}

void OperatingSystem::appendProcess(Process process)
{
    this->processes.push_back(process);
}
