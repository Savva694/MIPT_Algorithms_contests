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

std::vector<Node> nodes;
std::vector<int> main_nodes;

void CreatePersistentSegmentTree(int height) {
  if (height == 1) {
    nodes.push_back(Node(0, -1, -1));
    return;
  }
  int length = static_cast<int>(nodes.size());
  nodes.push_back(Node(0, length + 1, -1));
  CreatePersistentSegmentTree(height - 1);
  nodes[length].right_child = static_cast<int>(nodes.size());
  CreatePersistentSegmentTree(height - 1);
}

int GiveSumOnSegment(int start, int left, int right, int first_pos,
                     int second_pos) {
  if (left <= first_pos && second_pos <= right) {
    return nodes[start].value;
  }
  int answer = 0;
  int middle = (first_pos + second_pos) / 2;
  if (left <= middle) {
    answer += GiveSumOnSegment(nodes[start].left_child, left, right, first_pos,
                               middle);
  }
  if (right > middle) {
    answer += GiveSumOnSegment(nodes[start].right_child, left, right,
                               middle + 1, second_pos);
  }
  return answer;
}

void AddBranches(int length, std::vector<std::pair<int, int>>& numbers) {
  int tree_size =
      static_cast<int>(pow(2, static_cast<int>(log2(length - 1)) + 1));
  for (int i = 1; i <= length; ++i) {
    int count_nodes = static_cast<int>(nodes.size());
    main_nodes[i] = count_nodes;
    int last_version = main_nodes[i - 1];
    int new_version = count_nodes;
    Node start(0, -1, -1);
    nodes.push_back(start);
    ++count_nodes;

    int position = numbers[i - 1].second;
    int left = 0;
    int right = tree_size - 1;
    while (true) {
      nodes[new_version].value = nodes[last_version].value + 1;
      if (nodes[last_version].left_child == -1) {
        break;
      }
      int middle = (right + left) / 2;
      if (middle >= position) {
        nodes[new_version].right_child = nodes[last_version].right_child;
        nodes[new_version].left_child = count_nodes;
        nodes.push_back(start);
        ++count_nodes;
        new_version = nodes[new_version].left_child;
        last_version = nodes[last_version].left_child;
        right = middle;
      } else {
        nodes[new_version].left_child = nodes[last_version].left_child;
        nodes[new_version].right_child = count_nodes;
        nodes.push_back(start);
        ++count_nodes;
        new_version = nodes[new_version].right_child;
        last_version = nodes[last_version].right_child;
        left = middle;
      }
    }
  }
}

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
  std::sort(numbers.begin(), numbers.end());
  int tree_size =
      static_cast<int>(pow(2, static_cast<int>(log2(length - 1)) + 1));
  main_nodes.resize(length + 1);
  CreatePersistentSegmentTree(static_cast<int>(log2(tree_size)) + 1);
  main_nodes[0] = 0;
  AddBranches(length, numbers);
  int lower;
  int upper;
  int left;
  int right;
  for (int question = 0; question < questions; ++question) {
    std::cin >> left >> right >> lower >> upper;
    std::cout << GiveSumOnSegment(main_nodes[upper], left - 1, right - 1, 0,
                                  tree_size - 1) -
                     GiveSumOnSegment(main_nodes[lower - 1], left - 1,
                                      right - 1, 0, tree_size - 1)
              << "\n";
  }
  return 0;
}
