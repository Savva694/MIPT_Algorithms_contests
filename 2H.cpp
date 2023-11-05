#include <iostream>
#include <string>
#include <vector>

void SiftUpMin(std::vector<std::pair<int, int>>& heap_min,
               std::vector<std::pair<int, int>>& heap_max, int index) {
  while (index > 0 && heap_min[index].first < heap_min[(index - 1) / 2].first) {
    std::swap(heap_max[heap_min[index].second].second,
              heap_max[heap_min[(index - 1) / 2].second].second);
    std::swap(heap_min[index], heap_min[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}

void SiftDownMax(std::vector<std::pair<int, int>>& heap_min,
                 std::vector<std::pair<int, int>>& heap_max, int length,
                 int index) {
  while (2 * index + 1 <= length - 1) {
    if (2 * index + 1 == length - 1) {
      if (heap_min[index].first > heap_min[2 * index + 1].first) {
        std::swap(heap_max[heap_min[index].second].second,
                  heap_max[heap_min[2 * index + 1].second].second);
        std::swap(heap_min[index], heap_min[2 * index + 1]);
        index = 2 * index + 1;
      } else {
        break;
      }
    } else {
      if (heap_min[index].first > heap_min[2 * index + 1].first ||
          heap_min[index].first > heap_min[2 * index + 2].first) {
        if (heap_min[2 * index + 1].first > heap_min[2 * index + 2].first) {
          std::swap(heap_max[heap_min[index].second].second,
                    heap_max[heap_min[2 * index + 2].second].second);
          std::swap(heap_min[index], heap_min[2 * index + 2]);
          index = 2 * index + 2;
        } else {
          std::swap(heap_max[heap_min[index].second].second,
                    heap_max[heap_min[2 * index + 1].second].second);
          std::swap(heap_min[index], heap_min[2 * index + 1]);
          index = 2 * index + 1;
        }
      } else {
        break;
      }
    }
  }
}

void SiftUpMax(std::vector<std::pair<int, int>>& heap_min,
               std::vector<std::pair<int, int>>& heap_max, int index) {
  while (index > 0 && heap_max[index].first > heap_max[(index - 1) / 2].first) {
    std::swap(heap_min[heap_max[index].second].second,
              heap_min[heap_max[(index - 1) / 2].second].second);
    std::swap(heap_max[index], heap_max[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}

void SiftDownMin(std::vector<std::pair<int, int>>& heap_min,
                 std::vector<std::pair<int, int>>& heap_max, int length,
                 int index) {
  while (2 * index + 1 <= length - 1) {
    if (2 * index + 1 == length - 1) {
      if (heap_max[index].first < heap_max[2 * index + 1].first) {
        std::swap(heap_min[heap_max[index].second].second,
                  heap_min[heap_max[2 * index + 1].second].second);
        std::swap(heap_max[index], heap_max[2 * index + 1]);
        index = 2 * index + 1;
      } else {
        break;
      }
    } else {
      if (heap_max[index].first < heap_max[2 * index + 1].first ||
          heap_max[index].first < heap_max[2 * index + 2].first) {
        if (heap_max[2 * index + 1].first < heap_max[2 * index + 2].first) {
          std::swap(heap_min[heap_max[index].second].second,
                    heap_min[heap_max[2 * index + 2].second].second);
          std::swap(heap_max[index], heap_max[2 * index + 2]);
          index = 2 * index + 2;
        } else {
          std::swap(heap_min[heap_max[index].second].second,
                    heap_min[heap_max[2 * index + 1].second].second);
          std::swap(heap_max[index], heap_max[2 * index + 1]);
          index = 2 * index + 1;
        }
      } else {
        break;
      }
    }
  }
}

void Insert(std::vector<std::pair<int, int>>& heap_min,
            std::vector<std::pair<int, int>>& heap_max, int& length) {
  int number;
  std::cin >> number;
  ++length;
  heap_min.push_back(std::make_pair(number, length - 1));
  heap_max.push_back(std::make_pair(number, length - 1));
  SiftUpMin(heap_min, heap_max, length - 1);
  SiftUpMax(heap_min, heap_max, length - 1);
  std::cout << "ok"
            << "\n";
}

void ExtractMin(std::vector<std::pair<int, int>>& heap_min,
                std::vector<std::pair<int, int>>& heap_max, int& length) {
  if (length > 0) {
    std::cout << heap_min[0].first << "\n";
    std::swap(heap_max[heap_min[0].second].second,
              heap_max[heap_min[length - 1].second].second);
    std::swap(heap_min[0], heap_min[length - 1]);
    heap_min[heap_max[length - 1].second].second = heap_min[length - 1].second;
    std::swap(heap_max[length - 1], heap_max[heap_min[length - 1].second]);
    heap_max.pop_back();
    SiftUpMax(heap_min, heap_max, heap_min[length - 1].second);
    heap_min.pop_back();
    SiftDownMax(heap_min, heap_max, length - 1, 0);
    --length;
  } else {
    std::cout << "error"
              << "\n";
  }
}

void GetMin(std::vector<std::pair<int, int>>& heap_min, int length) {
  if (length > 0) {
    std::cout << heap_min[0].first << "\n";
  } else {
    std::cout << "error"
              << "\n";
  }
}

void ExtractMax(std::vector<std::pair<int, int>>& heap_min,
                std::vector<std::pair<int, int>>& heap_max, int& length) {
  if (length > 0) {
    std::cout << heap_max[0].first << "\n";
    std::swap(heap_min[heap_max[0].second].second,
              heap_min[heap_max[length - 1].second].second);
    std::swap(heap_max[0], heap_max[length - 1]);
    heap_max[heap_min[length - 1].second].second = heap_max[length - 1].second;
    std::swap(heap_min[length - 1], heap_min[heap_max[length - 1].second]);
    heap_min.pop_back();
    SiftUpMin(heap_min, heap_max, heap_max[length - 1].second);
    heap_max.pop_back();
    SiftDownMin(heap_min, heap_max, length - 1, 0);
    --length;
  } else {
    std::cout << "error"
              << "\n";
  }
}

void GetMax(std::vector<std::pair<int, int>>& heap_max, int length) {
  if (length > 0) {
    std::cout << heap_max[0].first << "\n";
  } else {
    std::cout << "error"
              << "\n";
  }
}

void Size(int length) { std::cout << length << "\n"; }

void Clear(std::vector<std::pair<int, int>>& heap_min,
           std::vector<std::pair<int, int>>& heap_max, int& length) {
  std::cout << "ok"
            << "\n";
  heap_min.clear();
  heap_max.clear();
  length = 0;
}

int main() {
  int questions;
  std::cin >> questions;
  std::vector<std::pair<int, int>> heap_min(0);
  std::vector<std::pair<int, int>> heap_max(0);
  int length = 0;
  std::string command;
  for (int question = 0; question < questions; ++question) {
    std::cin >> command;
    if (command == "insert") {
      Insert(heap_min, heap_max, length);
    } else if (command == "extract_min") {
      ExtractMin(heap_min, heap_max, length);
    } else if (command == "get_min") {
      GetMin(heap_min, length);
    } else if (command == "extract_max") {
      ExtractMax(heap_min, heap_max, length);
    } else if (command == "get_max") {
      GetMax(heap_max, length);
    } else if (command == "size") {
      Size(length);
    } else if (command == "clear") {
      Clear(heap_min, heap_max, length);
    }
  }
}
