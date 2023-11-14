#include <deque>
#include <iostream>
#include <string>

struct GoblinDeque {
  std::deque<int> left;
  std::deque<int> right;

  void MakeDequeCorrect() {
    if (left.size() > right.size()) {
      right.push_back(left.front());
      left.pop_front();
    }
  }

  void AddNewOrdinaryGoblin(int goblin) {
    left.push_back(goblin);
    this->MakeDequeCorrect();
  }

  void AddNewPrivilegedGoblin(int goblin) {
    left.push_front(goblin);
    this->MakeDequeCorrect();
  }

  void DeleteGoblin() {
    std::cout << right.front() << std::endl;
    right.pop_front();
    this->MakeDequeCorrect();
  }
};

int main() {
  int requests;
  std::cin >> requests;
  GoblinDeque goblin_queue;
  std::string sign;
  int goblin;
  for (int request = 0; request < requests; ++request) {
    std::cin >> sign;
    if (sign == "-") {
      goblin_queue.DeleteGoblin();
    } else if (sign == "+") {
      std::cin >> goblin;
      goblin_queue.AddNewOrdinaryGoblin(goblin);
    } else {
      std::cin >> goblin;
      goblin_queue.AddNewPrivilegedGoblin(goblin);
    }
  }
  return 0;
}
