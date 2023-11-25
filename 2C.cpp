#include <deque>
#include <iostream>
#include <string>

class GoblinDeque {
 private:
  std::deque<int> left_;
  std::deque<int> right_;

  void MakeDequeCorrect() {
    if (left_.size() > right_.size()) {
      right_.push_back(left_.front());
      left_.pop_front();
    }
  }

 public:
  void AddNewOrdinaryGoblin(int goblin) {
    left_.push_back(goblin);
    MakeDequeCorrect();
  }

  void AddNewPrivilegedGoblin(int goblin) {
    left_.push_front(goblin);
    MakeDequeCorrect();
  }

  int DeleteGoblin() {
    int deleting_goblin = right_.front();
    right_.pop_front();
    MakeDequeCorrect();
    return deleting_goblin;
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
      std::cout << goblin_queue.DeleteGoblin() << "\n";
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
