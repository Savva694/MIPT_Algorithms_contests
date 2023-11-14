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
    std::cout << "ok" << std::endl;
  }

  void Dequeue() {
    if (students_.empty()) {
      std::cout << "error" << std::endl;
      return;
    }
    if (minimal_.front() == students_.front()) {
      minimal_.pop_front();
    }
    std::cout << students_.front() << std::endl;
    students_.pop_front();
  }

  void Front() {
    if (students_.empty()) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << students_.front() << std::endl;
    }
  }

  void Size() { std::cout << students_.size() << std::endl; }

  void Clear() {
    students_.clear();
    minimal_.clear();
    std::cout << "ok" << std::endl;
  }

  void SayMin() {
    if (minimal_.empty()) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << minimal_.front() << std::endl;
    }
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
    } else if (command == "dequeue") {
      hat.Dequeue();
    } else if (command == "front") {
      hat.Front();
    } else if (command == "size") {
      hat.Size();
    } else if (command == "clear") {
      hat.Clear();
    } else {
      hat.SayMin();
    }
  }
  return 0;
}
