#include "../headers/scheduler.h"
#include "../headers/logEvent.h"
#include "../headers/queue.h"
#include <condition_variable>
#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

extern std::ofstream logFile;
extern Queue inputQueue;
extern Queue readyQueue;
extern std::mutex inputQueueMutex;
extern std::mutex readyQueueMutex;
extern std::condition_variable readyQueueCV;
extern std::atomic<bool> stopAll;
extern int miss_cnt, expire_cnt;

void Scheduler::schedule(){
  while(!stopAll){
    std::vector<Process> tempProcesses;
    {
      std::lock_guard<std::mutex> lock(inputQueueMutex);
      while(!inputQueue.isEmpty()){
        tempProcesses.push_back(inputQueue.dequeue());
      }
    }
	double currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                          std::chrono::steady_clock::now().time_since_epoch()).count();

        std::vector<Process> validProcesses;
        for (auto &p : tempProcesses) {
            if (p.getEndDeadline() < currentTime) {
                logEvent("missed", -1, p);
                expire_cnt++;
                miss_cnt++;
            } else {
                validProcesses.push_back(p);
            }
        }
    std::sort(validProcesses.begin(), validProcesses.end(), [](const Process &a, const Process &b) {
    double priorityA = (a.getScore() / (a.getEndDeadline() + 1)) - (a.getStartDeadline() * 0.1);
    double priorityB = (b.getScore() / (b.getEndDeadline() + 1)) - (b.getStartDeadline() * 0.1);
    return priorityA > priorityB;
	});


    {
      std::lock_guard<std::mutex> lock(readyQueueMutex);
      std::vector<Process> toRequeue;

      for (auto &p : validProcesses) {
        if (!readyQueue.isFull()) {
          readyQueue.enqueue(p);
        } else {
		  logEvent("missed", -1, p);
          miss_cnt++;
          Process weakest = readyQueue.back();
          double weakestPriority = weakest.getScore() / (weakest.getEndDeadline() + 1);
          double newPriority = p.getScore() / (p.getEndDeadline() + 1);

          if (weakestPriority < newPriority) {
            readyQueue.dequeue();
            readyQueue.enqueue(p);
            toRequeue.push_back(weakest);
          }else{ toRequeue.push_back(p); }
        }
      }
      std::lock_guard<std::mutex> inputLock(inputQueueMutex);
            for (auto &p : toRequeue) {
                inputQueue.enqueue(p);
                logEvent("move back", -1, p);
            }
    }
    readyQueueCV.notify_all();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}