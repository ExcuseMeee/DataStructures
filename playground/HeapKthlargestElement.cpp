#include <iostream>
#include <vector>
using namespace std;

const int MAX_HEAP_SIZE = 10000;

// Min heap implementation
class MinHeap {
public:
  MinHeap() {}

  void insert(int val) {
    this->data.push_back(val);

    int i = this->data.size() - 1; // index of last node (this one we just inserted)

    // percolate UP
    while (data[i] < data[(i - 1) / 2]) {
      swap(data[i], data[(i - 1) / 2]);
      i = (i - 1) / 2;
    }

  }

  void print() const {
    std::cout << "[print]" << std::endl;
    int curLevel = 0;
    int newLevel = 1;

    for (const int& element : this->data) {
      std::cout << element << " ";
      curLevel++;
      if (curLevel == newLevel) {
        std::cout << "\n";
        newLevel *= 2;
        curLevel = 0;
      }
    }
    std::cout << std::endl;
  }

  int popMin() {
    if (this->data.empty()) throw std::string("[popMin] empty string");

    int return_val = data[0]; // min val should be at root for a minheap

    // replace root node with last node, then percolate down
    data[0] = data[data.size() - 1];
    data.pop_back(); // remove last node (we are moved it to index 0)

    percolateDown(0); // perc down from root

    return return_val;

  }

private:
  vector<int> data; // use vector to make things a bit easier

  void swap(int& v1, int& v2) {
    int temp = v1;
    v1 = v2;
    v2 = temp;

  }

  void percolateDown(int index) {
    if (index < 0 || index >= this->data.size()) return;

    int curIndex = index;
    int newIndex = index;
    do {

      // determine which child to attempt swap with
      if (curIndex * 2 + 1 >= data.size()) {
        // if searching for left kid is out of bounds, then right kid definitely doesnt exist either. no kids to swap with.
        break;
      }
      else if (curIndex * 2 + 2 >= data.size()) {
        // no right kid, only left kid
        newIndex = curIndex * 2 + 1;
      }
      else if (curIndex * 2 + 2 < data.size()) {
        // both kids exist
        int leftVal = data[curIndex * 2 + 1];
        int rightVal = data[curIndex * 2 + 2];

        newIndex = leftVal < rightVal ? curIndex * 2 + 1 : curIndex * 2 + 2;
      }

      // perform swap IF child is less
      if (data[newIndex] < data[curIndex]) {
        swap(data[curIndex], data[newIndex]);
        curIndex = newIndex;
      }
      else {
        // if child is NOT less, then we cannot percolate any further
        break;
      }

    } while (true);


  }

};

// Function to find the kth largest element in an array. duplicates are counted
int findKthLargest(int arr[], int n, int k) {
  // largest goes from [1,n]. 1st largest (largest overall) to nth largest (smallest overall) ?
  if (k < 1 || k > n) throw string("invalid k value");
  MinHeap h;
  for (int i = 0; i < n; i++) {
    h.insert(arr[i]);
  }
  // kth largest is n-k+1 smallest?
  int t = n - k + 1;
  // pop t times from heap
  int min;
  for (int i = 0; i < t; i++) {
    min = h.popMin();
  }

  return min;


}

int main() {

  int arr[] = { 3,2,3,1,2,4,5,5,6 };

  int n = sizeof(arr) / sizeof(arr[0]);
  int k = 3; 

  cout << "k=" << k << endl;
  cout << "Kth largest element: " << findKthLargest(arr, n, k) << endl; // will throw if k < 1 or k > arr length


  return 0;
}
