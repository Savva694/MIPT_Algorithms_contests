#include <iostream>
#include <random>
#include <string>
#include <vector>

std::mt19937 family_random;
const int kRandomMod = 1'000'000;

struct Node {
  int first_coord;
  int second_coord;
  Node* left_child;
  Node* right_child;
  int lefter_count;
  int righter_count;

  Node()
      : first_coord(0),
        second_coord(0),
        left_child(nullptr),
        right_child(nullptr),
        lefter_count(0),
        righter_count(0){};
};

int Count(Node* main) {
  if (main == nullptr) {
    return 0;
  }
  return main->lefter_count + main->righter_count + 1;
}

Node* Merge(Node* first, Node* second) {
  if (first == nullptr) {
    return second;
  }
  if (second == nullptr) {
    return first;
  }
  if (first->first_coord > second->first_coord) {
    return Merge(second, first);
  }
  if (first->second_coord <= second->second_coord) {
    first->right_child = Merge(first->right_child, second);
    first->righter_count = Count(first->right_child);
    return first;
  }
  second->left_child = Merge(second->left_child, first);
  second->lefter_count = Count(second->left_child);
  return second;
}

std::pair<Node*, Node*> Split(Node* main, int value) {
  if (main == nullptr) {
    return {nullptr, nullptr};
  }
  if (main->first_coord <= value) {
    std::pair<Node*, Node*> right_split = Split(main->right_child, value);
    main->right_child = right_split.first;
    main->righter_count = Count(right_split.first);
    return {main, right_split.second};
  }
  std::pair<Node*, Node*> left_split = Split(main->left_child, value);
  main->left_child = left_split.second;
  main->lefter_count = Count(left_split.second);
  return {left_split.first, main};
}

Node* KthFromNode(Node* main, int number) {
  if (main == nullptr || main->lefter_count == number) {
    return main;
  }
  if (main->lefter_count < number) {
    return KthFromNode(main->right_child, number - main->lefter_count - 1);
  }
  return KthFromNode(main->left_child, number);
}

void DeleteAllTree(Node* main) {
  if (main == nullptr) {
    return;
  }
  DeleteAllTree(main->left_child);
  DeleteAllTree(main->right_child);
  delete main;
}

class Family {
 private:
  Node* head_;

 public:
  Family() : head_(nullptr) {}

  void Insert(int value) {
    std::pair<Node*, Node*> first_split = Split(this->head_, value);
    std::pair<Node*, Node*> second_split = Split(first_split.first, value - 1);
    if (second_split.second != nullptr) {
      this->head_ = Merge(Merge(second_split.first, second_split.second),
                          first_split.second);
      return;
    }
    Node* new_node = new Node;
    new_node->first_coord = value;
    new_node->second_coord = family_random() % kRandomMod;
    this->head_ =
        Merge(Merge(second_split.first, new_node), first_split.second);
  }

  void Delete(int value) {
    std::pair<Node*, Node*> first_split = Split(this->head_, value);
    std::pair<Node*, Node*> second_split = Split(first_split.first, value - 1);
    this->head_ = Merge(second_split.first, first_split.second);
    if (second_split.second == nullptr) {
      return;
    }
    delete second_split.second;
  }

  bool Exists(int value) {
    std::pair<Node*, Node*> first_split = Split(this->head_, value);
    std::pair<Node*, Node*> second_split = Split(first_split.first, value - 1);
    this->head_ = Merge(Merge(second_split.first, second_split.second),
                        first_split.second);
    return second_split.second != nullptr;
  }

  Node* Next(int value) {
    Node* answer = nullptr;
    Node* now = head_;
    while (now != nullptr) {
      if (now->first_coord > value) {
        answer = now;
        now = now->left_child;
      } else {
        now = now->right_child;
      }
    }
    return answer;
  }

  Node* Prev(int value) {
    Node* answer = nullptr;
    Node* now = head_;
    while (now != nullptr) {
      if (now->first_coord < value) {
        answer = now;
        now = now->right_child;
      } else {
        now = now->left_child;
      }
    }
    return answer;
  }

  Node* Kth(int number) { return KthFromNode(head_, number); }

  ~Family() { DeleteAllTree(head_); }
};

int main() {
  Family family;
  std::string command;
  int value;
  while (std::cin >> command >> value) {
    if (command == "insert") {
      family.Insert(value);
    } else if (command == "delete") {
      family.Delete(value);
    } else if (command == "exists") {
      if (family.Exists(value)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    } else if (command == "next") {
      Node* answer = family.Next(value);
      if (answer != nullptr) {
        std::cout << answer->first_coord << "\n";
      } else {
        std::cout << "none\n";
      }
    } else if (command == "prev") {
      Node* answer = family.Prev(value);
      if (answer != nullptr) {
        std::cout << answer->first_coord << "\n";
      } else {
        std::cout << "none\n";
      }
    } else if (command == "kth") {
      Node* answer = family.Kth(value);
      if (answer != nullptr) {
        std::cout << answer->first_coord << "\n";
      } else {
        std::cout << "none\n";
      }
    }
  }
  return 0;
}
