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

 public:
  void SiftUpMin(int index) {
    while (index > 0 &&
           heap_min_[index].first < heap_min_[(index - 1) / 2].first) {
      SwapNodesInHeapMin(index, (index - 1) / 2);
    }
  }

  void SiftDownMax(int index) {
    while (2 * index + 1 <= length_ - 1) {
      if (2 * index + 1 == length_ - 1) {
        if (heap_min_[index].first > heap_min_[2 * index + 1].first) {
          SwapNodesInHeapMin(index, 2 * index + 1);
        } else {
          break;
        }
      } else {
        if (heap_min_[index].first > heap_min_[2 * index + 1].first ||
            heap_min_[index].first > heap_min_[2 * index + 2].first) {
          if (heap_min_[2 * index + 1].first > heap_min_[2 * index + 2].first) {
            SwapNodesInHeapMin(index, 2 * index + 2);
          } else {
            SwapNodesInHeapMin(index, 2 * index + 1);
          }
        } else {
          break;
        }
      }
    }
  }

  void SiftUpMax(int index) {
    while (index > 0 &&
           heap_max_[index].first > heap_max_[(index - 1) / 2].first) {
      SwapNodesInHeapMax(index, (index - 1) / 2);
    }
  }

  void SiftDownMin(int index) {
    while (2 * index + 1 <= length_ - 1) {
      if (2 * index + 1 == length_ - 1) {
        if (heap_max_[index].first < heap_max_[2 * index + 1].first) {
          SwapNodesInHeapMax(index, 2 * index + 1);
        } else {
          break;
        }
      } else {
        if (heap_max_[index].first < heap_max_[2 * index + 1].first ||
            heap_max_[index].first < heap_max_[2 * index + 2].first) {
          if (heap_max_[2 * index + 1].first < heap_max_[2 * index + 2].first) {
            SwapNodesInHeapMax(index, 2 * index + 2);
          } else {
            SwapNodesInHeapMax(index, 2 * index + 1);
          }
        } else {
          break;
        }
      }
    }
  }

  void Insert() {
    int number;
    std::cin >> number;
    ++length_;
    heap_min_.push_back(std::make_pair(number, length_ - 1));
    heap_max_.push_back(std::make_pair(number, length_ - 1));
    SiftUpMin(length_ - 1);
    SiftUpMax(length_ - 1);
    std::cout << "ok" << std::endl;
  }

  void ExtractMin() {
    if (length_ > 0) {
      std::cout << heap_min_[0].first << std::endl;
      std::swap(heap_max_[heap_min_[0].second].second,
                heap_max_[heap_min_[length_ - 1].second].second);
      std::swap(heap_min_[0], heap_min_[length_ - 1]);
      heap_min_[heap_max_[length_ - 1].second].second =
          heap_min_[length_ - 1].second;
      std::swap(heap_max_[length_ - 1],
                heap_max_[heap_min_[length_ - 1].second]);
      heap_max_.pop_back();
      SiftUpMax(heap_min_[length_ - 1].second);
      heap_min_.pop_back();
      --length_;
      SiftDownMax(0);
    } else {
      std::cout << "error" << std::endl;
    }
  }

  void GetMin() {
    if (length_ > 0) {
      std::cout << heap_min_[0].first << std::endl;
    } else {
      std::cout << "error" << std::endl;
    }
  }

  void ExtractMax() {
    if (length_ > 0) {
      std::cout << heap_max_[0].first << std::endl;
      std::swap(heap_min_[heap_max_[0].second].second,
                heap_min_[heap_max_[length_ - 1].second].second);
      std::swap(heap_max_[0], heap_max_[length_ - 1]);
      heap_max_[heap_min_[length_ - 1].second].second =
          heap_max_[length_ - 1].second;
      std::swap(heap_min_[length_ - 1],
                heap_min_[heap_max_[length_ - 1].second]);
      heap_min_.pop_back();
      SiftUpMin(heap_max_[length_ - 1].second);
      heap_max_.pop_back();
      --length_;
      SiftDownMin(0);
    } else {
      std::cout << "error" << std::endl;
    }
  }

  void GetMax() {
    if (length_ > 0) {
      std::cout << heap_max_[0].first << std::endl;
    } else {
      std::cout << "error" << std::endl;
    }
  }

  void Size() const { std::cout << length_ << std::endl; }

  void Clear() {
    std::cout << "ok" << std::endl;
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
    } else if (command == "extract_min") {
      minimax.ExtractMin();
    } else if (command == "get_min") {
      minimax.GetMin();
    } else if (command == "extract_max") {
      minimax.ExtractMax();
    } else if (command == "get_max") {
      minimax.GetMax();
    } else if (command == "size") {
      minimax.Size();
    } else if (command == "clear") {
      minimax.Clear();
    }
  }
}
