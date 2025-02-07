#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <mutex>

extern std::mutex inputQueueMutex;
extern std::mutex readyQueueMutex;

class Scheduler {
  public:
    void schedule();
};

#endif