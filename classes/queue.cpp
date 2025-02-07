#include <iostream>
#include <chrono>
#include "../headers/queue.h"
#include "../headers/logEvent.h"

extern int miss_cnt, expire_cnt;
extern std::ofstream logFile;

Queue::Queue(int capacity){
  this->capacity = capacity;
 }
Queue::~Queue() { std::vector<Process>().swap(this->array); }

 bool Queue::isEmpty(){
   return this->array.empty();
 }
 bool Queue::isFull(){
   return this->array.size() >= this->capacity;
 }
 void Queue::enqueue(Process p){
   if(!this->isFull()){
     this->array.push_back(p);
     this->shiftUp(this->array.size() - 1);

   }else{
     std::cout << "Queue is full, skipping process with PID: " << p.getPid() << std::endl;
   }

 }

Process Queue::dequeue() {
    if (this->isEmpty()) {
        std::cout << "Queue is empty, cannot dequeue.\n";
        return Process(-1, -1);
    }

    double currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::steady_clock::now().time_since_epoch()).count();

    while (!this->isEmpty() &&
       (this->array[0].getEndDeadline() < currentTime ||
        this->array[0].getStartDeadline() < currentTime)) {
    logEvent("missed", -1, this->array[0]);
    expire_cnt++;
    miss_cnt++;
    this->array.erase(this->array.begin());

        if (this->isEmpty()) {
            std::cout << "Queue is empty after removing expired processes.\n";
            return Process(-1, -1);
        }
		shiftDown(0);
    }

    if (this->isEmpty()) {
        return Process(-1, -1);
    }

    Process max_score = this->array[0];
    this->array[0] = this->array.back();
    this->array.pop_back();
    shiftDown(0);
    return max_score;
}
Process Queue::front(){
  if(this->isEmpty()){
    throw std::underflow_error("Queue is empty");
  }
  return this->array[0];
}

Process Queue::back(){
  if(this->isEmpty()){
    throw std::underflow_error("Queue is empty");
  }
  return this->array.back();
}

int Queue::size(){
  return this->array.size();
}

void Queue::shiftUp(int index){
  while(index > 0 && this->array[parent(index)].getScore() < array[index].getScore()){
    std::swap(this->array[parent(index)], this->array[index]);
    index = parent(index);
  }
}

void Queue::shiftDown(int index){
  int maxIndex = index;
  int left = leftChild(index);
  if (left < size() && array[left].getScore() > array[maxIndex].getScore()){
    maxIndex = left;
  }
  int right = rightChild(index);
  if (right < size() && array[right].getScore() > array[maxIndex].getScore()){
    maxIndex = right;
  }
  if (index != maxIndex){
    std::swap(this->array[index], this->array[maxIndex]);
    shiftDown(maxIndex);
  }
}