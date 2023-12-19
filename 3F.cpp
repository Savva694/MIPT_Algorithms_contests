#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Node {
  int value = 0;
  int left_child = -1;
  int right_child = -1;

  Node(int value, int left_child, int right_child)
      : value(value), left_child(left_child), right_child(right_child) {}

  Node() : value(0), left_child(-1), right_child(-1) {}
};

class SegmentTree {
 private:
  int tree_size_;
  std::vector<Node> nodes_;
  std::vector<int> main_nodes_;
  std::vector<std::pair<int, int>> numbers_;

  void CreateSegmentTree(int height) {
    if (height == 1) {
      nodes_.push_back(Node(0, -1, -1));
      return;
    }
    int length = static_cast<int>(nodes_.size());
    nodes_.push_back(Node(0, length + 1, -1));
    CreateSegmentTree(height - 1);
    nodes_[length].right_child = static_cast<int>(nodes_.size());
    CreateSegmentTree(height - 1);
  }

  void AddBranches(int length) {
    for (int i = 1; i <= length; ++i) {
      int count_nodes = static_cast<int>(nodes_.size());
      main_nodes_[i] = count_nodes;
      int last_version = main_nodes_[i - 1];
      int new_version = count_nodes;
      Node start(0, -1, -1);
      nodes_.push_back(start);
      ++count_nodes;

      int position = numbers_[i - 1].second;
      int left = 0;
      int right = tree_size_ - 1;
      while (true) {
        nodes_[new_version].value = nodes_[last_version].value + 1;
        if (nodes_[last_version].left_child == -1) {
          break;
        }
        int middle = (right + left) / 2;
        if (middle >= position) {
          nodes_[new_version].right_child = nodes_[last_version].right_child;
          nodes_[new_version].left_child = count_nodes;
          nodes_.push_back(start);
          ++count_nodes;
          new_version = nodes_[new_version].left_child;
          last_version = nodes_[last_version].left_child;
          right = middle;
        } else {
          nodes_[new_version].left_child = nodes_[last_version].left_child;
          nodes_[new_version].right_child = count_nodes;
          nodes_.push_back(start);
          ++count_nodes;
          new_version = nodes_[new_version].right_child;
          last_version = nodes_[last_version].right_child;
          left = middle;
        }
      }
    }
  }

 public:
  SegmentTree(int length, std::vector<std::pair<int, int>>& new_numbers) {
    numbers_ = new_numbers;
    std::sort(numbers_.begin(), numbers_.end());
    tree_size_ =
        static_cast<int>(pow(2, static_cast<int>(log2(length - 1)) + 1));
    int height = static_cast<int>(log2(tree_size_)) + 1;
    CreateSegmentTree(height);
    main_nodes_.resize(length + 1);
    main_nodes_[0] = 0;
    AddBranches(length);
  }

  int GiveSumOnSegment(int start, int left, int right, int first_pos,
                       int second_pos) {
    if (left <= first_pos && second_pos <= right) {
      return nodes_[start].value;
    }
    int answer = 0;
    int middle = (first_pos + second_pos) / 2;
    if (left <= middle) {
      answer += GiveSumOnSegment(nodes_[start].left_child, left, right,
                                 first_pos, middle);
    }
    if (right > middle) {
      answer += GiveSumOnSegment(nodes_[start].right_child, left, right,
                                 middle + 1, second_pos);
    }
    return answer;
  }

  int GiveSumOnSegment(int left, int right, int number) {
    return GiveSumOnSegment(main_nodes_[number], left - 1, right - 1, 0,
                            tree_size_ - 1);
  }

  int GiveSumOnSegmentInThisBorder(int left, int right, int lower, int upper) {
    return GiveSumOnSegment(left, right, upper) -
           GiveSumOnSegment(left, right, lower - 1);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int length;
  int questions;
  std::cin >> length >> questions;
  std::vector<std::pair<int, int>> numbers(length);
  for (int i = 0; i < length; ++i) {
    std::cin >> numbers[i].first;
    numbers[i].second = i;
  }
  SegmentTree segment_tree(length, numbers);
  int lower;
  int upper;
  int left;
  int right;
  for (int question = 0; question < questions; ++question) {
    std::cin >> left >> right >> lower >> upper;
    std::cout << segment_tree.GiveSumOnSegmentInThisBorder(left, right, lower,
                                                           upper)
              << "\n";
  }
  return 0;
}
