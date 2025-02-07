#include "../headers/process.h"
#include <cstdlib>

Process::Process(int pid,double arrivalTime){
  this->pid=pid;
  this->arrivalTime = arrivalTime;
  this->executionTime = (rand() % 10) + 1;
  this->startDeadline = arrivalTime + (rand() % 5) + 1;
  this->endDeadline = this->startDeadline + (rand() % 5) + 1;
  this->cpu_number = -1;
  this->execute = false;
  this->score = (rand() % 100) + 1;;
}
void Process::setCPU(int cpu_number){
  this->cpu_number = cpu_number;
}
bool Process::reverseExecution(){
  this->execute = !this->execute;
  return this->execute;
}