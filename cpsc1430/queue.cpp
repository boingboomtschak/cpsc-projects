// Devon McKee
// queue.cpp
// Implementation of Queue as described in queue.h

#include "queue.h"
#include <iostream> // remove before completing

using namespace std;

Queue::Queue()
{
  front = nullptr;
  tail = nullptr;
}

Queue::Queue(const Queue &cp)
{
  if(cp.front == nullptr){
    front = nullptr;
    tail = nullptr;
  }else{ 
    Node* cpwalk = cp.front->next;
    Node* walk;
    front = new Node;
    front->data = cp.front->data;
    front->next = nullptr;
    walk = front;
    while(cpwalk != nullptr){
      Node* temp = new Node;
      temp->data = cpwalk->data;
      walk->next = temp;
      walk = walk->next;
      cpwalk = cpwalk->next;
    }
    tail = walk;
    tail->next = nullptr;
  }
}

Queue& Queue::operator=(const Queue &cp)
{
  if(this != &cp){
    if(cp.front == nullptr){
      front = nullptr;
      tail = nullptr;
    }else{      
      Node* cpwalk = cp.front->next;
      Node* walk;
      front = new Node;
      front->data = cp.front->data;
      front->next = nullptr;
      walk = front;
      while(cpwalk != nullptr){
        Node* temp = new Node;
        temp->data = cpwalk->data;
        walk->next = temp;
        walk = walk->next;
        cpwalk = cpwalk->next;
      }
      tail = walk;
      tail->next = nullptr;
    }
  }
  return *this;
}

Queue::~Queue()
{
  Node* walk = front;
  Node* delptr;
  while(walk != nullptr){
    delptr = walk;
    walk = walk->next;
    delete delptr;
  }
}

void Queue::enqueue(int val)
{
  if(front == nullptr){
    front = new Node;
    front->data = val;
    front->next = nullptr;
    tail = front;
  }else{ 
    Node* temp = new Node;
    temp->data = val;
    temp->next = nullptr;
    tail->next = temp;
    tail = tail->next;
  }
}

int Queue::dequeue()
{
  if(front == nullptr){
    throw EmptyQueue();
  }else{
    Node* ptr;
    int store;
    ptr = front;
    store = front->data;
    front = front->next;
    delete ptr;
    return store;
  }
}

bool Queue::isEmpty()
{
  return (front == nullptr);
}
