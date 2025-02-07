#include "../headers/cpu.h"
#include <mutex>
#include <iostream>
#include "../headers/logEvent.h"
#include "../headers/queue.h"

using namespace std;

extern std::mutex readyQueueMutex;
extern Queue inputQueue;
extern Queue readyQueue;
extern std::condition_variable readyQueueCV;
extern int total_score, miss_cnt, expire_cnt;
extern std::ofstream logFile;

CPU::CPU(int id){
    this->id = id;
    this->stopFlag = false;
    this->isBusy = false;
}

void CPU::executeProcess(Process p) {
    isBusy = true;
    double currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::steady_clock::now().time_since_epoch()).count();
    while (currentTime < p.getArrivalTime()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                          std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    if (currentTime > p.getStartDeadline()) {
        miss_cnt++;
        expire_cnt ++;
        logEvent("missed", -1, p);

    } else {
        p.setCPU(this->id);
      	total_score += p.getScore();
        calculateWaitingTime(p, currentTime);
        logEvent("executing", this->id, p);
        std::this_thread::sleep_for(std::chrono::seconds((int)p.getExecutionTime()));
        logEvent("finished", this->id, p);
    }

    isBusy = false;
}
void CPU::run() {
    while (!stopFlag) {
        Process p(0,0);
        {
            std::unique_lock<std::mutex> lock(readyQueueMutex);
            readyQueueCV.wait(lock, [this] { return !readyQueue.isEmpty() || stopFlag; });
            if (stopFlag) {
              std::cout << "CPU " << id << " stopping due to stopFlag.\n";
              break;
            }

            p = readyQueue.dequeue();
            if (p.getPid() == -1) continue;
        }
        logEvent("picked", this->id, p);
        executeProcess(p);
    }
}


void CPU::start() { cpuThread = std::thread(&CPU::run, this); }

void CPU::stop() {
    stopFlag = true;
    readyQueueCV.notify_all();
    if (cpuThread.joinable()) {
        cpuThread.join();
    }
}
