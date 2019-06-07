// Devon McKee
// queue.h
// Header file for Queue class (handles ints)
// 2019-02-28

// #includes here

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
 public:
  class EmptyQueue{};
  Queue();
  Queue(int num);
  Queue(const Queue &cp);
  Queue& operator=(const Queue &cp);
  ~Queue();
  void enqueue(int val);
  // enqueues val in queue
  int dequeue();
  // returns value at front of queue
  bool isEmpty();
  // returns true if stack is empty
 private:
  struct Node {
    int data;
    Node* next;
  };
  Node* front;
  // pointer to front of queue
  Node* tail;
  // pointer to end of queue
};

#endif //
