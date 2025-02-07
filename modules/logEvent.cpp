#include "../headers/logEvent.h"
#include "../headers/process.h"
#include <iostream>
#include <mutex>

std::mutex logMutex;
extern int total_score, miss_cnt, total_waiting_time, expire_cnt;

void logEvent(const std::string &event, int cpu_id, const Process &p) {
    double currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::steady_clock::now().time_since_epoch()).count();
    std::lock_guard<std::mutex> lock(logMutex);
    logFile << currentTime << ","
            << event << ","
            << cpu_id << ","
            << p.getPid() << ","
            << p.getExecutionTime() << ","
            << p.getStartDeadline() << ","
            << p.getEndDeadline() << ","
            << p.getScore() << ","
            << total_waiting_time << ","
            << expire_cnt << ","
            << miss_cnt << ","
            << total_score << std::endl;
    logFile.flush();
    std::cout << event << ": CPU " << cpu_id << " Process " << p.getPid() << "\n";
}

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);

    std::ostringstream oss;
    oss << "./logs/log_" << std::put_time(&now_tm, "%Y-%m-%d_%H-%M-%S") << ".csv";
    return oss.str();
}

void calculateWaitingTime(Process p, int start_time) {
    int waiting_time = start_time - p.getArrivalTime();
    total_waiting_time += waiting_time;
}
