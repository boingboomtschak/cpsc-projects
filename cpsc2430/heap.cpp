// Devon McKee
// heap.cpp
// Implementation of Heap as described in heap.h

#include "heap.h"
#include <iostream>

using namespace std;

Heap::Heap()
{
  heap = new int[DEFAULT_SIZE];
  size = DEFAULT_SIZE;
  elem = 0;
}

Heap::Heap(const Heap &cp)
{
  size = cp.size;
  elem = cp.elem;
  heap = new int[size];
  for(int i=0; i<=elem; i++){
    heap[i] = cp.heap[i];
  }
}

Heap& Heap::operator=(const Heap &cp)
{
  if(this != &cp){
    size = cp.size;
    elem = cp.elem;
    heap = new int[size];
    for(int i=0; i<=elem; i++){
      heap[i] = cp.heap[i];
    }
  }
  return *this;
}

Heap::~Heap()
{
  delete[] heap;
}

void Heap::insert(int num)
{
  elem++;
  if(elem == size)
    resize();
  int hole = elem;
  while(hole > 1 && num < heap[hole/2]){
    heap[hole] = heap[hole/2];
    hole = hole/2;
  }
  heap[hole] = num;
}

int Heap::removeMin()
{
  return remove(1);
}

bool Heap::flush(int key)
{
  bool ret = false;
  for(int i=1; i<=elem; i++){
    if(heap[i] == key){
      remove(i);
      ret = true;
    }
  }
  return ret;
}

bool Heap::empty()
{
  if(elem == 0){
    return true;
  }else{
    return false;
  }
}

int Heap::remove(int hole)
{
  if(elem == 0){
    throw EmptyHeap();
  }else{ 
    int rm = heap[hole];
    heap[hole] = heap[elem];
    elem--;
    percolateDown(hole);
    return rm;
  }
}

void Heap::percolateDown(int hole)
{
  int temp = heap[hole];
  while((hole*2 <= elem && temp > heap[hole*2])
        || (hole*2+1 <= elem && temp > heap[hole*2+1])){
    if(hole*2+1 <= elem && heap[hole*2+1] < heap[hole*2]){
      heap[hole] = heap[hole*2+1];
      hole = hole*2+1;
    }else{
      heap[hole] = heap[hole*2];
      hole = hole*2;
    }
  }
  heap[hole] = temp;
}

void Heap::resize()
{
  int newSize = size * 1.5;
  int* temp = new int[newSize];
  for(int i=0; i<size; i++){
    temp[i] = heap[i];
  }
  delete[] heap;
  size = newSize;
  heap = temp;
}
 
