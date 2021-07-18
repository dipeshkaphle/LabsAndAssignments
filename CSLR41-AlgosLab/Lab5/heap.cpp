#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> class Heap {
public:
  Heap(bool (*cmp)(T, T)) {
    this->size = 0;
    this->cmpFunc = cmp;
  }

  void from_array(vector<int> &vec) {
    this->arr.clear();
    this->arr = std::move(vec);
    this->size = this->arr.size();
    for (int i = this->size / 2; i >= 0; i--) {
      this->heapifyAtIndex(i);
    }
  }

  // This will heapify the element at given index
  // A smaller helper function that will help us in
  // heapifying the queue
  // useful to maintain heap invariant
  // For example: We are making a min heap
  // Provided an index i, it will make the element at
  // index i less than the element at index 2*i +1 and 2*i+2
  bool heapifyAtIndex(int index) {
    int br1 = 2 * index + 1;
    int br2 = br1 + 1;
    bool swapped = false;
    if (br1 < this->arr.size()) {
      if (this->cmpFunc(this->arr[br1], this->arr[index]) == 1) {
        T tmp = this->arr[br1];
        this->arr[br1] = this->arr[index];
        this->arr[index] = tmp;
        this->heapifyAtIndex(br1);
        swapped = true;
      }
    }
    if (br2 < this->arr.size()) {
      if (this->cmpFunc(this->arr[br2], this->arr[index]) == 1) {
        T tmp = this->arr[br2];
        this->arr[br2] = this->arr[index];
        this->arr[index] = tmp;
        this->heapifyAtIndex(br2);
        swapped = true;
      }
    }
    return swapped;
  }

  T extract_min() {
    if (this->size == 0)
      throw "Heap Empty";
    // swapping the first and last elem to facilitate deletion
    T tmp = this->arr[0];
    this->arr[0] = this->arr[this->arr.size() - 1];
    this->arr[this->arr.size() - 1] = tmp;
    this->arr.pop_back();
    this->size--;
    this->heapifyAtIndex(0);
    return tmp;
  }

  T top() {
    if (this->size == 0)
      throw "Heap Empty";
    return this->arr[0];
  }

  // Inserts to the heap
  // Also keeps the heap property intact
  // We bubble up from the end of the array
  // This has complexity of O(logN) i.e height of heap
  void push(T data) {
    this->arr.push_back(data);
    this->size++;
    int i = this->size - 1;
    i = floor((double(i - 1) / 2));
    while (i >= 0) {
      if (!this->heapifyAtIndex(i))
        break;
      i = floor((double)(i - 1) / 2);
    }
  }
  bool isEmpty() { return this->size == 0; }
  void display() {
    Heap<T> a(this->cmpFunc);
    while (!this->isEmpty()) {
      cout << this->top() << endl;
      a.enqueue(this->dequeue());
    }
    while (!a.isEmpty())
      this->enqueue(a.dequeue());
  }

private:
  int size;
  bool (*cmpFunc)(T, T);
  vector<T> arr;
};
