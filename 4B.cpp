#include <iostream>
#include <string>
#include <vector>

struct Node {
  int value;
  int left_child;
  int right_child;
  int father;
  int height;

  Node(int value, int left_child, int right_child, int father, int height)
      : value(value),
        left_child(left_child),
        right_child(right_child),
        father(father),
        height(height){};

  Node() : value(0), left_child(0), right_child(0), father(0), height(0){};
};

class AVLTree {
 private:
  std::vector<Node> points_;
  int top_;

  void FixHeight(int index) {
    points_[index].height =
        std::max(points_[points_[index].left_child].height,
                 points_[points_[index].right_child].height) +
        1;
  }

  int DeltaHeight(int index) {
    return points_[points_[index].left_child].height -
           points_[points_[index].right_child].height;
  }

  void LeftRotate(int index) {
    int child = points_[index].left_child;
    if (points_[index].father != 0) {
      top_ = child;
      if (points_[points_[index].father].left_child == index) {
        points_[points_[index].father].left_child = child;
      } else {
        points_[points_[index].father].right_child = child;
      }
    }
    points_[child].father = points_[index].father;
    points_[index].father = child;
    points_[index].left_child = points_[child].right_child;
    points_[child].right_child = index;
    FixHeight(index);
    FixHeight(child);
    FixHeight(points_[child].father);
  }

  void RightRotate(int index) {
    int child = points_[index].right_child;
    if (points_[index].father != 0) {
      top_ = child;
      if (points_[points_[index].father].left_child == index) {
        points_[points_[index].father].left_child = child;
      } else {
        points_[points_[index].father].right_child = child;
      }
    }
    points_[child].father = points_[index].father;
    points_[index].father = child;
    points_[index].right_child = points_[child].left_child;
    points_[child].left_child = index;
    FixHeight(index);
    FixHeight(child);
    FixHeight(points_[child].father);
  }

  void LeftRightRotate(int index) {
    int child = points_[index].left_child;
    RightRotate(child);
    LeftRotate(index);
  }

  void RightLeftRotate(int index) {
    int child = points_[index].right_child;
    LeftRotate(child);
    RightRotate(index);
  }

  void MakeTreeCorrectAfterInsert(int now_point) {
    while (now_point != 0) {
      if (DeltaHeight(now_point) == -2) {
        int child = points_[now_point].right_child;
        int child_delta = DeltaHeight(child);
        if (child_delta <= 0) {
          RightRotate(now_point);
        } else {
          RightLeftRotate(now_point);
        }
      } else if (DeltaHeight(now_point) == 2) {
        int child = points_[now_point].left_child;
        int child_delta = DeltaHeight(child);
        if (child_delta <= 0) {
          LeftRotate(now_point);
        } else {
          LeftRightRotate(now_point);
        }
      }
      now_point = points_[now_point].father;
    }
  }

 public:
  AVLTree() : points_({Node()}), top_(0){};

  void Insert(int number) {
    int now_point = top_;
    int next_point = 0;
    while (true) {
      if (points_[now_point].value == number) {
        return;
      }
      if (points_[now_point].value < number) {
        next_point = points_[now_point].right_child;
        if (next_point == 0) {
          points_[now_point].right_child = static_cast<int>(points_.size());
        }
      } else {
        next_point = points_[now_point].left_child;
        if (next_point == 0) {
          points_[now_point].left_child = static_cast<int>(points_.size());
        }
      }
      if (next_point == 0) {
        Node point;
        point.value = number;
        point.left_child = 0;
        point.right_child = 0;
        point.father = now_point;
        point.height = 1;
        points_.push_back(point);
        if (now_point == 0) {
          top_ = 1;
        }
        break;
      }
      now_point = next_point;
    }
    MakeTreeCorrectAfterInsert(static_cast<int>(points_.size()) - 1);
  }

  int Find(int number) {
    int now_point = top_;
    int answer = -1;
    int next_point = 0;
    while (true) {
      if (points_[now_point].value == number) {
        return number;
      }
      if (points_[now_point].value < number) {
        next_point = points_[now_point].right_child;
      } else {
        next_point = points_[now_point].left_child;
        answer = points_[now_point].value;
      }
      if (next_point == 0) {
        break;
      }
      now_point = next_point;
    }
    return answer;
  }
};

int main() {
  const int kMod = 1'000'000'000;
  AVLTree dominics_garage;
  int questions;
  std::cin >> questions;
  std::string command;
  std::string last_command = "0";
  int last_result = 0;
  int number;
  for (int question = 0; question < questions; ++question) {
    std::cin >> command >> number;
    if (command == "+") {
      if (last_command == "?") {
        dominics_garage.Insert((number + last_result) % kMod);
      } else {
        dominics_garage.Insert(number);
      }
      last_command = "+";
    } else if (command == "?") {
      last_result = dominics_garage.Find(number);
      std::cout << last_result << "\n";
      last_command = "?";
    }
  }
  return 0;
}
