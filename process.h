// process.h
#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process
{
public:
    std::string name;
    int burst;
    int burstLeft;
    int numberOfIO;
    int whenToLeaveIO;
    int queueTime;

    Process(std::string name, int burst, int numberOfIO);
    int executingTime();
    bool done();
};

#endif
