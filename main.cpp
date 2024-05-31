#include <iostream>
#include "operating_system.h"

int main()
{
    OperatingSystem os = OperatingSystem::init(IO(20));
    RoundRobinQueue rr = RoundRobinQueue(10);
    FCFSQueue fcfs = FCFSQueue();
    fcfs.setMaxTime(30);

    os.askForProccessesInput();
    os.appendQueue(rr);
    os.appendQueue(fcfs);

    os.execute();

    return 0;
}
