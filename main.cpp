#include <iostream>
#include "operating_system.h"

int main()
{
    OperatingSystem os = OperatingSystem::init(IO(5));
    os.q0 = RoundRobinQueue(10);
    os.q1 = FCFSQueue(30);

    os.askForProccessesInput();
    os.execute();

    return 0;
}
