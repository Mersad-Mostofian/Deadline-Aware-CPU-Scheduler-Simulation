#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "./process.h"
#include <string>

std::string getTimestamp();
void logEvent(const std::string &event, int cpu_id, const Process &p);
void calculateWaitingTime(Process p, int start_time);
extern std::ofstream logFile;

#endif
