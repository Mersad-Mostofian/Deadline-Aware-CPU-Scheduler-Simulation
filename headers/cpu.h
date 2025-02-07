#include <thread>
#include <condition_variable>
#include "process.h"
#ifndef CPU_H
#define CPU_H

extern std::mutex readyQueueMutex;

class CPU {
  private:
    int id;
    std::thread cpuThread;
    bool isBusy;
    bool stopFlag;

  public:
    CPU(int id);
    void run();
    void executeProcess(Process P);
    void stop();
    void start();
};

#endif