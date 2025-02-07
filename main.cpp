#include <iostream>
#include<bits/stdc++.h>
#include <vector>
#include <random>
#include <atomic>
#include <fstream>
#include "./headers/logEvent.h"
#include "./headers/cpu.h"
#include "./headers/scheduler.h"
#include "./headers/queue.h"
#include "./headers/process_generator.h"


std::ofstream logFile(getTimestamp());
int max_generatedProcesses = 0;
Queue inputQueue(100);
Queue readyQueue(20);
int total_score = 0;
int miss_cnt = 0;
int total_waiting_time = 0;
int expire_cnt = 0;

std::mutex inputQueueMutex, readyQueueMutex;
std::condition_variable readyQueueCV;
std::mutex mtx;
std::condition_variable cv;
std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(1, 1000000);
std::atomic<bool> stopAll(false);


void startProcessGenerator() {
    process_generator(inputQueue);
}

void startScheduler() {
  Scheduler scheduler;
  while(!stopAll) {
    scheduler.schedule();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

void startCPUs(std::vector<CPU> &cpus) {
  for (auto &cpu : cpus) {
    cpu.start();
  }
}



int main() {
  logFile << "time, event, cpu_id, process_id, execution_time, start_deadline, end_deadline, total_waiting_time, score,count_of_expire, count of misses, total_score\n";
  int numCPUs = 0;
  std::cout << "Please Enter number of CPUs: ";
  std::cin >> numCPUs;
  std::cout << "Please Enter number of Processes: ";
  std::cin >> max_generatedProcesses;

  std::vector<CPU> cpus;
  for (int i = 0; i < numCPUs; i++) {
    cpus.emplace_back(i);
  }

  std::thread processGeneratorThread(startProcessGenerator);

  std::thread schedulerThread(startScheduler);

  std::thread cpuThread(startCPUs, std::ref(cpus));

  std::this_thread::sleep_for(std::chrono::seconds(10));
  stopAll = true;

  processGeneratorThread.join();
  schedulerThread.join();
  cpuThread.join();

  for (auto &cpu : cpus) {
    cpu.stop();
  }

  std::cout << "Simulation finished." << std::endl;
  logFile.close();
  std::cout << "total score : " << total_score << ", miss count: " << miss_cnt << std::endl;
  std::cout << "Do you want run it again?[Y/n] " << std::endl;
  std::string input = "";
  std::cin >> input;
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  //use Alacritty terminal (You can change it!)
  if (input != "n" && input != "no" && input != "nope") { system("alacritty -e bash -c \"./a.out\""); }
  return 0;
}
