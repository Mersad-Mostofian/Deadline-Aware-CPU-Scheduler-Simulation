#ifndef PROCESS_GENERATOR_H
#define PROCESS_GENERATOR_H

#include "process.h"
#include "queue.h"

Process generateProcesses(int pid);
void process_generator(Queue &inputQueue);
void requestProcessCreation(int pid, Queue &inputQueue);

#endif
