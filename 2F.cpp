#include <iostream>
#include <string>
#include <vector>

class Binaryheap {
 private:
  std::vector<std::pair<long long, int>> heap_;
  std::vector<int> operations_;
  int length_ = 0;

 public:
  void SiftUp(int index) {
    while (index > 0 && heap_[index].first < heap_[(index - 1) / 2].first) {
      std::swap(operations_[heap_[index].second],
                operations_[heap_[(index - 1) / 2].second]);
      std::swap(heap_[index], heap_[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  void SiftDown(int index) {
    while (2 * index + 1 <= length_ - 1) {
      if (2 * index + 1 == length_ - 1) {
        if (heap_[index].first > heap_[2 * index + 1].first) {
          std::swap(operations_[heap_[index].second],
                    operations_[heap_[2 * index + 1].second]);
          std::swap(heap_[index], heap_[2 * index + 1]);
          index = 2 * index + 1;
        } else {
          break;
        }
      } else {
        if (heap_[index].first > heap_[2 * index + 1].first ||
            heap_[index].first > heap_[2 * index + 2].first) {
          if (heap_[2 * index + 1].first > heap_[2 * index + 2].first) {
            std::swap(operations_[heap_[index].second],
                      operations_[heap_[2 * index + 2].second]);
            std::swap(heap_[index], heap_[2 * index + 2]);
            index = 2 * index + 2;
          } else {
            std::swap(operations_[heap_[index].second],
                      operations_[heap_[2 * index + 1].second]);
            std::swap(heap_[index], heap_[2 * index + 1]);
            index = 2 * index + 1;
          }
        } else {
          break;
        }
      }
    }
  }

  void Insert(long long number) {
    operations_.push_back(length_++);
    heap_.push_back(
        std::make_pair(number, static_cast<int>(operations_.size()) - 1));
    this->SiftUp(length_ - 1);
  }

  long long GetMin() {
    operations_.push_back(-1);
    return heap_[0].first;
  }

  void ExtractMin() {
    operations_.push_back(-1);
    std::swap(operations_[heap_[0].second],
              operations_[heap_[length_ - 1].second]);
    std::swap(heap_[0], heap_[--length_]);
    heap_.pop_back();
    this->SiftDown(0);
  }

  void DecreaseKey(int operation_num, long long number) {
    operations_.push_back(-1);
    heap_[operations_[operation_num - 1]].first -= number;
    this->SiftUp(operations_[operation_num - 1]);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int questions;
  std::cin >> questions;
  Binaryheap binary_heap;
  std::string command;
  long long number;
  int operation_num;
  for (int question = 0; question < questions; ++question) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> number;
      binary_heap.Insert(number);
    } else if (command == "getMin") {
      std::cout << binary_heap.GetMin() << "\n";
    } else if (command == "extractMin") {
      binary_heap.ExtractMin();
    } else if (command == "decreaseKey") {
      std::cin >> operation_num;
      std::cin >> number;
      binary_heap.DecreaseKey(operation_num, number);
    }
  }
}
