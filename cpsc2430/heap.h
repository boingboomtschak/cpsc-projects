// Devon McKee
// heap.h
// Header file for Heap
// 2019-05-13

#ifndef HEAP_H
#define HEAP_H

class Heap
{
 public:
  class EmptyHeap{}; // thrown when removing from empty heap
  Heap(); // constructor
  Heap(const Heap &cp); // copy constructor
  Heap& operator=(const Heap &cp); // overloaded assignment operator
  ~Heap(); // destructor
  void insert(int key);
  // PRE: requires integer to be added to heap
  // POST: heap array contains one more int, with others adjusted
  int removeMin();
  // PRE: requires item to be on heap, throws EmptyHeap otherwise.
  // POST: heap array contains one less int (smallest), with others adjusted
  bool flush(int key);
  // PRE: heap should contain key to flush
  // POST: bool returns false if key not found.
  bool empty();
  // PRE: heap must be initialized
  // POST: returns true if heap elems >0 
 private:
  static const int DEFAULT_SIZE = 10; // default size of heap array
  int* heap; // * to arr containing heap values
  int size; // num of current arr size
  int elem; // num of elements on heap
  int remove(int hole);
  // PRE: elem must be >0 or EmptyHeap thrown
  // POST: elem at index 'hole' removed, heap restructured accordingly
  void percolateDown(int hole);
  // PRE: hole must be num of index in array
  // POST: element in hole moved to necessary position in heap
  void resize();
  // PRE: heap must be initialized
  // POST: heap elements copied into new array of 1.5x size
};

#endif // heap_h
