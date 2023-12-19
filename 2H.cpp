#include <iostream>
#include <string>
#include <vector>

class Minimax {
 private:
  std::vector<std::pair<int, int>> heap_min_;
  std::vector<std::pair<int, int>> heap_max_;
  int length_ = 0;

  void SwapNodesInHeapMin(int& index_1, int index_2) {
    std::swap(heap_max_[heap_min_[index_1].second].second,
              heap_max_[heap_min_[index_2].second].second);
    std::swap(heap_min_[index_1], heap_min_[index_2]);
    index_1 = index_2;
  }

  void SwapNodesInHeapMax(int& index_1, int index_2) {
    std::swap(heap_min_[heap_max_[index_1].second].second,
              heap_min_[heap_max_[index_2].second].second);
    std::swap(heap_max_[index_1], heap_max_[index_2]);
    index_1 = index_2;
  }

  int ExtractSomething(std::vector<std::pair<int, int>>& heap_first,
                       std::vector<std::pair<int, int>>& heap_second,
                       bool is_min) {
    if (length_ == 0) {
      return 0;
    }
    int answer = heap_first[0].first;
    std::swap(heap_second[heap_first[0].second].second,
              heap_second[heap_first[length_ - 1].second].second);
    std::swap(heap_first[0], heap_first[length_ - 1]);
    heap_first[heap_second[length_ - 1].second].second =
        heap_first[length_ - 1].second;
    std::swap(heap_second[length_ - 1],
              heap_second[heap_first[length_ - 1].second]);
    heap_second.pop_back();
    if (is_min) {
      SiftUpMax(heap_first[length_ - 1].second);
    } else {
      SiftUpMin(heap_first[length_ - 1].second);
    }
    heap_first.pop_back();
    --length_;
    if (is_min) {
      SiftDownMax(0);
    } else {
      SiftDownMin(0);
    }
    return answer;
  }

  int GetSomething(std::vector<std::pair<int, int>>& heap) const {
    if (length_ > 0) {
      return heap[0].first;
    }
    return 0;
  }

  bool CompareElementsInHeaps(int index_1, int index_2, bool is_min) {
    if (is_min) {
      return heap_max_[index_1].first < heap_max_[index_2].first;
    }
    return heap_min_[index_1].first > heap_min_[index_2].first;
  }

  void SwapNodes(int& index_1, int index_2, bool is_min) {
    if (is_min) {
      SwapNodesInHeapMin(index_1, index_2);
    } else {
      SwapNodesInHeapMax(index_1, index_2);
    }
  }

  void SiftUpSomething(int index, bool is_min) {
    while (index > 0 &&
           CompareElementsInHeaps((index - 1) / 2, index, !is_min)) {
      SwapNodes(index, (index - 1) / 2, is_min);
    }
  }

  void SiftDownSomething(int index, bool is_min) {
    while (2 * index + 1 <= length_ - 1) {
      if (2 * index + 1 == length_ - 1) {
        if (CompareElementsInHeaps(index, 2 * index + 1, !is_min)) {
          SwapNodes(index, 2 * index + 1, is_min);
        } else {
          break;
        }
      } else {
        if (CompareElementsInHeaps(index, 2 * index + 1, !is_min) ||
            CompareElementsInHeaps(index, 2 * index + 2, !is_min)) {
          if (CompareElementsInHeaps(2 * index + 1, 2 * index + 2, !is_min)) {
            SwapNodes(index, 2 * index + 2, is_min);
          } else {
            SwapNodes(index, 2 * index + 1, is_min);
          }
        } else {
          break;
        }
      }
    }
  }

 public:
  void SiftUpMin(int index) { SiftUpSomething(index, true); }

  void SiftDownMax(int index) { SiftDownSomething(index, true); }

  void SiftUpMax(int index) { SiftUpSomething(index, false); }

  void SiftDownMin(int index) { SiftDownSomething(index, false); }

  void Insert() {
    int number;
    std::cin >> number;
    ++length_;
    heap_min_.emplace_back(number, length_ - 1);
    heap_max_.emplace_back(number, length_ - 1);
    SiftUpMin(length_ - 1);
    SiftUpMax(length_ - 1);
  }

  int ExtractMin() { return ExtractSomething(heap_min_, heap_max_, true); }

  int GetMin() { return GetSomething(heap_min_); }

  int ExtractMax() { return ExtractSomething(heap_max_, heap_min_, false); }

  int GetMax() { return GetSomething(heap_max_); }

  int Size() const { return length_; }

  void Clear() {
    heap_min_.clear();
    heap_max_.clear();
    length_ = 0;
  }
};

int main() {
  int questions;
  std::cin >> questions;
  Minimax minimax;
  std::string command;
  for (int question = 0; question < questions; ++question) {
    std::cin >> command;
    if (command == "insert") {
      minimax.Insert();
      std::cout << "ok\n";
    } else if (command == "extract_min") {
      int answer = minimax.ExtractMin();
      if (answer != 0) {
        std::cout << answer << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (command == "get_min") {
      int answer = minimax.GetMin();
      if (answer != 0) {
        std::cout << answer << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (command == "extract_max") {
      int answer = minimax.ExtractMax();
      if (answer != 0) {
        std::cout << answer << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (command == "get_max") {
      int answer = minimax.GetMax();
      if (answer != 0) {
        std::cout << answer << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (command == "size") {
      std::cout << minimax.Size() << "\n";
    } else if (command == "clear") {
      minimax.Clear();
      std::cout << "ok\n";
    }
  }
}
