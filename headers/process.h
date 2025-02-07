#ifndef PROCESS_H
#define PROCESS_H

class Process {
  private:
      double executionTime;
      double startDeadline;
      double arrivalTime;
      double endDeadline;
      int cpu_number;
      bool execute;
      int score;
      int pid;
  public:
    Process(int pid, double arrivalTime);
    void setCPU(int cpu_number);
    bool reverseExecution();
    double getExecutionTime() const { return executionTime; }
    double getStartDeadline() const { return startDeadline; }
    double getArrivalTime() const { return arrivalTime; }
    double getEndDeadline() const { return endDeadline; }
    bool isExecuting() const { return execute; }
    int getCPU() const { return cpu_number; }
    int getScore() const { return score; }
    int getPid() const { return pid; }
};

#endif