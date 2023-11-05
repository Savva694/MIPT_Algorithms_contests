#include <deque>
#include <iostream>
#include <string>

void MakeDequeCorrect(std::deque<int>& left, std::deque<int>& right) {
  if (left.size() > right.size()) {
    right.push_back(left.front());
    left.pop_front();
  }
}

int main() {
  int requests;
  std::cin >> requests;
  std::deque<int> left;
  std::deque<int> right;
  std::string sign;
  int goblin;
  for (int request = 0; request < requests; ++request) {
    std::cin >> sign;
    if (sign == "-") {
      std::cout << right.front() << std::endl;
      right.pop_front();
    } else if (sign == "+") {
      std::cin >> goblin;
      left.push_back(goblin);
    } else {
      std::cin >> goblin;
      left.push_front(goblin);
    }
    MakeDequeCorrect(left, right);
  }
  return 0;
}
