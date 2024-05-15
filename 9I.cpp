#include <iostream>
#include <numeric>
#include <vector>

class Graph {
 private:
  size_t left_;
  size_t right_;
  std::vector<std::vector<size_t>> edges_;
  std::vector<size_t> matching_;
  std::vector<bool> left_used_;
  std::vector<bool> right_used_;

 public:
  Graph(size_t left, size_t right, std::vector<std::vector<size_t>>& edges,
        std::vector<size_t>& matching)
      : left_(left), right_(right) {
    matching_.resize(right_, std::numeric_limits<size_t>::max());
    for (size_t i = 0; i < left_; ++i) {
      if (matching[i] != 0) {
        matching_[matching[i] - 1] = i;
      }
    }
    edges_.resize(left_);
    for (size_t i = 0; i < left_; ++i) {
      for (size_t vertex : edges[i]) {
        if (i != matching_[vertex - 1]) {
          edges_[i].push_back(vertex - 1);
        }
      }
    }
    left_used_.resize(left_, false);
    right_used_.resize(right_, false);
  }

  void Dfs(size_t vertex, bool is_left) {
    if (is_left) {
      if (left_used_[vertex]) {
        return;
      }
      left_used_[vertex] = true;
      for (size_t neighbour : edges_[vertex]) {
        Dfs(neighbour, false);
      }
    } else {
      if (right_used_[vertex]) {
        return;
      }
      right_used_[vertex] = true;
      if (matching_[vertex] != std::numeric_limits<size_t>::max()) {
        Dfs(matching_[vertex], true);
      }
    }
  }

  std::pair<std::vector<size_t>, std::vector<size_t>> GetMaxIndependentSet() {
    std::vector<size_t> left_set;
    std::vector<size_t> right_set;
    std::vector<bool> left_not_in_matching(left_, true);
    for (size_t vertex : matching_) {
      if (vertex != std::numeric_limits<size_t>::max()) {
        left_not_in_matching[vertex] = false;
      }
    }
    for (size_t i = 0; i < left_; ++i) {
      if (left_not_in_matching[i]) {
        Dfs(i, true);
      }
    }

    for (size_t i = 0; i < left_; ++i) {
      if (!left_used_[i]) {
        left_set.push_back(i);
      }
    }
    for (size_t i = 0; i < right_; ++i) {
      if (right_used_[i]) {
        right_set.push_back(i);
      }
    }

    return std::make_pair(left_set, right_set);
  }
};

int main() {
  size_t left;
  size_t right;
  std::cin >> left;
  std::cin >> right;
  std::vector<std::vector<size_t>> edges(left);
  size_t count;
  for (size_t i = 0; i < left; ++i) {
    std::cin >> count;
    edges[i].resize(count);
    for (size_t j = 0; j < count; ++j) {
      std::cin >> edges[i][j];
    }
  }
  std::vector<size_t> matching(left);
  for (size_t i = 0; i < left; ++i) {
    std::cin >> matching[i];
  }

  Graph graph(left, right, edges, matching);
  std::pair<std::vector<size_t>, std::vector<size_t>> max_independent_sets =
      graph.GetMaxIndependentSet();
  std::vector<size_t> left_set = std::move(max_independent_sets.first);
  std::vector<size_t> right_set = std::move(max_independent_sets.second);

  std::cout << left_set.size() + right_set.size() << "\n";
  std::cout << left_set.size() << " ";
  for (size_t vertex : left_set) {
    std::cout << vertex + 1 << " ";
  }
  std::cout << "\n" << right_set.size() << " ";
  for (size_t vertex : right_set) {
    std::cout << vertex + 1 << " ";
  }
  return 0;
}
