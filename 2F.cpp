#include <iostream>
#include <string>
#include <vector>

void SiftUp(std::vector<std::pair<long long, int>>& heap,
            std::vector<int>& operations, int index) {
  while (index > 0 && heap[index].first < heap[(index - 1) / 2].first) {
    std::swap(operations[heap[index].second],
              operations[heap[(index - 1) / 2].second]);
    std::swap(heap[index], heap[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}

void SiftDown(std::vector<std::pair<long long, int>>& heap, int length,
              std::vector<int>& operations, int index) {
  while (2 * index + 1 <= length - 1) {
    if (2 * index + 1 == length - 1) {
      if (heap[index].first > heap[2 * index + 1].first) {
        std::swap(operations[heap[index].second],
                  operations[heap[2 * index + 1].second]);
        std::swap(heap[index], heap[2 * index + 1]);
        index = 2 * index + 1;
      } else {
        break;
      }
    } else {
      if (heap[index].first > heap[2 * index + 1].first ||
          heap[index].first > heap[2 * index + 2].first) {
        if (heap[2 * index + 1].first > heap[2 * index + 2].first) {
          std::swap(operations[heap[index].second],
                    operations[heap[2 * index + 2].second]);
          std::swap(heap[index], heap[2 * index + 2]);
          index = 2 * index + 2;
        } else {
          std::swap(operations[heap[index].second],
                    operations[heap[2 * index + 1].second]);
          std::swap(heap[index], heap[2 * index + 1]);
          index = 2 * index + 1;
        }
      } else {
        break;
      }
    }
  }
}

void Insert(std::vector<std::pair<long long, int>>& heap, int& length,
            std::vector<int>& operations, long long number) {
  operations.push_back(length++);
  heap.push_back(
      std::make_pair(number, static_cast<int>(operations.size()) - 1));
  SiftUp(heap, operations, length - 1);
}

long long GetMin(std::vector<std::pair<long long, int>>& heap) {
  return heap[0].first;
}

void ExtractMin(std::vector<std::pair<long long, int>>& heap, int& length,
                std::vector<int>& operations) {
  std::swap(operations[heap[0].second], operations[heap[length - 1].second]);
  std::swap(heap[0], heap[--length]);
  heap.pop_back();
  SiftDown(heap, length, operations, 0);
}

void DecreaseKey(std::vector<std::pair<long long, int>>& heap,
                 std::vector<int>& operations, int operation_num,
                 long long number) {
  heap[operations[operation_num - 1]].first -= number;
  SiftUp(heap, operations, operations[operation_num - 1]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int questions;
  std::cin >> questions;
  std::vector<std::pair<long long, int>> heap(0);
  std::vector<int> operations(0);
  int length = 0;
  std::string command;
  long long number;
  int operation_num;
  for (int question = 0; question < questions; ++question) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> number;
      Insert(heap, length, operations, number);
    } else if (command == "getMin") {
      operations.push_back(-1);
      std::cout << GetMin(heap) << "\n";
    } else if (command == "extractMin") {
      operations.push_back(-1);
      ExtractMin(heap, length, operations);
    } else if (command == "decreaseKey") {
      operations.push_back(-1);
      std::cin >> operation_num;
      std::cin >> number;
      DecreaseKey(heap, operations, operation_num, number);
    }
  }
}
