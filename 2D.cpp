#include <deque>
#include <iostream>
#include <string>

class DistributingHat {
 private:
  std::deque<int> students_;
  std::deque<int> minimal_;

 public:
  void Enqueue(int student) {
    students_.push_back(student);
    while (!(minimal_.empty()) && minimal_.back() > students_.back()) {
      minimal_.pop_back();
    }
    minimal_.push_back(students_.back());
  }

  bool Dequeue() {
    if (students_.empty()) {
      return false;
    }
    if (minimal_.front() == students_.front()) {
      minimal_.pop_front();
    }
    std::cout << students_.front() << std::endl;
    students_.pop_front();
    return true;
  }

  int Front() {
    if (students_.empty()) {
      return 0;
    }
    return students_.front();
  }

  size_t Size() { return students_.size(); }

  void Clear() {
    students_.clear();
    minimal_.clear();
  }

  int GetMin() {
    if (minimal_.empty()) {
      return 0;
    }
    return minimal_.front();
  }
};

int main() {
  int requests;
  std::cin >> requests;
  DistributingHat hat;
  std::string command;
  int student;
  for (int request = 0; request < requests; ++request) {
    std::cin >> command;
    if (command == "enqueue") {
      std::cin >> student;
      hat.Enqueue(student);
      std::cout << "ok" << std::endl;
    } else if (command == "dequeue") {
      if (!hat.Dequeue()) {
        std::cout << "error" << std::endl;
      }
    } else if (command == "front") {
      int front = hat.Front();
      if (front == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << front << std::endl;
      }
    } else if (command == "size") {
      std::cout << hat.Size() << std::endl;
    } else if (command == "clear") {
      hat.Clear();
      std::cout << "ok" << std::endl;
    } else {
      int min = hat.GetMin();
      if (min == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << min << std::endl;
      }
    }
  }
  return 0;
}
