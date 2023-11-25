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

  int Dequeue() {
    if (students_.empty()) {
      return 0;
    }
    if (minimal_.front() == students_.front()) {
      minimal_.pop_front();
    }
    int front_student = students_.front();
    students_.pop_front();
    return front_student;
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
      std::cout << "ok"
                << "\n";
    } else if (command == "dequeue") {
      int front_student = hat.Dequeue();
      if (front_student == 0) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << front_student << "\n";
      }
    } else if (command == "front") {
      int front_student = hat.Front();
      if (front_student == 0) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << front_student << "\n";
      }
    } else if (command == "size") {
      std::cout << hat.Size() << "\n";
    } else if (command == "clear") {
      hat.Clear();
      std::cout << "ok"
                << "\n";
    } else {
      int min = hat.GetMin();
      if (min == 0) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << min << "\n";
      }
    }
  }
  return 0;
}
