#include "process.h"
#include <vector>

#ifndef QUEUE_H
#define QUEUE_H

class Queue {
  private:
    int capacity;
    std::vector<Process> array;
    int parent(int i){ return (i-1)/2; }
    int leftChild(int i){ return (i*2)+1; }
    int rightChild(int i){ return (i*2)+2; }
    void shiftUp(int i);
    void shiftDown(int i);
  public:
    Queue(int capacity);
    ~Queue();
    bool isFull();
    bool isEmpty();
    void enqueue(Process p);
    Process dequeue();
    Process front();
    Process back();
    int size();
};

#endif