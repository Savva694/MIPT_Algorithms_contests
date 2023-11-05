#include <deque>
#include <iostream>
#include <string>

void Enqueue(std::deque<int>& students, std::deque<int>& minimal, int student) {
  students.push_back(student);
  while (!(minimal.empty()) && minimal.back() > students.back()) {
    minimal.pop_back();
  }
  minimal.push_back(students.back());
}

int Dequeue(std::deque<int>& students, std::deque<int>& minimal) {
  if (students.empty()) {
    return 0;
  }
  if (minimal.front() == students.front()) {
    minimal.pop_front();
  }
  int front_student;
  front_student = students.front();
  students.pop_front();
  return front_student;
}

int Front(std::deque<int>& students) {
  if (students.empty()) {
    return 0;
  }
  return students.front();
}

size_t Size(std::deque<int>& students) { return students.size(); }

void Clear(std::deque<int>& students, std::deque<int>& minimal) {
  students.clear();
  minimal.clear();
}

int SayMin(std::deque<int>& minimal) {
  if (minimal.empty()) {
    return 0;
  }
  return minimal.front();
}

int main() {
  int requests;
  std::cin >> requests;
  std::deque<int> students;
  std::deque<int> minimal;
  std::string command;
  int student;
  int temporary;
  for (int request = 0; request < requests; ++request) {
    std::cin >> command;
    if (command == "enqueue") {
      std::cin >> student;
      Enqueue(students, minimal, student);
      std::cout << "ok" << std::endl;
    } else if (command == "dequeue") {
      temporary = Dequeue(students, minimal);
      if (temporary == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << temporary << std::endl;
      }
    } else if (command == "front") {
      temporary = Front(students);
      if (temporary == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << temporary << std::endl;
      }
    } else if (command == "size") {
      std::cout << Size(students) << std::endl;
    } else if (command == "clear") {
      Clear(students, minimal);
      std::cout << "ok" << std::endl;
    } else {
      temporary = SayMin(minimal);
      if (temporary == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << temporary << std::endl;
      }
    }
  }
  return 0;
}
