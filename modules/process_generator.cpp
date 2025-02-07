#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <random>
#include <atomic>
#include <condition_variable>
#include "../headers/process.h"
#include "../headers/queue.h"
#include "../headers/logEvent.h"
#include "../headers/process_generator.h"


extern std::mutex mtx;
extern std::condition_variable cv;
extern std::mt19937 rng;
extern std::uniform_int_distribution<int> dist;
extern std::atomic<bool> stopAll;
extern int max_generatedProcesses;
extern std::ofstream logFile;

Process generateProcesses(int pid){
  auto now = std::chrono::steady_clock::now();
  auto duration = now.time_since_epoch();
  auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
  double t = seconds.count();

  Process p(pid, t);
  return p;
}

void process_generator(Queue &inputQueue){
  int generatedProcesses = 0;
  while(!stopAll && generatedProcesses < max_generatedProcesses){
    int pid = dist(rng);
    Process p = generateProcesses(pid);

    {
      std::lock_guard<std::mutex> lock(mtx);
      if (!inputQueue.isFull()) {
        inputQueue.enqueue(p);
        generatedProcesses++;
      } else {
        logEvent("skipping", p.getPid(), p);
      }
    }
    logEvent("created", p.getPid(), p);


    cv.notify_all();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

void requestProcessCreation(int pid, Queue &inputQueue){
    double arrivalTime = std::chrono::duration_cast<std::chrono::seconds>(
                        std::chrono::steady_clock::now().time_since_epoch()).count();
    std::lock_guard<std::mutex> lock(mtx);
    if (!inputQueue.isFull()) {
      inputQueue.enqueue(Process(pid, arrivalTime));
      cv.notify_all();
    } else {
      std::cout << "Queue is full, process with PID " << pid << std::endl;
    }
}

